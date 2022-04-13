#include "BinaryDataProvider.h"

BinaryDataProvider::BinaryDataProvider(const std::string& fileName):
  fileName_(fileName)
{
}

BinaryDataProvider::~BinaryDataProvider()
{
  close();
}

void BinaryDataProvider::open() const
{
  file_.open(fileName_, std::ios::binary);
  if (!file_.is_open())
  {
    throw std::invalid_argument("can't open file " + fileName_);
  }
}

void BinaryDataProvider::close() const
{
  if (file_ && file_.is_open())
  {
    file_.close();
  }
}

int BinaryDataProvider::rdInt() const
{
  int data = 0;
  file_.read((char*)& data, sizeof(int));
  return data;
}
double BinaryDataProvider::rdDouble() const 
{
  double data = 0;
  file_.read((char*)&data, sizeof(double));
  return data;
}
