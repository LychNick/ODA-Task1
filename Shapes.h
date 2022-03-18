#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

#include "Point2d.h"

namespace FrameWork
{
  const int TYPE_SQUARE = 1;
  const int TYPE_CIRCLE = 2;
  const int TYPE_ARC = 4;
  const int TYPE_POLYGON = 5;
  const int TYPE_BROKEN_LINE = 6;

  const int POINT_SIZE = 2;

  class BoundingBox
  {
    public:
    BoundingBox(const Point2d& leftDown, const Point2d& rightUp);
    Point2d getLeftDownPoint() const { return leftDown_; };
    Point2d getRightUpPoint() const { return rightUp_; };
  private:
    Point2d leftDown_;
    Point2d rightUp_;
  };

  class Shape
  {
  public:
    Shape();
    virtual ~Shape(void);

    virtual int getShapeType() const = 0;

    std::shared_ptr<BoundingBox> getBoundingBox() const;
    double getLineWidth() const;

  protected:
    virtual void calcBoundingBox() const = 0;
    virtual void calcLineWidth() const = 0;
    mutable std::shared_ptr<BoundingBox> boundingBox_;
    mutable double lineWidth_ = 0;
  };
  
  struct DrawableEntity
  {
    std::shared_ptr<FrameWork::Shape> shape;
  };

  class Square : public Shape
  {
  public:
    Square(const Point2d& leftDown, const Point2d& rightUp);
    int getShapeType() const override { return TYPE_SQUARE; };
    void calcBoundingBox() const override;
    void calcLineWidth() const override;
    Point2d getLeftDownPoint() const { return leftDown_; };
    Point2d getRightUpPoint() const { return rightUp_; };
  private:
    Point2d leftDown_;
    Point2d rightUp_;
  };

  class Circle : public Shape
  {
  public:
    Circle(const Point2d& centerPoint, double R);
    int getShapeType() const override { return TYPE_CIRCLE; };
    void calcBoundingBox() const override;
    void calcLineWidth() const override;
    Point2d getCenterPoint() const { return centerPoint_; };
    double getR() const { return R_; };
    int getSegmentsCount() const;
  private:
    Point2d centerPoint_;
    double R_;
  };

  class Arc : public Shape
  {
  public:
    Arc(const Point2d& centerPoint, double R, double startR, double endR);
    int getShapeType() const override { return TYPE_ARC; };
    void calcBoundingBox() const override;
    void calcLineWidth() const override;
    Point2d getCenterPoint() const { return centerPoint_; };
    double getR() const { return R_; };
    double getStartR() const { return startR_; };
    double getEndR() const { return endR_; };
    int getSegmentsCount() const;
  private:
    Point2d centerPoint_;
    double R_;
    double startR_;
    double endR_;
  };

  class Polygon : public Shape
  {
  public:
    Polygon(const std::vector<Point2d>& points);
    Polygon(std::vector<Point2d>&& points);
    int getShapeType() const override { return TYPE_POLYGON; };
    void calcBoundingBox() const override;
    void calcLineWidth() const override;
    std::vector<Point2d> getPoints() const { return points_; };
  private:
    std::vector<Point2d> points_;
  };

  class BrokenLine : public Shape
  {
  public:
    BrokenLine(const std::vector<Point2d>& points);
    BrokenLine(std::vector<Point2d>&& points);
    int getShapeType() const override { return TYPE_BROKEN_LINE; };
    void calcBoundingBox() const override;
    void calcLineWidth() const override;
    std::vector<Point2d> getPoints() const { return points_; };
  private:
    std::vector<Point2d> points_;
  };


  class ShapeFactory //Reader
  {
  public:
    static std::shared_ptr<Square> buildSquare(const std::vector<double>& data);
    static std::shared_ptr<Circle> buildCircle(const std::vector<double>& data);
    static std::shared_ptr<Arc> buildArc(const std::vector<double>& data);
    static std::shared_ptr<Polygon> buildPolygon(const std::vector<double>& data);
    static std::shared_ptr<BrokenLine> buildBrokenLine(const std::vector<double>& data);
    static std::shared_ptr<Shape> buildShape(const int& type, const std::vector<double>& data);
  };
}
