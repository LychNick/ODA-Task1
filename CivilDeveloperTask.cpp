// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "DataProvider.h"
#include "FrameWork.h"
#include <tchar.h>


int _tmain(int argc, _TCHAR* argv[])
{
  _tprintf(_TEXT("%s\n"), argv[0]);
  try
  {
    FrameWork::loadData();
  }
  catch (const std::exception& e)
  {
    fprintf(stderr, "%s\n", e.what());
    exit(1);
  }

  return 0;
}
