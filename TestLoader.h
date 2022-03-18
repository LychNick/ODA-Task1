#pragma once

#include "Loader.h"

#include "DataProvider.h"
#include "Exceptions.h"
#include "Shapes.h"

class TestLoader : public Loader
{
public:
  std::vector<std::shared_ptr<FrameWork::Shape>> loadShapes() const override;
private:
};
