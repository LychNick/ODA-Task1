#include "OpenGLWorker.h"

glm::vec2 winParams = glm::vec2(800, 600);

OpenGLWorker::OpenGLWorker(void) :
  OMVP_(glm::mat4(1.f))
{
}

OpenGLWorker::~OpenGLWorker(void)
{
}

GLuint createShader(GLuint type, const std::wstring& file)
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
      char* log = new char[logLen];
      GLsizei written;
      glGetShaderInfoLog(newShader, logLen, &written, log);
      fprintf(stderr, "Shader log:\n%s", log);
      delete[] log;
    }
    throw std::invalid_argument("shader error");
  }
  return newShader;
};

GLuint createShaderProgram(const std::vector<GLuint>& shaders)
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
      char* log = new char[logLen];
      GLsizei written;
      glGetProgramInfoLog(programHandle, logLen, &written, log);
      fprintf(stderr, "Program log: \n%s", log);
      delete[] log;
    }
    throw std::invalid_argument("Shader error");
  }
  return programHandle;
};

GLuint createShaderPair(const std::wstring& fragmentShader, const std::wstring& vertexShader)
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
void OpenGLWorker::setCurrentDir()
{
  wchar_t  szPath[MAX_PATH];
  wchar_t szFileName[MAX_PATH];
  GetModuleFileName(0, &szFileName[0], MAX_PATH);
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

void OpenGLWorker::openGLInit() const
{
  int argc = 0;
  glutInit(&argc, nullptr);
  glutInitContextProfile(GLUT_CORE_PROFILE);
}



void OpenGLWorker::createWindow(const std::string& name) const
{
  glutInitWindowSize(static_cast<int>(winParams.x),
    static_cast<int>(winParams.y));
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

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  glClearColor(1.f, 1.f, 1.f, 1.f);

  std::wstring fragmentShaderPath = mainDir_ + L"\\Shaders\\main.fp";
  std::wstring vertexShaderName = mainDir_ + L"\\Shaders\\main.vp";
  mainShader_ = createShaderPair(fragmentShaderPath, vertexShaderName);

  OMVP_ = glm::ortho(
    -winParams.x / 2.f,
    winParams.x / 2.f,
    -winParams.y / 2.f,
    winParams.y / 2.f,
    -1000.0f, 1000.0f);
}


void OpenGLWorker::drawEntity(const OpenGLEntity& entity) const
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
  glUniformMatrix4fv(locTrans, 1, GL_FALSE, &Translate[0][0]);
  checkGLError(__FILE__, __LINE__);
  
  GLuint locRot = glGetUniformLocation(mainShader_, "Rotate");
  glUniformMatrix4fv(locRot, 1, GL_FALSE, &rotate[0][0]);
  checkGLError(__FILE__, __LINE__);
  
  GLuint locScale = glGetUniformLocation(mainShader_, "Scale");
  glUniformMatrix4fv(locScale, 1, GL_FALSE, &scale[0][0]);
  checkGLError(__FILE__, __LINE__);
  
  GLuint locColor = glGetUniformLocation(mainShader_, "mainColor");
  glUniform4f(locColor, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
  checkGLError(__FILE__, __LINE__);
  
  
  glPolygonMode(GL_FRONT, GL_FILL);
  checkGLError(__FILE__, __LINE__);
  glDrawArrays(entity.drawType, 0, entity.size);
  checkGLError(__FILE__, __LINE__);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

void OpenGLWorker::checkGLError(const std::string& file, GLuint line) const
{
  GLenum error = glGetError();
  if (error != 0) 
  {
    throw std::invalid_argument("GL error: " + std::to_string(error) 
      + " at " + file + " in " + std::to_string(line));
  }
}
