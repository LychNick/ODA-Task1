#include "Shapes.h"

namespace FrameWork
{
  Shape::Shape(std::string name) :
    name_(name)
  {
  }
  Shape::~Shape(void)
  {
  }

  std::string Shape::getName(void) const
  {
    return name_;
  }


  double getLineLength(std::vector<Point2d>& data, bool isLoop)
  {
    double length = 0;
    for (size_t i = 0; i < data.size() - 1; i++)
    {
      length += (data[i + 1] - data[i]).length();
    }
    if (isLoop)
    {
      length += (data[0] - data[data.size() - 1]).length();
    }
    return length;
  }


  Square::Square(Point2d leftDown, Point2d rightUp) :
    Shape("Square"),
    leftDown_(leftDown),
    rightUp_(rightUp)
  {
  }

  void Square::calcBoundingBox()
  {
    boundingBox_ = std::make_shared<BoundingBox>(leftDown_, rightUp_);
  }

  void Square::calcLineWidth()
  {
    Point2d diff = rightUp_ - leftDown_;
    lineWidth_ = 2 * (diff.x() + diff.y());
  }

  Circle::Circle(Point2d centerPoint, double R) :
    Shape("Circle"),
    centerPoint_(centerPoint),
    R_(R)
  {
  }

  void Circle::calcBoundingBox()
  {
    boundingBox_ = std::make_shared<BoundingBox>(centerPoint_ + Point2d(-R_, -R_),
      centerPoint_ + Point2d(R_, R_));
  }

  void Circle::calcLineWidth()
  {
    double step = 2 * M_PI / FrameWork::segmentsCount_;
    lineWidth_ = FrameWork::segmentsCount_ * R_ * sqrt(pow(1 - cos(step), 2) + pow(sin(step), 2));
  }

  Arc::Arc(Point2d centerPoint, double R, double startR, double endR) :
    Shape("Arc"),
    centerPoint_(centerPoint),
    R_(R),
    startR_(startR),
    endR_(endR)
  {
  }

  void Arc::calcBoundingBox()
  {
    double step = (endR_ - startR_) / FrameWork::segmentsCount_;
    Point2d leftDown(R_, R_);
    Point2d rightUp(-R_, -R_);
    for (double i = 0; i <= FrameWork::segmentsCount_; i++)
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

  void Arc::calcLineWidth()
  {
    double step = (endR_ - startR_) / FrameWork::segmentsCount_;
    lineWidth_ = FrameWork::segmentsCount_ * R_ * sqrt(pow(1 - cos(step), 2) + pow(sin(step), 2));
  }

  Polygon::Polygon(std::vector<Point2d> && points) :
    Shape("Polygon"),
    points_(std::move(points))
  {
  }

  void Polygon::calcBoundingBox()
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

  void Polygon::calcLineWidth()
  {
    lineWidth_ = 0;
    for (size_t i = 0; i < points_.size() - 1; i++)
    {
      lineWidth_ += (points_[i + 1] - points_[i]).length();
    }
    lineWidth_ += (points_[0] - points_[points_.size() - 1]).length();
  }

  BrokenLine::BrokenLine(std::vector<Point2d> && points) :
    Shape("BrokenLine"),
    points_(std::move(points))
  {
  }

  void BrokenLine::calcBoundingBox()
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

  void BrokenLine::calcLineWidth()
  {
    lineWidth_ = 0;
    for (size_t i = 0; i < points_.size() - 1; i++)
    {
      lineWidth_ += (points_[i + 1] - points_[i]).length();
    }
  }

  std::shared_ptr<Square> ShapeFabric::buildSquare(std::vector<double> & data)
  {
    if (data.size() != 4)
    {
      throw std::invalid_argument("bad Square data");
    }
    return std::make_shared<Square>(Point2d(data[0], data[1]), Point2d(data[2], data[3]));
  }

  std::shared_ptr<Circle> ShapeFabric::buildCircle(std::vector<double> & data)
  {
    if (data.size() != 3)
    {
      throw std::invalid_argument("bad Circle data");
    }
    return std::make_shared<Circle>(Point2d(data[0], data[1]), data[2]);
  }

  std::shared_ptr<Arc> ShapeFabric::buildArc(std::vector<double> & data)
  {
    if (data.size() != 5)
    {
      throw std::invalid_argument("bad Arc data");
    }
    return std::make_shared<Arc>(Point2d(data[0], data[1]), data[2], data[3], data[4]);
  }

  std::shared_ptr<Polygon> ShapeFabric::buildPolygon(std::vector<double> & data)
  {
    if ((data.size() % 2 != 0) || (data.size() < 3 * POINT_SIZE))
    {
      throw std::invalid_argument("bad Polygon data");
    }

    std::vector<Point2d> points;
    for (size_t i = 0; i < data.size() - 1; i += 2)
    {
      points.push_back(Point2d(data[i], data[i + 1]));
    }

    return std::make_shared<Polygon>(std::move(points));
  }

  std::shared_ptr<BrokenLine> ShapeFabric::buildBrokenLine(std::vector<double> & data)
  {
    if ((data.size() % 2 != 0) || (data.size() < 2 * POINT_SIZE))
    {
      throw std::invalid_argument("bad Polygon data");
    }

    std::vector<Point2d> points;
    for (size_t i = 0; i < data.size() - 1; i += 2)
    {
      points.push_back(Point2d(data[i], data[i + 1]));
    }

    return std::make_shared<BrokenLine>(std::move(points));
  }

  BoundingBox::BoundingBox(Point2d leftDown, Point2d rightUp) :
    leftDown_(leftDown),
    rightUp_(rightUp)
  {
  }

}
