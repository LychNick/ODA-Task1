#include "FrameWork.h"

namespace FrameWork
{
  std::vector<std::shared_ptr<FrameWork::Shape>> baseShapes_;
  void loadShapes(const DataProvider& dataProvider)
  {
    dataProvider.open();

    size_t count = 0;
    try
    {
      count = dataProvider.rdInt();
      printf("count %i\n", count);
      for (size_t i = 0; i < count; i++)
      {
        int type = dataProvider.rdInt();
        printf("\ntype %i\n", type);

        int dataSize = dataProvider.rdInt();
        if (dataSize <= 0)
        {
          throw std::invalid_argument("Bad data size");
        }
        printf("data size: %i\n", dataSize);
        std::vector<double> data;
        bool isGood = true;
        for (int j = 0; j < dataSize; j++)
        {
          try
          {
            double dataElement = dataProvider.rdDouble();
            data.push_back(dataElement);
            printf(" %f", dataElement);
          } catch (const ReadError&)
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
          } else
          {
            addShape(shape);
          }
        }
      }
    } catch (const ReadError&)
    {
      printf("\n%s\n", "ReadError skip");
    } catch (const EndOfFile&)
    {
      printf("%s\n", "End of file");
    }
    dataProvider.close();
  }

  void saveShapes(const DataExporter& dataExporter)
  {
    dataExporter.open();
    if (baseShapes_.size() > 0)
    {
      dataExporter.wrInt(baseShapes_.size());
      for (size_t i = 0; i < baseShapes_.size(); i++)
      {
        dataExporter.wrInt(baseShapes_[i]->getShapeType());
        const std::vector<double> data = Exporter::exportShape(baseShapes_[i]);
        dataExporter.wrInt(data.size());
        for (size_t i = 0; i < data.size(); i++)
        {
          dataExporter.wrDouble(data[i]);
        }
      }
    }
    dataExporter.close();
  }

  void drawShapes(const Draw& draw, double detailing)
  {
    drawer.setupDetailing(detailing);    
    drawer.drawShapes(draw, baseShapes_);
  }

  void addShape(std::shared_ptr<FrameWork::Shape> shape)
  {
    baseShapes_.push_back(shape);
  }

  void drawShape(const Draw& draw,std::shared_ptr<Shape> shape, double detailing)
  {
    drawer.setupDetailing(detailing);
    drawer.drawShape(draw, shape);
  }
}
