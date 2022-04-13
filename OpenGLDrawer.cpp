#include "OpenGLDrawer.h"


OpenGLDrawer::OpenGLDrawer()
{
  draw_ = std::make_shared<OpenGLDraw>();
}

void OpenGLDrawer::drawShapes(const std::vector<std::shared_ptr<FrameWork::Shape>>& shapes) const
{
  draw_->createWindow(glm::vec2(800, 600), "Task2");
  for (size_t i = 0; i < shapes.size(); i++) 
  {
    drawShape(draw_, shapes[i]);
  }
  draw_->initLoop();
}
