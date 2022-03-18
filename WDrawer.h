#pragma once

#include "Drawer.h"
#include "WDraw.h"

class WDrawer: public Drawer
{
public:
  WDrawer();
  void drawShapes(const std::vector<std::shared_ptr<FrameWork::Shape>>& shapes) const override;
private:
  std::shared_ptr<WDraw> draw_;
};
