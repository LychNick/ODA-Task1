#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataProvider.h"
#include "Exceptions.h"
#include "Shapes.h"
#include "Drawer.h"
#include "Loader.h"

//#include "OpenGLDrawer.h"

namespace FrameWork
{
  static std::vector<std::shared_ptr<FrameWork::Shape>> baseShapes_;

  void loadShapes(const std::unique_ptr<Loader> loader);
  void drawShapes(const std::unique_ptr<Drawer> drawer, double detailing);

}