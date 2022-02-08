#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "FrameWork.h"


const double EPS = 1 / 100000.;

BOOST_AUTO_TEST_CASE(calcSquareLineWidthTest)
{
  Point2d leftDown = Point2d(-20, -15);
  Point2d rightUp = Point2d(5.5, 6);
  std::shared_ptr<FrameWork::Square> testSquare = std::make_shared<FrameWork::Square>(leftDown, rightUp);
  testSquare->calcLineWidth();
  double correctLineWidth = (rightUp.x() - leftDown.x()) * 2 + (rightUp.y() - leftDown.y()) * 2;
  BOOST_REQUIRE_EQUAL(testSquare->getLineWidth(), correctLineWidth);
}

BOOST_AUTO_TEST_CASE(calcCircleLineWidthTest)
{
  std::shared_ptr<FrameWork::Circle> testCircle = std::make_shared<FrameWork::Circle>(Point2d(0,0), 25);
  testCircle->calcLineWidth();
  double step = 2 * M_PI / FrameWork::segmentsCount_;
  double correctLineWidth = FrameWork::segmentsCount_ * testCircle->getR() * sqrt(std::pow(1 - cos(step), 2) + std::pow(sin(step), 2));
  BOOST_REQUIRE_EQUAL(testCircle->getLineWidth(), correctLineWidth);
}

BOOST_AUTO_TEST_CASE(calcArcLineWidthTest)
{
  std::shared_ptr<FrameWork::Arc> testArc = std::make_shared<FrameWork::Arc>(Point2d(0, 0), 25, -M_PI/4, M_PI/2);
  testArc->calcLineWidth();
  double step = (testArc->getEndR() - testArc->getStartR()) / FrameWork::segmentsCount_;
  double correctLineWidth = FrameWork::segmentsCount_ * testArc->getR() * sqrt(std::pow(1 - cos(step), 2) + std::pow(sin(step), 2));
  BOOST_REQUIRE_EQUAL(testArc->getLineWidth(), correctLineWidth);
}

BOOST_AUTO_TEST_CASE(calcPolygonLineWidthTest)
{
  std::vector<Point2d> points = { 
    {0,0},
    {0,2},
    {2,0}
  };
  std::shared_ptr<FrameWork::Polygon> testPolygon = std::make_shared<FrameWork::Polygon>(std::move(points));
  testPolygon->calcLineWidth();

  double correctLineWidth = sqrt(8) + 4;

  BOOST_REQUIRE_EQUAL(testPolygon->getLineWidth(), correctLineWidth);
}

BOOST_AUTO_TEST_CASE(calcBrokenLineWidthTest)
{
  std::vector<Point2d> points = {
    {0,0},
    {0,2},
    {2,0}
  };
  std::shared_ptr<FrameWork::BrokenLine> testBrokenLine = std::make_shared<FrameWork::BrokenLine>(std::move(points));
  testBrokenLine->calcLineWidth();

  double correctLineWidth = sqrt(8) + 2;

  BOOST_REQUIRE_EQUAL(testBrokenLine->getLineWidth(), correctLineWidth);
}


BOOST_AUTO_TEST_CASE(calcSquareBoundingBoxTest)
{
  Point2d leftDown = Point2d(-20, -15);
  Point2d rightUp = Point2d(5.5, 6);
  std::shared_ptr<FrameWork::Square> testSquare = std::make_shared<FrameWork::Square>(leftDown, rightUp);
  testSquare->calcBoundingBox();

  std::shared_ptr<FrameWork::BoundingBox> box = testSquare->getBoundingBox();

  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().x(), leftDown.x());
  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().y(), leftDown.y());
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().x(), rightUp.x());
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().y(), rightUp.y());
}

BOOST_AUTO_TEST_CASE(calcCircleBoundingBoxTest)
{
  Point2d centerPoint = Point2d(-5, 0);
  double R = 25;

  std::shared_ptr<FrameWork::Circle> testCircle = std::make_shared<FrameWork::Circle>(centerPoint, R);
  testCircle->calcBoundingBox();

  std::shared_ptr<FrameWork::BoundingBox> box = testCircle->getBoundingBox();
  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().x(), centerPoint.x() - R);
  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().y(), centerPoint.y() - R);
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().x(), centerPoint.x() + R);
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().y(), centerPoint.y() + R);
}

BOOST_AUTO_TEST_CASE(calcArcBoundingBoxTest)
{
  Point2d centerPoint = Point2d(-5, 0);
  double R = 25;

  std::shared_ptr<FrameWork::Arc> testArc = std::make_shared<FrameWork::Arc>(centerPoint, R, 0, M_PI / 2);
  testArc->calcBoundingBox();

  std::shared_ptr<FrameWork::BoundingBox> box = testArc->getBoundingBox();
  BOOST_REQUIRE_CLOSE(box->getLeftDownPoint().x(), centerPoint.x(), EPS);
  BOOST_REQUIRE_CLOSE(box->getLeftDownPoint().y(), centerPoint.y(), EPS);
  BOOST_REQUIRE_CLOSE(box->getRightUpPoint().x(), centerPoint.x() + R, EPS);
  BOOST_REQUIRE_CLOSE(box->getRightUpPoint().y(), centerPoint.y() + R, EPS);
}

BOOST_AUTO_TEST_CASE(calcPolygonBoundingBoxTest)
{
  std::vector<Point2d> points = {
    {0,0},
    {0,-2},
    {2,0}
  };
  std::shared_ptr<FrameWork::Polygon> testPolygon = std::make_shared<FrameWork::Polygon>(std::move(points));
  testPolygon->calcBoundingBox();
  
  std::shared_ptr<FrameWork::BoundingBox> box = testPolygon->getBoundingBox();
  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().x(), 0);
  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().y(), -2);
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().x(), 2);
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().y(), 0);
}

BOOST_AUTO_TEST_CASE(calcBrokenLineBoundingBoxTest)
{
  std::vector<Point2d> points = {
    {0,0},
    {-4,2},
    {2,0}
  };
  std::shared_ptr<FrameWork::BrokenLine> testBrokenLine = std::make_shared<FrameWork::BrokenLine>(std::move(points));
  testBrokenLine->calcBoundingBox();

  std::shared_ptr<FrameWork::BoundingBox> box = testBrokenLine->getBoundingBox();
  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().x(), -4);
  BOOST_REQUIRE_EQUAL(box->getLeftDownPoint().y(), 0);
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().x(), 2);
  BOOST_REQUIRE_EQUAL(box->getRightUpPoint().y(), 2);
}