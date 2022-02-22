#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Shapes.h"
#include "WDraw.h"

class Drawer
{
public:
  Drawer();
  virtual ~Drawer();
  virtual void drawBoundingBox(std::shared_ptr<FrameWork::BoundingBox> box) const;
  virtual void drawSquare(std::shared_ptr<FrameWork::Square> square) const;
  virtual void drawCircle(std::shared_ptr<FrameWork::Circle> circle) const;
  virtual void drawArc(std::shared_ptr<FrameWork::Arc> arc) const;
  virtual void drawPolygon(std::shared_ptr<FrameWork::Polygon> polygon) const;
  virtual void drawBrokenLine(std::shared_ptr<FrameWork::BrokenLine> brokenLine) const;
  void drawShape(std::shared_ptr<FrameWork::Shape> shape);
private:
  WDraw wdraw_;
};
