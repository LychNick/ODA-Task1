#include "FrameWork.h"

namespace FrameWork
{

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
          std::shared_ptr<Shape> shape = nullptr;
          switch (type)
          {
          case TYPE_SQUARE: 
          {
            shape = ShapeFabric::buildSquare(data);
            break;
          }
          case TYPE_CIRCLE:
          {
            shape = ShapeFabric::buildCircle(data);
            break;
          }
          case TYPE_ARC:
          {
            shape = ShapeFabric::buildArc(data);
            break;
          }
          case TYPE_POLYGON:
          {
            shape = ShapeFabric::buildPolygon(data);
            break;
          }
          case TYPE_BROKEN_LINE:
          {
            shape = ShapeFabric::buildBrokenLine(data);
            break;
          }
          default:
            break;
          }
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

  void calcShapesParams()
  {
    for (size_t i = 0; i < baseShapes_.size(); i++)
    {
      baseShapes_[i]->calcBoundingBox();
      baseShapes_[i]->calcLineWidth();
    }
  }

  void drawShapes()
  {
    for (size_t i = 0; i < baseShapes_.size(); i++)
    {
      switch (baseShapes_[i]->getShapeType())
      {
      case TYPE_SQUARE:
      {
        drawer_.drawSquare(std::static_pointer_cast<FrameWork::Square>(baseShapes_[i]));
        break;
      }
      case TYPE_CIRCLE:
      {
        drawer_.drawCircle(std::static_pointer_cast<FrameWork::Circle>(baseShapes_[i]));
        break;
      }
      case TYPE_ARC:
      {
        drawer_.drawArc(std::static_pointer_cast<FrameWork::Arc>(baseShapes_[i]));
        break;
      }
      case TYPE_POLYGON:
      {
        drawer_.drawPolygon(std::static_pointer_cast<FrameWork::Polygon>(baseShapes_[i]));
        break;
      }
      case TYPE_BROKEN_LINE:
      {
        drawer_.drawBrokenLine(std::static_pointer_cast<FrameWork::BrokenLine>(baseShapes_[i]));
        break;
      }
      default:
        break;
      }
      if (baseShapes_[i]->getBoundingBox()) 
      {
        drawer_.drawBoundingBox(baseShapes_[i]->getBoundingBox());
      }
    }
  }
}
