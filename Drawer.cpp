#include "Drawer.h"

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
}

void Drawer::drawBoundingBox(std::shared_ptr<FrameWork::BoundingBox> box) const
{
  Point2d leftDown = box->getLeftDownPoint();
  Point2d rightUp = box->getRightUpPoint();
  wdraw_.drawText("Drawing BoundingBox:");
  wdraw_.drawSegment(leftDown, Point2d(leftDown.x(), rightUp.y()));
  wdraw_.drawSegment(Point2d(leftDown.x(), rightUp.y()), rightUp);
  wdraw_.drawSegment(rightUp, Point2d(rightUp.x(), leftDown.y()));
  wdraw_.drawSegment(Point2d(rightUp.x(), leftDown.y()), leftDown);
}

void Drawer::drawSquare(std::shared_ptr<FrameWork::Square> square) const
{
  Point2d leftDown = square->getLeftDownPoint();
  Point2d rightUp = square->getRightUpPoint();
  wdraw_.drawText("Drawing Square:");
  wdraw_.drawSegment(leftDown, Point2d(leftDown.x(), rightUp.y()));
  wdraw_.drawSegment(Point2d(leftDown.x(), rightUp.y()), rightUp);
  wdraw_.drawSegment(rightUp, Point2d(rightUp.x(), leftDown.y()));
  wdraw_.drawSegment(Point2d(rightUp.x(), leftDown.y()), leftDown);
  wdraw_.drawText(("Line width: " 
    + std::to_string(square->getLineWidth())).c_str());
}

void Drawer::drawCircle(std::shared_ptr<FrameWork::Circle> circle) const
{
  wdraw_.drawText("Drawing Circle:");
  double R = circle->getR();
  Point2d centerPoint = circle->getCenterPoint();
  double step = 2 * M_PI / FrameWork::segmentsCount;
  for (double i = 0; i < FrameWork::segmentsCount; i++)
  {
    wdraw_.drawSegment(centerPoint + Point2d(R * cos(step * i), R * sin(step * i)),
      centerPoint + Point2d(R * cos(step * (i + 1)), R * sin(step * (i + 1))));
  }
  wdraw_.drawText(("Line width: "
    + std::to_string(circle->getLineWidth())).c_str());
}

void Drawer::drawArc(std::shared_ptr<FrameWork::Arc> arc) const
{
  wdraw_.drawText("Drawing Arc:");
  double R = arc->getR();
  Point2d centerPoint = arc->getCenterPoint();
  double startR = arc->getStartR();
  double endR = arc->getEndR();
  double step = (endR - startR) / FrameWork::segmentsCount;
  for (double i = 0; i < FrameWork::segmentsCount; i++)
  {
    wdraw_.drawSegment(centerPoint + Point2d(R * cos(startR + step * i), R * sin(startR + step * i)),
      centerPoint + Point2d(R * cos(step * (i + 1)), R * sin(step * (i + 1))));
  }
  wdraw_.drawText(("Line width: "
    + std::to_string(arc->getLineWidth())).c_str());
}

void Drawer::drawPolygon(std::shared_ptr<FrameWork::Polygon> polygon) const
{
  wdraw_.drawText("Drawing Polygon:");
  for (size_t i = 0; i < polygon->getPoints().size() - 1; i++)
  {
    wdraw_.drawSegment(polygon->getPoints()[i], polygon->getPoints()[i + 1]);
  }
  wdraw_.drawSegment(polygon->getPoints()[polygon->getPoints().size()-1], 
    polygon->getPoints()[0]);
  wdraw_.drawText(("Line width: "
    + std::to_string(polygon->getLineWidth())).c_str());
}

void Drawer::drawBrokenLine(std::shared_ptr<FrameWork::BrokenLine> brokenLine) const
{
  wdraw_.drawText("Drawing BrokenLine:");
  for (size_t i = 0; i < brokenLine->getPoints().size() - 1; i++)
  {
    wdraw_.drawSegment(brokenLine->getPoints()[i], brokenLine->getPoints()[i + 1]);
  }
  wdraw_.drawText(("Line width: "
    + std::to_string(brokenLine->getLineWidth())).c_str());
}

void Drawer::drawShape(std::shared_ptr<FrameWork::Shape> shape)
{
  switch (shape->getShapeType())
  {
  case FrameWork::TYPE_SQUARE:
  {
    drawSquare(std::static_pointer_cast<FrameWork::Square>(shape));
    break;
  }
  case FrameWork::TYPE_CIRCLE:
  {
    drawCircle(std::static_pointer_cast<FrameWork::Circle>(shape));
    break;
  }
  case FrameWork::TYPE_ARC:
  {
    drawArc(std::static_pointer_cast<FrameWork::Arc>(shape));
    break;
  }
  case FrameWork::TYPE_POLYGON:
  {
    drawPolygon(std::static_pointer_cast<FrameWork::Polygon>(shape));
    break;
  }
  case FrameWork::TYPE_BROKEN_LINE:
  {
    drawBrokenLine(std::static_pointer_cast<FrameWork::BrokenLine>(shape));
    break;
  }
  default:
    break;
  }
}
