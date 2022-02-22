#pragma once

#include <string>

class Exception
{
public:
  Exception(std::wstring message);
  ~Exception();
  std::wstring what() const;

private:
  std::wstring message_;
};


class EndOfFile
{
public:
    EndOfFile(void);
    ~EndOfFile(void);
};

class ReadError {
};
