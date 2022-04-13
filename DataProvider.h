#pragma once

#include <string>

class DataProvider
{
public:
    DataProvider(void) = default;
    virtual ~DataProvider(void) = default;

    virtual void open() const = 0;
    virtual void close() const = 0;
    virtual int rdInt() const = 0;
    virtual double rdDouble() const = 0;
};
