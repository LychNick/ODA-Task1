#include "Point2d.h"


Point2d::Point2d():
  m_dX(0),
  m_dY(0)
{}

Point2d::Point2d(double xx, double yy) :
  m_dX(xx), m_dY(yy)
{
}

Point2d::~Point2d(void)
{
}

Point2d Point2d::operator+(const Point2d& rPoint) const
{
  return Point2d(m_dX + rPoint.m_dX, m_dY + rPoint.m_dY);
}

Point2d Point2d::operator-(const Point2d& rPoint) const
{
  return Point2d(m_dX - rPoint.m_dX, m_dY - rPoint.m_dY);
}

double Point2d::length() const
{
  return sqrt(pow(m_dX, 2) + pow(m_dY, 2));
}
