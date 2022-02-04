#pragma once

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

  class Shape
  {
  public:
    Shape(std::string name);
    virtual ~Shape(void);

    std::vector<double> getFileData() const;

    virtual int getShapeType() = 0;

    virtual void draw(void) = 0;
    std::string getName(void);
  private:
    std::string name_;
  protected:
    std::vector<double> fileData_;
    std::vector<Point2d> data_;
  };


  class BoundingBox : public Shape
  {
    public:
    BoundingBox();
    BoundingBox(std::vector<Point2d>& data);
    void draw(void) override;
    int getShapeType() override { return -1; };
    Point2d leftDownPoint_;
    Point2d rightUpPoint_;
  };

  class Square : public Shape
  {
  public:
    Square(Point2d leftDown, Point2d rightUp);
    Square(std::vector<double> data);
    void draw(void) override;
    int getShapeType() override { return TYPE_SQUARE; };
    BoundingBox boundingBox_;
  private:
    int shapeType_ = 1;
  };

  class Circle : public Shape
  {
  public:
    Circle(std::vector<double> data);
    void draw(void) override;
    int getShapeType() override { return TYPE_CIRCLE; };
    BoundingBox boundingBox_;
  private:
  };

  class Arc : public Shape
  {
  public:
    Arc(std::vector<double> data);
    void draw(void) override;
    int getShapeType() override { return TYPE_ARC; };
    BoundingBox boundingBox_;
  private:
  };

  class Polygon : public Shape
  {
  public:
    Polygon(std::vector<double> data);
    void draw(void) override;
    int getShapeType() override { return TYPE_POLYGON; };
    BoundingBox boundingBox_;
  private:
  };

  class BrokenLine : public Shape
  {
  public:
    BrokenLine(std::vector<double> data);
    void draw(void) override;
    int getShapeType() override { return TYPE_BROKEN_LINE; };
    BoundingBox boundingBox_;
  private:
  };


  class ShapeFabric
  {
  public:
    static std::shared_ptr<Shape> buildShape(int type, std::vector<double> data);
  };
}
