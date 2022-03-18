#pragma once

#include "Draw.h"

class WDraw : public Draw
{
public:
  void drawSegment(const Point2d& p1, const Point2d& p2) const override;
  void drawPolyLine(const std::vector<Point2d>& vertices) const override;
};
