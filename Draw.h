#pragma once

#include "Point2d.h"
#include <vector>

class Draw 
{
public:
  Draw(void) = default;
  virtual ~Draw(void) = default;

  virtual void drawSegment(const Point2d& p1, const Point2d& p2) const = 0;

  virtual void drawPolyLine(const std::vector<Point2d>& vertices) const = 0;

  virtual void drawText(const char* text) const;
};