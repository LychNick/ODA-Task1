#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <mutex>

#include "Draw.h"
#include "Exceptions.h"

#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32.lib")

void drawFunc();
void mouseWheel(int button, int dir, int x, int y);
void mouseState(int button, int state, int x, int y);

const std::string getGLError(const std::string& file, GLuint line);

class OpenGLDraw: public Draw
{
public:
  OpenGLDraw();
  ~OpenGLDraw();

  void createWindow(const glm::vec2& params, const std::string& name) const;

  void drawSegment(const Point2d& p1, const Point2d& p2) const override;
  void drawPolyLine(const std::vector<Point2d>& vertices) const override;

  void initLoop();
private:
  GLuint createShader(GLuint type, const std::wstring& file) const;
  GLuint createShaderProgram(const std::vector<GLuint>& shaders) const;
  GLuint createShaderPair(const std::wstring& fragmentShader, const std::wstring& vertexShader) const;
  void setCurrentDir();
  void openGLInit() const;
  mutable GLuint windowHandler_ = 0;
  std::wstring mainDir_;
};