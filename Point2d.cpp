#include "Point2d.h"


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



template<typename T>
Point<T>::Point(T xx, T yy) :
  m_dX(xx),
  m_dY(yy)
{
}

template<typename T>
Point<T>::~Point()
{
}

template<typename T>
Point<T> Point<T>::operator+(const Point<T>& rPoint) const
{
  return Point(m_dX + rPoint.m_dX, m_dY + rPoint.m_dY);
}

template<typename T>
Point<T> Point<T>::operator-(const Point<T>& rPoint) const
{
  return Point(m_dX - rPoint.m_dX, m_dY - rPoint.m_dY);
}

template<typename T>
inline double Point<T>::length() const
{
  return sqrt(pow(m_dX, 2) + pow(m_dY, 2));
}
