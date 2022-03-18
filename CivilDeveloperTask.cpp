// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <conio.h>
#include <tchar.h>

#include "FrameWork.h"
#include "TestLoader.h"
#include "OpenGLDrawer.h"
#include "WDrawer.h"


int _tmain(int argc, _TCHAR* argv[])
{
  _tprintf(_TEXT("%s\n"), argv[0]);
  try
  { 
    FrameWork::loadShapes(std::make_unique<TestLoader>());
    FrameWork::drawShapes(std::make_unique<OpenGLDrawer>(), 1/10.);
  }
  catch (const std::exception& e)
  {
    fprintf(stderr, "%s\n", e.what());
    exit(1);
  }
  catch (const Exception& e)
  {
    fprintf(stderr, "%ls\n", e.what().c_str());
    exit(1);
  }
  _getch();
  return 0;
}
