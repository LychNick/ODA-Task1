#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataProvider.h"
#include "DataExporter.h"
#include "Exceptions.h"
#include "Shapes.h"
#include "Drawer.h"
#include "Loader.h"

#include "OpenGLDraw.h"

namespace FrameWork
{
  static const Drawer drawer;

  void loadShapes(const DataProvider& dataProvider);
  void saveShapes(const DataExporter& dataExporter);
  void drawShapes(const Draw& draw, double detailing);
  void addShape(const std::shared_ptr<FrameWork::Shape> shape);

  void drawShape(const Draw& draw, std::shared_ptr<Shape> shape, double detailing);

}