#pragma once

#include <string>

class DataProvider
{
public:
    DataProvider(void);
    virtual ~DataProvider(void);

    virtual int rdInt();
    virtual double rdDouble();

protected:
    void checkC();

    int c;
    long maxC;
};
