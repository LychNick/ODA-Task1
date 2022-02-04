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

  std::vector<double> Shape::getFileData() const
  {
    return fileData_;
  }

  std::string Shape::getName(void)
  {
    return name_;
  }

  BoundingBox::BoundingBox() :
    leftDownPoint_({ 0,0 }),
    rightUpPoint_({ 0,0 }),
    Shape("BoundingBox")
  {
  }

  BoundingBox::BoundingBox(std::vector<Point2d>& data) : 
    leftDownPoint_({0,0}),
    rightUpPoint_({0,0}),
    Shape("BoundingBox")
  {
    if (data.size() <= 0)
    {
      throw std::invalid_argument("Empty data");
    }
    leftDownPoint_ = data[0];
    rightUpPoint_ = data[0];
    for (size_t i = 1; i < data.size(); i++)
    {
      if (data[i].x() < leftDownPoint_.x())
      {
        leftDownPoint_.setX(data[i].x());
      }
      if (data[i].y() < leftDownPoint_.y())
      {
        leftDownPoint_.setY(data[i].y());
      }

      if (data[i].x() > rightUpPoint_.x())
      {
        rightUpPoint_.setX(data[i].x());
      }
      if (data[i].y() > rightUpPoint_.y())
      {
        rightUpPoint_.setY(data[i].y());
      }
    }

    data_.push_back(leftDownPoint_);
    data_.push_back({ leftDownPoint_.x(), rightUpPoint_.y() });
    data_.push_back(rightUpPoint_);
    data_.push_back({ rightUpPoint_.x(), leftDownPoint_.y() });

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
}