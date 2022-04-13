#include "Drawer.h"

void Drawer::drawBoundingBox(const Draw& draw, const std::shared_ptr<FrameWork::BoundingBox> box) const
{
  const Point2d& leftDown = box->getLeftDownPoint();
  const Point2d& rightUp = box->getRightUpPoint();

  std::vector<Point2d> vertices{
    leftDown,
    {leftDown.x(), rightUp.y()}, 
    rightUp, 
    {rightUp.x(), leftDown.y()}, 
    leftDown
  };

  draw.drawText("BoundingBox:");
  draw.drawPolyLine(vertices);
}

void Drawer::drawSquare(const Draw& draw, const std::shared_ptr<FrameWork::Square> square) const
{
  const Point2d& leftDown = square->getLeftDownPoint();
  const Point2d& rightUp = square->getRightUpPoint();

  std::vector<Point2d> vertices{
    leftDown,
    {leftDown.x(), rightUp.y()},
    rightUp,
    {rightUp.x(), leftDown.y()},
    leftDown
  };

  draw.drawText("Square:");
  draw.drawPolyLine(vertices);
}

void Drawer::drawCircle(const Draw& draw, const std::shared_ptr<FrameWork::Circle> circle) const
{
  double R = circle->getR();
  const Point2d& centerPoint = circle->getCenterPoint();

  int segmentsCount = static_cast<int>(circle->getSegmentsCount() * detailing_);

  double step = 2 * M_PI / segmentsCount;

  std::vector<Point2d> vertices(segmentsCount + 1);
  for (int i = 0; i <= segmentsCount; i++)
  {
    vertices[i] = Point2d(centerPoint + Point2d(R * cos(step * i), R * sin(step * i)));
  }

  draw.drawText("Circle:");
  draw.drawPolyLine(vertices);
}

void Drawer::drawArc(const Draw& draw, const std::shared_ptr<FrameWork::Arc> arc) const
{
  double R = arc->getR();
  const Point2d& centerPoint = arc->getCenterPoint();
  double startR = arc->getStartR();
  double endR = arc->getEndR();

  int segmentsCount = static_cast<int>(arc->getSegmentsCount() * detailing_);

  double step = (endR - startR) / segmentsCount;

  std::vector<Point2d> vertices(segmentsCount + 1);
  for (int i = 0; i <= segmentsCount; i++)
  {
    vertices[i] = Point2d(centerPoint + Point2d(R * cos(startR + step * i), 
      R * sin(startR + step * i)));
  }

  draw.drawText("Arc:");
  draw.drawPolyLine(vertices);
}

void Drawer::drawPolygon(const Draw& draw, const std::shared_ptr<FrameWork::Polygon> polygon) const
{
  draw.drawText("Polygon:");
  draw.drawPolyLine(polygon->getPoints());
}

void Drawer::drawBrokenLine(const Draw& draw, const std::shared_ptr<FrameWork::BrokenLine> brokenLine) const
{
  draw.drawText("BrokenLine:");
  draw.drawPolyLine(brokenLine->getPoints());
}

void Drawer::drawShape(const Draw& draw,
  std::shared_ptr<FrameWork::Shape> shape) const
{
  switch (shape->getShapeType())
  {
  case FrameWork::TYPE_SQUARE:
  {
    drawSquare(draw, std::static_pointer_cast<FrameWork::Square>(shape));
    break;
  }
  case FrameWork::TYPE_CIRCLE:
  {
    drawCircle(draw, std::static_pointer_cast<FrameWork::Circle>(shape));
    break;
  }
  case FrameWork::TYPE_ARC:
  {
    drawArc(draw, std::static_pointer_cast<FrameWork::Arc>(shape));
    break;
  }
  case FrameWork::TYPE_POLYGON:
  {
    drawPolygon(draw, std::static_pointer_cast<FrameWork::Polygon>(shape));
    break;
  }
  case FrameWork::TYPE_BROKEN_LINE:
  {
    drawBrokenLine(draw, std::static_pointer_cast<FrameWork::BrokenLine>(shape));
    break;
  }
  default:
    break;
  }
  drawBoundingBox(draw, shape->getBoundingBox());
}

void Drawer::drawShapes(const Draw& draw, const std::vector<std::shared_ptr<FrameWork::Shape>>& shapes) const
{
  for (size_t i = 0; i < shapes.size(); i++)
  {
    drawShape(draw, shapes[i]);
  }
}

void Drawer::setupDetailing(double detailing) const
{
  detailing_ = detailing;
}
