#include "FrameWork.h"

namespace FrameWork
{
  size_t segmentsCount = 4;
  void FrameWork::loadShapes()
  {
    DataProvider dataProvider;

    size_t count = 0;
    try
    {
      count = dataProvider.rdInt();
      printf("count %i\n", count);
      for (size_t i = 0; i < count; i++)
      {
        int type = dataProvider.rdInt();
        printf("\ntype %i\n", type);

        size_t dataSize = dataProvider.rdInt();
        printf("data size: %i\n", dataSize);
        std::vector<double> data;
        bool isGood = true;
        for (size_t j = 0; j < dataSize; j++)
        {
          try
          {
            double dataElement = dataProvider.rdDouble();
            data.push_back(dataElement);
            printf(" %f", dataElement);
          }
          catch (const ReadError&)
          {
            isGood = false;
            printf("\n%s\n", "ReadError skip");
          }
        }
        printf("\n");
        if (isGood)
        {
          std::shared_ptr<Shape> shape = ShapeFactory::buildShape(type, data);
          
          if (!shape)
          {
            printf("%s\n", ("Unknown shape: " + std::to_string(type)).c_str());
          }
          else 
          {
            baseShapes_.push_back(shape);
          }
        }
      }
    }
    catch (const ReadError&)
    {
      printf("\n%s\n", "ReadError skip");
    }
    catch (const EndOfFile&)
    {
      printf("%s\n", "End of file");
    }
  }


  void drawShapes()
  {
    for (size_t i = 0; i < baseShapes_.size(); i++)
    {
      drawer_.drawShape(baseShapes_[i]);
      if (baseShapes_[i]->getBoundingBox()) 
      {
        drawer_.drawBoundingBox(baseShapes_[i]->getBoundingBox());
      }
    }
  }
}
