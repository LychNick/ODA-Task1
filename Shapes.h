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
  double getLineLength(std::vector<Point2d>& data, bool isLoop);

  const int TYPE_SQUARE = 1;
  const int TYPE_CIRCLE = 2;
  const int TYPE_ARC = 4;
  const int TYPE_POLYGON = 5;
  const int TYPE_BROKEN_LINE = 6;

  const int POINT_SIZE = 2;

  const size_t segmentsCount_ = 4;

  class BoundingBox
  {
    public:
    BoundingBox(Point2d leftDown, Point2d rightUp);
    Point2d getLeftDownPoint() const { return leftDown_; };
    Point2d getRightUpPoint() const { return rightUp_; };
  private:
    Point2d leftDown_;
    Point2d rightUp_;
  };

  class Shape
  {
  public:
    Shape(std::string name);
    virtual ~Shape(void);

    virtual void calcBoundingBox() = 0;
    virtual void calcLineWidth() = 0;

    virtual int getShapeType() const = 0;
    std::string getName(void) const;
    std::shared_ptr<BoundingBox> getBoundingBox() const
    { return boundingBox_; };
    double getLineWidth() const { return lineWidth_; };
  private:
    std::string name_;
  protected:
    std::shared_ptr<BoundingBox> boundingBox_;
    double lineWidth_ = 0;
  };


  class Square : public Shape
  {
  public:
    Square(Point2d leftDown, Point2d rightUp);
    int getShapeType() const override { return TYPE_SQUARE; };
    void calcBoundingBox() override;
    void calcLineWidth() override;
    Point2d getLeftDownPoint() const { return leftDown_; };
    Point2d getRightUpPoint() const { return rightUp_; };
  private:
    Point2d leftDown_;
    Point2d rightUp_;
  };

  class Circle : public Shape
  {
  public:
    Circle(Point2d centerPoint, double R);
    int getShapeType() const override { return TYPE_CIRCLE; };
    void calcBoundingBox() override;
    void calcLineWidth() override;
    Point2d getCenterPoint() const { return centerPoint_; };
    double getR() const { return R_; };
  private:
    Point2d centerPoint_;
    double R_;
  };

  class Arc : public Shape
  {
  public:
    Arc(Point2d centerPoint, double R, double startR, double endR);
    int getShapeType() const override { return TYPE_ARC; };
    void calcBoundingBox() override;
    void calcLineWidth() override;
    Point2d getCenterPoint() const { return centerPoint_; };
    double getR() const { return R_; };
    double getStartR() const { return startR_; };
    double getEndR() const { return endR_; };
  private:
    Point2d centerPoint_;
    double R_;
    double startR_;
    double endR_;
  };

  class Polygon : public Shape
  {
  public:
    Polygon(std::vector<Point2d>&& points);
    int getShapeType() const override { return TYPE_POLYGON; };
    void calcBoundingBox() override;
    void calcLineWidth() override;
    std::vector<Point2d> getPoints() const { return points_; };
  private:
    std::vector<Point2d> points_;
  };

  class BrokenLine : public Shape
  {
  public:
    BrokenLine(std::vector<Point2d>&& points);
    int getShapeType() const override { return TYPE_BROKEN_LINE; };
    void calcBoundingBox() override;
    void calcLineWidth() override;
    std::vector<Point2d> getPoints() const { return points_; };
  private:
    std::vector<Point2d> points_;
  };


  class ShapeFabric //Reader
  {
  public:
    static std::shared_ptr<Square> buildSquare(std::vector<double>& data);
    static std::shared_ptr<Circle> buildCircle(std::vector<double>& data);
    static std::shared_ptr<Arc> buildArc(std::vector<double>& data);
    static std::shared_ptr<Polygon> buildPolygon(std::vector<double>& data);
    static std::shared_ptr<BrokenLine> buildBrokenLine(std::vector<double>& data);
  };
}
