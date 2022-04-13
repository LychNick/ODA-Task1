#include "TestDataProvider.h"
#include "Exceptions.h"

#define PI 3.141
#define THROW_ERR 23000000

double gData[] = {
    8, // -- ����� �������� � �����



    1, // 1 -- ��� "�������" �� ���������, ������������� ���� ���������
    4, // 4 -- ���������� ����� double
    0.0, 0.0, // ���������� - ����� ������ ����
    10.0, 10.0, // ���������� - ������ ������� ����



    2, // 2 -- ��� "����������"
    3, 
    0.0, 0.0, // ���������� - ����� ����������
    25.0, // ������ ����������



    3, // 3 -- ���� ����������� ���
    5,
    1., 2., 3., 4., 5., // ������



    4, // 4 - ���� ����������
    5,
    150., 150.,  // ���������� -- ����� ����������
    44.,         // ������ ����������
    -PI/4., PI/2., // ����� -- ������ � ����� ����


    2, // 2 -- ��� "����������"
    3,
    10.0, THROW_ERR, // ��� ������ ������� ���������� ����������
    25.0,



    5, // 5 -- ��� �������������
    10,
    10., 20., // ���������� �����
    20., 30., // ���������� �����
    35., 25., // ���������� �����
    0., 50., // ���������� �����
    0., 0.,   // ���������� �����



    6, // -- ��� "�������"
    10,
    0,0, // ���������� �����
    1,1, // ���������� �����
    0,1, // ���������� �����
    0,2, // ���������� �����
    5,5, // ���������� �����


    28, // ����������� ������
    10,
    90,91,92,93,94,95,96,97,98,99
};

TestDataProvider::TestDataProvider(void) : c(0), maxC(sizeof(gData)/sizeof(gData[0]))
{
}

TestDataProvider::~TestDataProvider(void)
{
}

void TestDataProvider::open() const
{}

void TestDataProvider::close() const
{}

int TestDataProvider::rdInt() const {
    checkC();
    return (int)gData[c++];
}

double TestDataProvider::rdDouble() const {
    checkC();
    double d = gData[c++];
    if (d == THROW_ERR) {
        throw ReadError();
    }
    return d;
}

void TestDataProvider::checkC() const {
    if (c == maxC) {
        throw EndOfFile();
    }
}
