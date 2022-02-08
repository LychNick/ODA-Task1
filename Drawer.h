#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Shapes.h"
#include "WDraw.h"

class Drawer
{
public:
  Drawer();
  ~Drawer();
  void drawBoundingBox(std::shared_ptr<FrameWork::BoundingBox> box) const;
  void drawSquare(std::shared_ptr<FrameWork::Square> square) const;
  void drawCircle(std::shared_ptr<FrameWork::Circle> circle) const;
  void drawArc(std::shared_ptr<FrameWork::Arc> arc) const;
  void drawPolygon(std::shared_ptr<FrameWork::Polygon> polygon);
  void drawBrokenLine(std::shared_ptr<FrameWork::BrokenLine> brokenLine) const;
private:
  WDraw wdraw_;
};

