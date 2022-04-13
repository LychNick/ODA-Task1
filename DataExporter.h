#pragma once

class DataExporter
{
public:
  DataExporter(void) = default;
  virtual ~DataExporter(void) = default;

  virtual void open() const = 0;
  virtual void close() const = 0;
  virtual void wrInt(int data) const = 0;
  virtual void wrDouble(double data) const = 0;
};
