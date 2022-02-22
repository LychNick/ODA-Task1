#include "OpenGLDrawer.h"




void drawFunc()
{
  glViewport(0, 0, static_cast<GLsizei>(winParams.x),
    static_cast<GLsizei>(winParams.y));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  openGLWorker.checkGLError(__FILE__, __LINE__);
  for (size_t i = 0; i < entities.size(); i++)
  {
    openGLWorker.drawEntity(entities[i]);
  }
  openGLWorker.checkGLError(__FILE__, __LINE__);
  glutSwapBuffers();
  glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y)
{
  if (dir > 0)
  {
    openGLWorker.globalScale *= 2;
  }
  else
  {
    openGLWorker.globalScale /= 2;
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
      winPos = { x,y };

    }
    if (state == GLUT_UP)
    {
      glm::vec2 shift = glm::vec2(x, y) - winPos;
      shift.y = -shift.y;
      openGLWorker.Translate = glm::translate(openGLWorker.Translate,
        glm::vec3(shift, 0) / openGLWorker.globalScale);
    }
    break;
  }
  default:
    break;
  }
}


void generateBuffers(OpenGLEntity& entity, std::vector<GLdouble>& vertices) 
{
  glGenVertexArrays(1, &entity.VAO);

  GLuint VBOs[1];

  glGenBuffers(1, VBOs);

  GLuint positionBuffer_ = VBOs[0];

  glBindVertexArray(entity.VAO);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer_);
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
  glBufferData(GL_ARRAY_BUFFER,
    sizeof(GLdouble) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

void OpenGLDrawer::createWindow() const
{
  openGLWorker.setCurrentDir();
  openGLWorker.openGLInit();
  openGLWorker.createWindow("Task2");

  glutDisplayFunc(drawFunc);
  glutMouseWheelFunc(mouseWheel);
  glutMouseFunc(mouseState);
}

void OpenGLDrawer::startLoop() const
{
  glutMainLoop();
}

void OpenGLDrawer::drawBoundingBox(std::shared_ptr<FrameWork::BoundingBox> box) const
{
  OpenGLEntity newEntity;
  newEntity.shape = nullptr;
  newEntity.drawType = GL_LINE_LOOP;

  Point2d leftDown = box->getLeftDownPoint();
  Point2d rightUp = box->getRightUpPoint();

  std::vector<double> vertices;

  vertices.push_back(leftDown.x());
  vertices.push_back(leftDown.y());
  vertices.push_back(0);
  vertices.push_back(leftDown.x());
  vertices.push_back(rightUp.y());
  vertices.push_back(0);
  vertices.push_back(rightUp.x());
  vertices.push_back(rightUp.y());
  vertices.push_back(0);
  vertices.push_back(rightUp.x());
  vertices.push_back(leftDown.y());
  vertices.push_back(0);

  newEntity.size = 4;

  generateBuffers(newEntity, vertices);

  entities.push_back(newEntity);
}

void OpenGLDrawer::drawSquare(std::shared_ptr<FrameWork::Square> square) const
{
  OpenGLEntity newEntity;
  newEntity.shape = square;
  newEntity.drawType = GL_LINE_LOOP;

  Point2d leftDown = square->getLeftDownPoint();
  Point2d rightUp = square->getRightUpPoint();

  std::vector<double> vertices;

  vertices.push_back(leftDown.x());
  vertices.push_back(leftDown.y());
  vertices.push_back(0);
  vertices.push_back(leftDown.x());
  vertices.push_back(rightUp.y());
  vertices.push_back(0);
  vertices.push_back(rightUp.x());
  vertices.push_back(rightUp.y());
  vertices.push_back(0);
  vertices.push_back(rightUp.x());
  vertices.push_back(leftDown.y());
  vertices.push_back(0);

  newEntity.size = 4;

  generateBuffers(newEntity, vertices);

  entities.push_back(newEntity);
}

void OpenGLDrawer::drawCircle(std::shared_ptr<FrameWork::Circle> circle) const
{
  OpenGLEntity newEntity;
  newEntity.shape = circle;
  newEntity.drawType = GL_LINE_LOOP;

  std::vector<double> vertices;

  double R = circle->getR();
  Point2d centerPoint = circle->getCenterPoint();
  double step = 2 * M_PI / FrameWork::segmentsCount;
  for (double i = 0; i < FrameWork::segmentsCount; i++)
  {
    Point2d firstPoint(centerPoint + Point2d(R * cos(step * i), R * sin(step * i)));
    Point2d secondPoint(centerPoint + Point2d(R * cos(step * (i + 1)), R * sin(step * (i + 1))));

    vertices.push_back(firstPoint.x());
    vertices.push_back(firstPoint.y());
    vertices.push_back(0);
    vertices.push_back(secondPoint.x());
    vertices.push_back(secondPoint.y());
    vertices.push_back(0);
  }
  newEntity.size = vertices.size() / 3;

  generateBuffers(newEntity, vertices);

  entities.push_back(newEntity);
}

void OpenGLDrawer::drawArc(std::shared_ptr<FrameWork::Arc> arc) const
{
  OpenGLEntity newEntity;
  newEntity.shape = arc;
  newEntity.drawType = GL_LINE_STRIP;

  std::vector<double> vertices;

  double R = arc->getR();
  Point2d centerPoint = arc->getCenterPoint();
  double startR = arc->getStartR();
  double endR = arc->getEndR();
  double step = (endR - startR) / FrameWork::segmentsCount;
  for (double i = 0; i < FrameWork::segmentsCount; i++)
  {
    Point2d point(centerPoint + Point2d(R * cos(startR + step * i), R * sin(startR + step * i)));
    
    vertices.push_back(point.x());
    vertices.push_back(point.y());
    vertices.push_back(0);
  }
  newEntity.size = vertices.size() / 3;

  generateBuffers(newEntity, vertices);

  entities.push_back(newEntity);
}

void OpenGLDrawer::drawPolygon(std::shared_ptr<FrameWork::Polygon> polygon) const
{
  OpenGLEntity newEntity;
  newEntity.shape = polygon;
  newEntity.drawType = GL_LINE_LOOP;
  
  std::vector<double> vertices;
  for (size_t i = 0; i < polygon->getPoints().size(); i++) 
  {
    vertices.push_back(polygon->getPoints()[i].x());
    vertices.push_back(polygon->getPoints()[i].y());
    vertices.push_back(0);
  }

  newEntity.size = vertices.size() / 3;

  generateBuffers(newEntity, vertices);

  entities.push_back(newEntity);
}

void OpenGLDrawer::drawBrokenLine(std::shared_ptr<FrameWork::BrokenLine> brokenLine) const
{
  OpenGLEntity newEntity;
  newEntity.shape = brokenLine;
  newEntity.drawType = GL_LINE_STRIP;

  std::vector<double> vertices;
  for (size_t i = 0; i < brokenLine->getPoints().size(); i++)
  {
    vertices.push_back(brokenLine->getPoints()[i].x());
    vertices.push_back(brokenLine->getPoints()[i].y());
    vertices.push_back(0);
  }

  newEntity.size = vertices.size() / 3;

  generateBuffers(newEntity, vertices);

  entities.push_back(newEntity);
}
