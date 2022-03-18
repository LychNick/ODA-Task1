#include "OpenGLDraw.h"

GLfloat globalScale = 1.f;
glm::mat4 globalTranslate = glm::mat4(1.f);
GLuint mainShader_ = 0;
glm::mat4 OMVP_;

const GLuint DRAW_TYPE = GL_LINE_STRIP;
const GLuint CORD_SIZE = 3;

struct entity_t 
{
  GLuint VAO;
  GLuint size;
};

std::vector<entity_t> Entities_;

void drawEntity(const entity_t& entity)
{
  glUseProgram(mainShader_);
  checkGLError(__FILE__, __LINE__);

  glBindVertexArray(entity.VAO);
  checkGLError(__FILE__, __LINE__);

  glEnableVertexAttribArray(0);

  glm::mat4 rotate = glm::mat4(1.0f);
  glm::mat4 scale = glm::mat4(1.0f);
  scale = glm::scale(scale, glm::vec3(globalScale));

  GLuint locMVP = glGetUniformLocation(mainShader_, "Matrix");
  glUniformMatrix4fv(locMVP, 1, GL_FALSE, &OMVP_[0][0]);
  checkGLError(__FILE__, __LINE__);

  GLuint locTrans = glGetUniformLocation(mainShader_, "Translate");
  glUniformMatrix4fv(locTrans, 1, GL_FALSE, &globalTranslate[0][0]);
  checkGLError(__FILE__, __LINE__);

  GLuint locRot = glGetUniformLocation(mainShader_, "Rotate");
  glUniformMatrix4fv(locRot, 1, GL_FALSE, &rotate[0][0]);
  checkGLError(__FILE__, __LINE__);

  GLuint locScale = glGetUniformLocation(mainShader_, "Scale");
  glUniformMatrix4fv(locScale, 1, GL_FALSE, &scale[0][0]);
  checkGLError(__FILE__, __LINE__);

  GLuint locColor = glGetUniformLocation(mainShader_, "mainColor");
  glUniform4f(locColor, 0, 0, 0, 1);
  checkGLError(__FILE__, __LINE__);


  glPolygonMode(GL_FRONT, GL_FILL);
  checkGLError(__FILE__, __LINE__);
  glPointSize(5);
  glDrawArrays(DRAW_TYPE, 0, entity.size);
  checkGLError(__FILE__, __LINE__);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

void drawFunc()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  checkGLError(__FILE__, __LINE__);
  for (size_t i = 0; i < Entities_.size(); i++)
  {
    drawEntity(Entities_[i]);
  }
  checkGLError(__FILE__, __LINE__);
  glutSwapBuffers();
  glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y)
{
  if (dir > 0)
  {
    globalScale *= 2;
  } else
  {
    globalScale /= 2;
  }
}

void mouseState(int button, int state, int x, int y)
{
  static glm::vec2 winPos = glm::vec2(x, y);
  switch (button)
  {
  case GLUT_LEFT_BUTTON:
  {
    if (state == GLUT_DOWN)
    {
      winPos = {x, y};

    }
    if (state == GLUT_UP)
    {
      glm::vec2 shift = glm::vec2(x, y) - winPos;
      shift.y = -shift.y;
      globalTranslate = glm::translate(globalTranslate,
        glm::vec3(shift, 0) / globalScale);
    }
    break;
  }
  default:
    break;
  }
}

void checkGLError(const std::string& file, GLuint line)
{
  GLenum error = glGetError();
  if (error != 0)
  {
    throw std::invalid_argument("GL error: " + std::to_string(error)
      + " at " + file + " in " + std::to_string(line));
  }
}


OpenGLDraw::OpenGLDraw()
{
  OMVP_ = glm::mat4(1.f);
  setCurrentDir();
  openGLInit();
}

OpenGLDraw::~OpenGLDraw()
{}

void OpenGLDraw::createWindow(const glm::vec2& params, const std::string& name) const
{
  glutInitWindowSize(static_cast<int>(params.x),
    static_cast<int>(params.y));
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  windowHandler_ = glutCreateWindow(name.c_str());

  if (windowHandler_ == 0)
  {
    throw std::invalid_argument("can't initialize window");
  }
  if (glewInit() != GLEW_OK)
  {
    throw std::invalid_argument("can't initialize glew");
  }

  glutDisplayFunc(drawFunc);
  glutMouseFunc(mouseState);
  glutMouseWheelFunc(mouseWheel);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  glViewport(0, 0, static_cast<GLsizei>(params.x),
    static_cast<GLsizei>(params.y));

  glClearColor(1.f, 1.f, 1.f, 1.f);

  std::wstring fragmentShaderPath = mainDir_ + L"\\Shaders\\main.fp";
  std::wstring vertexShaderName = mainDir_ + L"\\Shaders\\main.vp";
  mainShader_ = createShaderPair(fragmentShaderPath, vertexShaderName);

  OMVP_ = glm::ortho(
    -params.x / 2.f,
    params.x / 2.f,
    -params.y / 2.f,
    params.y / 2.f,
    -1000.0f, 1000.0f);
}

void OpenGLDraw::setCurrentDir()
{
  wchar_t  szPath[MAX_PATH];
  wchar_t szFileName[MAX_PATH];
  GetModuleFileName(0, szFileName, MAX_PATH);
  int i = 0;
  int pathEnd = 0;
  while (szFileName[i] != '\0')
  {
    if (szFileName[i] == '\\')
    {
      pathEnd = i;
    }
    i++;
  }
  if (lstrcpyn(szPath, szFileName, pathEnd + 2) == NULL)
  {
    throw std::invalid_argument("can't parse main dir");
  }
  mainDir_ = szPath;
}

void OpenGLDraw::openGLInit() const
{
  int argc = 0;
  glutInit(&argc, nullptr);
  glutInitContextProfile(GLUT_CORE_PROFILE);
}

void OpenGLDraw::drawSegment(const Point2d& p1, const Point2d& p2) const
{
  std::vector<Point2d> vertices{p1, p2};
  drawPolyLine(vertices);
}

void OpenGLDraw::drawPolyLine(const std::vector<Point2d>& vertices) const
{
  GLuint VAO = 0;
  glGenVertexArrays(1, &VAO);
  
  GLuint VBOs[1];
  
  glGenBuffers(1, VBOs);
  
  GLuint positionBuffer_ = VBOs[0];
  
  glBindVertexArray(VAO);
  
  glEnableVertexAttribArray(0);
  
  std::vector<GLdouble> coordinates;
  for (int i = 0; i < vertices.size(); i++) 
  {
    coordinates.push_back(vertices[i].x());
    coordinates.push_back(vertices[i].y());
    coordinates.push_back(0);
  }

  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer_);
  glVertexAttribPointer(0, CORD_SIZE, GL_DOUBLE, GL_FALSE, 0, NULL);
  glBufferData(GL_ARRAY_BUFFER,
    sizeof(GLdouble) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
  entity_t newEntity;
  newEntity.VAO = VAO;
  newEntity.size = vertices.size();
  Entities_.push_back(newEntity);
}

void OpenGLDraw::initLoop()
{
  glutMainLoop();
}

GLuint OpenGLDraw::createShader(GLuint type, const std::wstring& file) const
{
  GLuint newShader = glCreateShader(type);
  if (!newShader)
  {
    throw std::invalid_argument("can't create shader");
  }

  std::string readData;
  std::ifstream shaderFile(file);
  if (!shaderFile)
  {
    std::wstring msg = L"cant open file: " + file;
    throw Exception(msg);
  }
  while (!shaderFile.eof())
  {
    std::string tmpLine;
    std::getline(shaderFile, tmpLine);
    readData += tmpLine + '\n';
  }
  GLchar* shaderCode = const_cast<char*>(readData.data());

  glShaderSource(newShader, 1, &shaderCode, NULL);
  glCompileShader(newShader);

  GLint result;
  glGetShaderiv(newShader, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    fprintf(stderr, "shader compilation failed!\n");
    GLint logLen;
    glGetShaderiv(newShader, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0)
    {
      std::string log;
      GLsizei written;
      glGetShaderInfoLog(newShader, logLen, &written, &log[0]);
      fprintf(stderr, "Shader log:\n%s", log.c_str());
    }
    throw std::invalid_argument("shader error");
  }
  return newShader;
};

GLuint OpenGLDraw::createShaderProgram(const std::vector<GLuint>& shaders) const
{
  GLuint programHandle = glCreateProgram();
  if (!programHandle)
  {
    throw std::invalid_argument("can't create shaderProgram");
  }
  for (size_t i = 0; i < shaders.size(); ++i)
  {
    glAttachShader(programHandle, shaders[i]);
  }

  glBindAttribLocation(programHandle, 0, "VertexPosition");
  glBindAttribLocation(programHandle, 1, "VertexColor");
  glBindAttribLocation(programHandle, 2, "VertexNormal");
  glBindAttribLocation(programHandle, 3, "VertexUV");

  glLinkProgram(programHandle);

  GLint status;
  glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
  if (!status)
  {
    fprintf(stderr, "Failed to link shader program!\n");
    GLint logLen;
    glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0)
    {
      std::string log;
      GLsizei written;
      glGetProgramInfoLog(programHandle, logLen, &written, &log[0]);
      fprintf(stderr, "Program log: \n%s", log.c_str());
    }
    throw std::invalid_argument("Shader error");
  }
  return programHandle;
};


GLuint OpenGLDraw::createShaderPair(const std::wstring& fragmentShader, const std::wstring& vertexShader) const
{
  std::vector <GLuint> shaders;
  GLuint fragShader = createShader(GL_FRAGMENT_SHADER, fragmentShader);
  GLuint vertShader = createShader(GL_VERTEX_SHADER, vertexShader);

  shaders.push_back(vertShader);
  shaders.push_back(fragShader);

  printf("%s\n", "Shaders created and compiled!");

  GLuint programHandle = createShaderProgram(shaders);

  printf("%s\n", "Shader program created and compiled!");

  return programHandle;
}
