#include "Shapes.h"

namespace FrameWork
{
  const double normsSegments_ = 4;

  Shape::Shape()
  {
  }
  Shape::~Shape(void)
  {
  }

  std::shared_ptr<BoundingBox> Shape::getBoundingBox() const
  {
    calcBoundingBox();
    return boundingBox_;
  }

  double Shape::getLineWidth() const
  {
    calcLineWidth();
    return lineWidth_;
  }


  Square::Square(const Point2d& leftDown, const Point2d& rightUp) :
    Shape(),
    leftDown_(leftDown),
    rightUp_(rightUp)
  {
  }

  void Square::calcBoundingBox() const
  {
    boundingBox_ = std::make_shared<BoundingBox>(leftDown_, rightUp_);
  }

  void Square::calcLineWidth() const
  {
    Point2d diff = rightUp_ - leftDown_;
    lineWidth_ = 2 * (diff.x() + diff.y());
  }

  Circle::Circle(const Point2d& centerPoint, double R) :
    Shape(),
    centerPoint_(centerPoint),
    R_(R)
  {
  }

  void Circle::calcBoundingBox() const
  {
    boundingBox_ = std::make_shared<BoundingBox>(centerPoint_ + Point2d(-R_, -R_),
      centerPoint_ + Point2d(R_, R_));
  }

  void Circle::calcLineWidth() const
  {
    int segmentsCount = getSegmentsCount();
    double step = 2 * M_PI / segmentsCount;
    lineWidth_ = segmentsCount * R_ * sqrt(pow(1 - cos(step), 2) + pow(sin(step), 2));
  }

  int Circle::getSegmentsCount() const
  {
    return static_cast<int>(normsSegments_ * R_);
  }

  Arc::Arc(const Point2d& centerPoint, double R, double startR, double endR) :
    Shape(),
    centerPoint_(centerPoint),
    R_(R),
    startR_(startR),
    endR_(endR)
  {
  }

  void Arc::calcBoundingBox() const
  {
    int segmentsCount = getSegmentsCount();
    double step = (endR_ - startR_) / segmentsCount;
    Point2d leftDown = centerPoint_ + Point2d(R_, R_);
    Point2d rightUp = centerPoint_ - Point2d(R_, R_);
    for (double i = 0; i <= segmentsCount; i++)
    {
      Point2d point = centerPoint_ + Point2d(R_ * cos(startR_ + step * i),
        R_ * sin(startR_ + step * i));
      if (point.x() < leftDown.x())
      {
        leftDown.setX(point.x());
      }
      if (point.x() > rightUp.x())
      {
        rightUp.setX(point.x());
      }
      if (point.y() < leftDown.y())
      {
        leftDown.setY(point.y());
      }
      if (point.y() > rightUp.y())
      {
        rightUp.setY(point.y());
      }
    }
    boundingBox_ = std::make_shared<BoundingBox>(leftDown, rightUp);
  }

  void Arc::calcLineWidth() const
  {
    int segmentsCount = getSegmentsCount();
    double step = (endR_ - startR_) / segmentsCount;
    lineWidth_ = segmentsCount * R_ * sqrt(pow(1 - cos(step), 2) + pow(sin(step), 2));
  }

  int Arc::getSegmentsCount() const
  {
    return static_cast<int>(normsSegments_ * R_);
  }

  Polygon::Polygon(const std::vector<Point2d>& points) :
    Shape(),
    points_(points)
  {
  }

  Polygon::Polygon(std::vector<Point2d> && points) :
    Shape(),
    points_(std::move(points))
  {
  }

  void Polygon::calcBoundingBox() const
  {
    Point2d leftDown = points_[0];
    Point2d rightUp = points_[0];
    for (size_t i = 1; i < points_.size(); i++)
    {
      if (points_[i].x() < leftDown.x())
      {
        leftDown.setX(points_[i].x());
      }
      if (points_[i].x() > rightUp.x())
      {
        rightUp.setX(points_[i].x());
      }
      if (points_[i].y() < leftDown.y())
      {
        leftDown.setY(points_[i].y());
      }
      if (points_[i].y() > rightUp.y())
      {
        rightUp.setY(points_[i].y());
      }
    }
    boundingBox_ = std::make_shared<BoundingBox>(leftDown, rightUp);
  }

  void Polygon::calcLineWidth() const
  {
    lineWidth_ = 0;
    for (size_t i = 0; i < points_.size() - 1; i++)
    {
      lineWidth_ += (points_[i + 1] - points_[i]).length();
    }
    lineWidth_ += (points_[0] - points_[points_.size() - 1]).length();
  }

  BrokenLine::BrokenLine(const std::vector<Point2d>& points) :
    Shape(),
    points_(points)
  {
  }

  BrokenLine::BrokenLine(std::vector<Point2d> && points) :
    Shape(),
    points_(std::move(points))
  {
  }

  void BrokenLine::calcBoundingBox() const
  {
    Point2d leftDown = points_[0];
    Point2d rightUp = points_[0];
    for (size_t i = 1; i < points_.size(); i++)
    {
      if (points_[i].x() < leftDown.x())
      {
        leftDown.setX(points_[i].x());
      }
      if (points_[i].x() > rightUp.x())
      {
        rightUp.setX(points_[i].x());
      }
      if (points_[i].y() < leftDown.y())
      {
        leftDown.setY(points_[i].y());
      }
      if (points_[i].y() > rightUp.y())
      {
        rightUp.setY(points_[i].y());
      }
    }
    boundingBox_ = std::make_shared<BoundingBox>(leftDown, rightUp);
  }

  void BrokenLine::calcLineWidth() const
  {
    lineWidth_ = 0;
    for (size_t i = 0; i < points_.size() - 1; i++)
    {
      lineWidth_ += (points_[i + 1] - points_[i]).length();
    }
  }

  std::shared_ptr<Square> ShapeFactory::buildSquare(const std::vector<double> & data)
  {
    if (data.size() != 4)
    {
      printf("%s\n", "Bad square data");
      return nullptr;
    }
    return std::make_shared<Square>(Point2d(data[0], data[1]), Point2d(data[2], data[3]));
  }

  std::shared_ptr<Circle> ShapeFactory::buildCircle(const std::vector<double> & data)
  {
    if (data.size() != 3)
    {
      printf("%s\n", "Bad Circle data");
      return nullptr;
    }
    return std::make_shared<Circle>(Point2d(data[0], data[1]), data[2]);
  }

  std::shared_ptr<Arc> ShapeFactory::buildArc(const std::vector<double> & data)
  {
    if (data.size() != 5)
    {
      printf("%s\n", "Bad Arc data");
      return nullptr;
    }
    return std::make_shared<Arc>(Point2d(data[0], data[1]), data[2], data[3], data[4]);
  }

  std::shared_ptr<Polygon> ShapeFactory::buildPolygon(const std::vector<double> & data)
  {
    if ((data.size() % 2 != 0) || (data.size() < 3 * POINT_SIZE))
    {
      printf("%s\n", "Bad Polygon data");
      return nullptr;
    }

    std::vector<Point2d> points;
    for (size_t i = 0; i < data.size() - 1; i += 2)
    {
      points.push_back(Point2d(data[i], data[i + 1]));
    }

    return std::make_shared<Polygon>(std::move(points));
  }

  std::shared_ptr<BrokenLine> ShapeFactory::buildBrokenLine(const std::vector<double> & data)
  {
    if ((data.size() % 2 != 0) || (data.size() < 2 * POINT_SIZE))
    {
      printf("%s\n", "Bad Broken Line data");
      return nullptr;
    }

    std::vector<Point2d> points;
    for (size_t i = 0; i < data.size() - 1; i += 2)
    {
      points.push_back(Point2d(data[i], data[i + 1]));
    }

    return std::make_shared<BrokenLine>(std::move(points));
  }

  std::shared_ptr<Shape> ShapeFactory::buildShape(const int& type, const std::vector<double>& data)
  {
    switch (type)
    {
    case TYPE_SQUARE:
    {
      return ShapeFactory::buildSquare(data);
      break;
    }
    case TYPE_CIRCLE:
    {
      return ShapeFactory::buildCircle(data);
      break;
    }
    case TYPE_ARC:
    {
      return ShapeFactory::buildArc(data);
      break;
    }
    case TYPE_POLYGON:
    {
      return ShapeFactory::buildPolygon(data);
      break;
    }
    case TYPE_BROKEN_LINE:
    {
      return ShapeFactory::buildBrokenLine(data);
      break;
    }
    default:
      printf("%s\n", "Unknown shape");
      return nullptr;
      break;
    }
  }

  BoundingBox::BoundingBox(const Point2d& leftDown, const Point2d& rightUp) :
    leftDown_(leftDown),
    rightUp_(rightUp)
  {
  }

  const std::vector<double> Exporter::exportSquare(std::shared_ptr<Square> square)
  {
    std::vector<double> data(4);

    const Point2d& leftDown = square->getLeftDownPoint();
    const Point2d& rightUp = square->getRightUpPoint();
    data[0] = leftDown.x();
    data[1] = leftDown.y();
    data[2] = rightUp.x();
    data[3] = rightUp.y();

    return data;
  }

  const std::vector<double> Exporter::exportCircle(std::shared_ptr<Circle> circle)
  {
    std::vector<double> data(3);

    const Point2d& center = circle->getCenterPoint();
    double R = circle->getR();
    data[0] = center.x();
    data[1] = center.y();
    data[2] = R;

    return data;
  }

  const std::vector<double> Exporter::exportArc(std::shared_ptr<Arc> arc)
  {
    std::vector<double> data(5);

    const Point2d& center = arc->getCenterPoint();
    double R = arc->getR();
    double startR = arc->getStartR();
    double endR = arc->getEndR();
    data[0] = center.x();
    data[1] = center.y();
    data[2] = R;
    data[3] = startR;
    data[4] = endR;

    return data;
  }

  const std::vector<double> Exporter::exportPolygon(std::shared_ptr<Polygon> polygon)
  {
    const std::vector<Point2d>& points = polygon->getPoints();
    std::vector<double> data(points.size() * 2);
    int j = 0;
    for (int i = 0; i < points.size(); i++, j += 2)
    {
      data[j] = points[i].x();
      data[j + 1] = points[i].y();
    }
    return data;
  }

  const std::vector<double> Exporter::exportBrokenLine(std::shared_ptr<BrokenLine> brokenLine)
  {
    const std::vector<Point2d>& points = brokenLine->getPoints();
    std::vector<double> data(points.size() * 2);
    int j = 0;
    for (int i = 0; i < points.size(); i++, j += 2)
    {
      data[j] = points[i].x();
      data[j + 1] = points[i].y();
    }
    return data;
  }

  const std::vector<double> Exporter::exportShape(std::shared_ptr<Shape> shape)
  {
    if (shape)
    {
      switch (shape->getShapeType())
      {
      case TYPE_SQUARE:
      {
        return exportSquare(std::static_pointer_cast<FrameWork::Square>(shape));
        break;
      }
      case TYPE_CIRCLE:
      {
        return exportCircle(std::static_pointer_cast<FrameWork::Circle>(shape));
        break;
      }
      case TYPE_ARC:
      {
        return exportArc(std::static_pointer_cast<FrameWork::Arc>(shape));
        break;
      }
      case TYPE_POLYGON:
      {
        return exportPolygon(std::static_pointer_cast<FrameWork::Polygon>(shape));
        break;
      }
      case TYPE_BROKEN_LINE:
      {
        return exportBrokenLine(std::static_pointer_cast<FrameWork::BrokenLine>(shape));
        break;
      }
      default:
        break;
      }
    }
  }
}
