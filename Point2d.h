#pragma once

#include <math.h>

class Point2d
{
public:
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

template<typename T>
class Point
{
public:
  Point(T xx, T yy);
  ~Point();
  Point operator+(const Point& rPoint) const;
  Point operator-(const Point& rPoint) const;
  double length() const;
  T x() const { return m_dX; }
  T y() const { return m_dY; }
  void setX(T x) { m_dX = x; }
  void setY(T y) { m_dY = y; }
private:
  T m_dX;
  T m_dY;
};


