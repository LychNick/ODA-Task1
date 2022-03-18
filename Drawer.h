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
	void drawBoundingBox(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::BoundingBox> box) const;
	void drawSquare(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Square> square) const;
	void drawCircle(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Circle> circle) const;
	void drawArc(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Arc> arc) const;
	void drawPolygon(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Polygon> polygon) const;
	void drawBrokenLine(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::BrokenLine> brokenLine) const;
	void drawShape(const std::shared_ptr<Draw> draw, const std::shared_ptr<FrameWork::Shape> shape) const;
	virtual void drawShapes(const std::vector<std::shared_ptr<FrameWork::Shape>>& shapes) const = 0;
	void setupDetailing(double detailing);
private:
	double detailing_ = 1;
};
