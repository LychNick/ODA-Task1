// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <conio.h>
#include <tchar.h>
#include <memory>

#include <thread>
#include <string>
#include <sstream>

#include "FrameWork.h"
#include "TestDataProvider.h"
#include "BinaryDataProvider.h"
#include "BinaryDataExporter.h"
#include "OpenGLDraw.h"
#include "WDraw.h"


void console(const Draw& draw)
{
  while (true) 
  {
    std::string command;
    std::getline(std::cin, command);
    if (command.substr(0, 5) == "save:") 
    {
      std::string fileName = command.substr(5, command.size() - 5) + ".tst";
      BinaryDataExporter binaryDataExporter(fileName);
      FrameWork::saveShapes(binaryDataExporter);
    }
    else if(command.substr(0, 5) == "load:")
    {
      std::string fileName = command.substr(5, command.size() - 5) + ".tst";
      BinaryDataProvider binaryDataProvider(fileName);
      FrameWork::loadShapes(binaryDataProvider);
      FrameWork::drawShapes(draw, 1);

    }
    else
    {
      std::istringstream stream(command);
      double value = 0;
      int type = 0;
      bool isType = true;
      std::vector<double> data;
      while (stream >> value)
      {
        if (isType)
        {
          type = value;
          isType = false;
        } else
        {
          data.push_back(value);
        }
      }
      if (!stream.eof())
      {
        std::cout << "bad command\n";
      }
      if (data.size() > 0)
      {
        std::shared_ptr<FrameWork::Shape> shape = FrameWork::ShapeFactory::buildShape(type, data);
        if (shape)
        {
          FrameWork::addShape(shape);
          FrameWork::drawShape(draw, shape, 1);
        }
      }
      else 
      {
        std::cout << "bad data\n";
      }
    }
  }
}

int _tmain(int argc, _TCHAR* argv[])
{
  _tprintf(_TEXT("%s\n"), argv[0]);
  try
  {
    TestDataProvider testDataProvider;
    FrameWork::loadShapes(testDataProvider);

    //BinaryDataProvider binaryDataProvider("testFile.tst");
    //FrameWork::loadShapes(binaryDataProvider);

    /*
    BinaryDataExporter binaryDataExporter("testFile.tst");
    FrameWork::saveShapes(binaryDataExporter);*/

    OpenGLDraw draw;
    draw.createWindow({800, 600}, "Task2");
    FrameWork::drawShapes(draw, 0.5);
    std::thread tr(console, draw);
    draw.initLoop();
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
