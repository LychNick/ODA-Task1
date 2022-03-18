#include "FrameWork.h"

namespace FrameWork
{
  void loadShapes(const std::unique_ptr<Loader> loader)
  {
    baseShapes_ = loader->loadShapes();
  }

  void drawShapes(const std::unique_ptr<Drawer> drawer, double detailing)
  {
    drawer->setupDetailing(detailing);
    drawer->drawShapes(baseShapes_);
  }
}
