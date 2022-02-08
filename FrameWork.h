#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataProvider.h"
#include "Exceptions.h"
#include "Shapes.h"
#include "Drawer.h"

namespace FrameWork
{
  static Drawer drawer_;

  static std::vector<std::shared_ptr<FrameWork::Shape>> baseShapes_;

  void loadShapes();
  void calcShapesParams();
  void drawShapes();

}