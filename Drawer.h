#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Shapes.h"
#include "Draw.h"

class Drawer
{
public:
	Drawer() = default;
	~Drawer() = default;
	void drawBoundingBox(const Draw& draw, const std::shared_ptr<FrameWork::BoundingBox> box) const;
	void drawSquare(const Draw& draw, const std::shared_ptr<FrameWork::Square> square) const;
	void drawCircle(const Draw& draw, const std::shared_ptr<FrameWork::Circle> circle) const;
	void drawArc(const Draw& draw, const std::shared_ptr<FrameWork::Arc> arc) const;
	void drawPolygon(const Draw& draw, const std::shared_ptr<FrameWork::Polygon> polygon) const;
	void drawBrokenLine(const Draw& draw, const std::shared_ptr<FrameWork::BrokenLine> brokenLine) const;
	void drawShape(const Draw& draw, const std::shared_ptr<FrameWork::Shape> shape) const;
	void drawShapes(const Draw& draw, const std::vector<std::shared_ptr<FrameWork::Shape>>& shapes) const;
	void setupDetailing(double detailing) const;
private:
	mutable double detailing_ = 1;
};
