#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <tchar.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Point2d.h"
#include "Shapes.h"
#include "Exceptions.h"

#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32.lib")

struct OpenGLEntity : public FrameWork::DrawableEntity 
{
  GLuint VAO = -1;
  GLuint drawType = -1;
  GLuint size = 0;
  glm::vec4 color = glm::vec4(glm::vec3(0), 1.f);
};

extern glm::vec2 winParams;

class OpenGLWorker
{
public:
  OpenGLWorker(void);
  ~OpenGLWorker(void);

  void setCurrentDir();
  void openGLInit() const;
  void setupWindowParams(const glm::vec2& params) { winParams = params; };
  void createWindow(const std::string& name) const;
  void drawEntity(const OpenGLEntity& entity) const;
  void checkGLError(const std::string& file, GLuint line) const;

  GLfloat globalScale = 1.f;
  glm::mat4 Translate = glm::mat4(1.f);
private:
  mutable GLuint windowHandler_ = 0;
  mutable GLuint mainShader_ = 0;
  mutable glm::mat4 OMVP_;
  std::wstring mainDir_;
};

