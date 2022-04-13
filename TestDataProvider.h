#pragma once

#include "DataProvider.h"

class TestDataProvider: public DataProvider
{
public:
  TestDataProvider(void);
  ~TestDataProvider(void);

  void open() const override;
  void close() const override;
  int rdInt() const override;
  double rdDouble() const override;

protected:
  void checkC() const;

  mutable int c;
  long maxC;
};