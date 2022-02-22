// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <conio.h>

#include "DataProvider.h"
#include "FrameWork.h"
#include <tchar.h>


int _tmain(int argc, _TCHAR* argv[])
{
  _tprintf(_TEXT("%s\n"), argv[0]);
  try
  {    
    FrameWork::segmentsCount = 200;
    FrameWork::loadShapes();
    FrameWork::drawShapes();
  }
  catch (const std::exception& e)
  {
    fprintf(stderr, "%s\n", e.what());
    exit(1);
  }
  catch (const Exception& e)
  {
    fprintf(stderr, "%S\n", e.what().c_str());
    exit(1);
  }
  _getch();
  return 0;
}
