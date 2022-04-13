#pragma once

#include <math.h>

class Point2d
{
public:
  Point2d();
  Point2d(double xx, double yy);
  ~Point2d(void);

  Point2d operator+(const Point2d& rPoint) const;
  Point2d operator-(const Point2d& rPoint) const;

  double x() const { return m_dX; }
  double y() const { return m_dY; }
  double length() const;

  void setX(double x) { m_dX = x; }
  void setY(double y) { m_dY = y; }
private:
    double m_dX;
    double m_dY;
};

template<int L, typename T>
class Point
{
public:
  Point() 
  {}
  ~Point() {};
private:
  T params_[L];
};
