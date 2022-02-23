#include "Exceptions.h"


Exception::Exception(const std::wstring& message) :
  message_(message)
{}

Exception::~Exception()
{
}

std::wstring Exception::what() const
{
  return message_;
}

EndOfFile::EndOfFile(void)
{
}

EndOfFile::~EndOfFile(void)
{
}
