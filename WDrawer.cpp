#include "WDrawer.h"

WDrawer::WDrawer()
{
  draw_ = std::make_shared<WDraw>();
}

void WDrawer::drawShapes(const std::vector<std::shared_ptr<FrameWork::Shape>>& shapes) const
{
  for (size_t i = 0; i < shapes.size(); i++)
  {
    drawShape(draw_, shapes[i]);
  }
}
