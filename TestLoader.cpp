#include "TestLoader.h"


std::vector<std::shared_ptr<FrameWork::Shape>> TestLoader::loadShapes() const
{
  DataProvider dataProvider;
  std::vector<std::shared_ptr<FrameWork::Shape>> shapes;

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
        std::shared_ptr<FrameWork::Shape> shape = FrameWork::ShapeFactory::buildShape(type, data);
          
        if (!shape)
        {
          printf("%s\n", ("Unknown shape: " + std::to_string(type)).c_str());
        }
        else 
        {
          shapes.push_back(shape);
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
  return shapes;
}
