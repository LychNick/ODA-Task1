#pragma once

#include <memory>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "DataProvider.h"
#include "Exceptions.h"
#include "Shapes.h"
#include "WDraw.h"

namespace FrameWork
{
  static WDraw wDraw_;
  static size_t segmentsCount_ = 40;

  static std::vector<std::shared_ptr<FrameWork::Shape>> baseShapes_;
  static std::vector<std::shared_ptr<FrameWork::Shape>> drawShapes_;
  void loadData();


}