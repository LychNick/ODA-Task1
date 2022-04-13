#pragma once

#include "DataExporter.h"

#include <fstream>

class BinaryDataExporter: public DataExporter
{
public:
  BinaryDataExporter(const std::string& fileName);
  ~BinaryDataExporter();

  void open() const override;
  void close() const override;
  void wrInt(int data) const override;
  void wrDouble(double data) const override;

private:
  mutable std::ofstream file_;
  const std::string fileName_;
};