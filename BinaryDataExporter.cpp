#include "BinaryDataExporter.h"

BinaryDataExporter::BinaryDataExporter(const std::string& fileName):
  fileName_(fileName)
{  
}

BinaryDataExporter::~BinaryDataExporter()
{
  close();
}

void BinaryDataExporter::open() const
{
  file_.open(fileName_, std::ios::binary);
  if (!file_.is_open())
  {
    throw std::invalid_argument("can't open file " + fileName_);
  }
}

void BinaryDataExporter::close() const
{
  if (file_ && file_.is_open())
  {
    file_.close();
  }
}

void BinaryDataExporter::wrInt(int data) const
{
  file_.write((char*) & data, sizeof(int));
}

void BinaryDataExporter::wrDouble(double data) const
{
  file_.write((char*)&data, sizeof(double));
}
