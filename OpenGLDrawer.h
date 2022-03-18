#pragma once

#include "Drawer.h"
#include "OpenGLDraw.h"

class OpenGLDrawer: public Drawer
{
public:
  OpenGLDrawer();
  void drawShapes(const std::vector<std::shared_ptr<FrameWork::Shape>>& shapes) const override;
private:
  std::shared_ptr<OpenGLDraw> draw_;
};

