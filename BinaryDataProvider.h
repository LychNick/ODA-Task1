#pragma once

#include "DataProvider.h"

#include <string>
#include <fstream>

class BinaryDataProvider: public DataProvider
{
public:
  BinaryDataProvider(const std::string& fileName);
  ~BinaryDataProvider();

  void open() const override;
  void close() const override;
  int rdInt() const override;
  double rdDouble() const override;
private:
  mutable std::ifstream file_;
  const std::string fileName_;
};
