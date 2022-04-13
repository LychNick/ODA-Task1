#include "WDraw.h"
#include <stdio.h>


void WDraw::drawSegment (const Point2d& p1, const Point2d& p2) const 
{
  printf("(%f, %f) - (%f, %f)\n", p1.x(), p1.y(), p2.x(), p2.y());
}

void WDraw::drawPolyLine(const std::vector<Point2d>& vertices) const
{
  for (size_t i = 0; i < vertices.size() - 1; i++)
  {
    printf("(%f, %f) - (%f, %f)\n", vertices[i].x(), vertices[i].y(),
      vertices[i + 1].x(), vertices[i + 1].y());
  }
}
