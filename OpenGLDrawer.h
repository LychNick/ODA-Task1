#pragma once

#include "Drawer.h"
#include "OpenGLWorker.h"

static std::vector<OpenGLEntity> entities;

void drawFunc();
void mouseWheel(int button, int dir, int x, int y);
void mouseState(int button, int state, int x, int y);

static OpenGLWorker openGLWorker;

class OpenGLDrawer: public Drawer
{
public:
  void createWindow() const;
  void startLoop() const;
  void drawBoundingBox(std::shared_ptr<FrameWork::BoundingBox> box) const override;
  void drawSquare(std::shared_ptr<FrameWork::Square> square) const override;
  void drawCircle(std::shared_ptr<FrameWork::Circle> circle) const override;
  void drawArc(std::shared_ptr<FrameWork::Arc> arc) const override;
  void drawPolygon(std::shared_ptr<FrameWork::Polygon> polygon) const override;
  void drawBrokenLine(std::shared_ptr<FrameWork::BrokenLine> brokenLine) const override;
};

