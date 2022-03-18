#include "Drawer.h"

void Drawer::drawBoundingBox(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::BoundingBox> box) const
{
  Point2d leftDown = box->getLeftDownPoint();
  Point2d rightUp = box->getRightUpPoint();

  std::vector<Point2d> vertices;

  vertices.push_back(leftDown);
  vertices.push_back({leftDown.x(), rightUp.y()});
  vertices.push_back(rightUp);
  vertices.push_back({rightUp.x(), leftDown.y()});
  vertices.push_back(leftDown);

  draw->drawText("BoundingBox:");
  draw->drawPolyLine(vertices);
}

void Drawer::drawSquare(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Square> square) const
{
  Point2d leftDown = square->getLeftDownPoint();
  Point2d rightUp = square->getRightUpPoint();

  std::vector<Point2d> vertices;

  vertices.push_back(leftDown);
  vertices.push_back({leftDown.x(), rightUp.y()});
  vertices.push_back(rightUp);
  vertices.push_back({rightUp.x(), leftDown.y()});
  vertices.push_back(leftDown);

  draw->drawText("Square:");
  draw->drawPolyLine(vertices);
}

void Drawer::drawCircle(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Circle> circle) const
{
  std::vector<Point2d> vertices;

  double R = circle->getR();
  Point2d centerPoint = circle->getCenterPoint();

  double segmentsCount = circle->getSegmentsCount() * detailing_;

  double step = 2 * M_PI / segmentsCount;
  for (double i = 0; i <= segmentsCount; i++)
  {
    vertices.push_back(Point2d(centerPoint + Point2d(R * cos(step * i), R * sin(step * i))));
  }

  draw->drawText("Circle:");
  draw->drawPolyLine(vertices);
}

void Drawer::drawArc(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Arc> arc) const
{

  std::vector<Point2d> vertices;

  double R = arc->getR();
  Point2d centerPoint = arc->getCenterPoint();
  double startR = arc->getStartR();
  double endR = arc->getEndR();

  double segmentsCount = arc->getSegmentsCount() * detailing_;

  double step = (endR - startR) / segmentsCount;
  for (double i = 0; i <= segmentsCount; i++)
  {
    vertices.push_back(Point2d(centerPoint + Point2d(R * cos(startR + step * i), 
      R * sin(startR + step * i))));
  }

  draw->drawText("Arc:");
  draw->drawPolyLine(vertices);
}

void Drawer::drawPolygon(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Polygon> polygon) const
{
  draw->drawText("Polygon:");
  draw->drawPolyLine(polygon->getPoints());
}

void Drawer::drawBrokenLine(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::BrokenLine> brokenLine) const
{
  draw->drawText("BrokenLine:");
  draw->drawPolyLine(brokenLine->getPoints());
}

void Drawer::drawShape(std::shared_ptr<Draw> draw,
  std::shared_ptr<FrameWork::Shape> shape) const
{
  switch (shape->getShapeType())
  {
  case FrameWork::TYPE_SQUARE:
  {
    drawSquare(draw, std::static_pointer_cast<FrameWork::Square>(shape));
    drawBoundingBox(draw, shape->getBoundingBox());
    break;
  }
  case FrameWork::TYPE_CIRCLE:
  {
    drawCircle(draw, std::static_pointer_cast<FrameWork::Circle>(shape));
    drawBoundingBox(draw, shape->getBoundingBox());
    break;
  }
  case FrameWork::TYPE_ARC:
  {
    drawArc(draw, std::static_pointer_cast<FrameWork::Arc>(shape));
    drawBoundingBox(draw, shape->getBoundingBox());
    break;
  }
  case FrameWork::TYPE_POLYGON:
  {
    drawPolygon(draw, std::static_pointer_cast<FrameWork::Polygon>(shape));
    drawBoundingBox(draw, shape->getBoundingBox());
    break;
  }
  case FrameWork::TYPE_BROKEN_LINE:
  {
    drawBrokenLine(draw, std::static_pointer_cast<FrameWork::BrokenLine>(shape));
    drawBoundingBox(draw, shape->getBoundingBox());
    break;
  }
  default:
    break;
  }
}

void Drawer::setupDetailing(double detailing)
{
  detailing_ = detailing;
}
