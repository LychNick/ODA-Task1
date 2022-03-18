#pragma once

#include "Shapes.h"

class Loader 
{
public:
  virtual std::vector<std::shared_ptr<FrameWork::Shape>> loadShapes() const = 0;
};
