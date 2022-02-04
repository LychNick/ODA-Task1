#include "FrameWork.h"

namespace FrameWork
{

  void FrameWork::loadData()
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
            wDraw_.drawText("ReadError skip");
          }
        }
        printf("\n");
        if (isGood)
        {
          std::shared_ptr<Shape> shape = nullptr;
          std::shared_ptr<Shape> boundingShape = nullptr;
          switch (type)
          {
          case TYPE_SQUARE: 
          {
            std::shared_ptr<Square> tmp = std::make_shared<Square>(data);
            boundingShape = std::make_shared<BoundingBox>(tmp->boundingBox_);
            shape = tmp;
            break;
          }
          case TYPE_CIRCLE:
          {
            std::shared_ptr<Circle> tmp = std::make_shared<Circle>(data);
            boundingShape = std::make_shared<BoundingBox>(tmp->boundingBox_);
            shape = tmp;
            break;
          }
          case TYPE_ARC:
          {
            std::shared_ptr<Arc> tmp = std::make_shared<Arc>(data);
            boundingShape = std::make_shared<BoundingBox>(tmp->boundingBox_);
            shape = tmp;
            break;
          }
          case TYPE_POLYGON:
          {
            std::shared_ptr<Polygon> tmp = std::make_shared<Polygon>(data);
            boundingShape = std::make_shared<BoundingBox>(tmp->boundingBox_);
            shape = tmp;
            break;
          }
          case TYPE_BROKEN_LINE:
          {
            std::shared_ptr<BrokenLine> tmp = std::make_shared<BrokenLine>(data);
            boundingShape = std::make_shared<BoundingBox>(tmp->boundingBox_);
            shape = tmp;
            break;
          }
          default:
            break;
          }
          if (!shape)
          {
            wDraw_.drawText(("Unknown shape: " + std::to_string(type)).c_str());
          }
          else 
          {
            baseShapes_.push_back(shape);
            drawShapes_.push_back(boundingShape);
          }
        }
      }
    }
    catch (const ReadError&)
    {
      wDraw_.drawText("ReadError skip");
    }
    catch (const EndOfFile&)
    {
      wDraw_.drawText("EndOfFile");
    }
  }

  std::shared_ptr<Shape> ShapeFabric::buildShape(int type, std::vector<double> data)
  {
    switch (type)
    {
    case 1:
      return std::make_shared<Square>(data);
      break;
    case 2:
      return std::make_shared<Circle>(data);
      break;
    case 4:
      return std::make_shared<Arc>(data);
      break;
    case 5:
      return std::make_shared<Polygon>(data);
      break;
    case 6:
      return std::make_shared<BrokenLine>(data);
      break;
    default:
      return nullptr;
      break;
    }
  }

  void BoundingBox::draw(void)
  {
    wDraw_.drawText("draw Bounding Box:");
    for (size_t i = 0; i < data_.size() - 1; i++)
    {
      wDraw_.drawSegment(data_[i], data_[i + 1]);
    }
    wDraw_.drawSegment(data_[data_.size() - 1], data_[0]);
    wDraw_.drawText("");
  }

  Square::Square(Point2d leftDown, Point2d rightUp) :
    Square({leftDown.x(), leftDown.y(), rightUp.x(), rightUp.y()})
  {
  }

  Square::Square(std::vector<double> data) :
    Shape("Square")
  {
    if (data.size() != 4)
    {
      throw std::invalid_argument("bad Square data");
    }
    fileData_ = data;
    data_.push_back(Point2d(data[0], data[1])); //leftDown
    data_.push_back(Point2d(data[0], data[3])); //leftUp
    data_.push_back(Point2d(data[2], data[3])); //rightUp
    data_.push_back(Point2d(data[2], data[1])); //rightDown

    boundingBox_ = BoundingBox(data_);

    double lineLength = getLineLength(data_, true);
    wDraw_.drawText(("Linearized length: " + std::to_string(lineLength)).c_str());
    draw();
  }

  void Square::draw(void)
  {
    wDraw_.drawText("draw Square:");
    for (size_t i = 0; i < data_.size() - 1; i++)
    {
      wDraw_.drawSegment(data_[i], data_[i + 1]);
    }
    wDraw_.drawSegment(data_[data_.size() - 1], data_[0]);
    wDraw_.drawText("");
  }

  Circle::Circle(std::vector<double> data) :
    Shape("Circle")
  {
    if (data.size() != 3)
    {
      throw std::invalid_argument("bad Circle data");
    }
    fileData_ = data;
    Point2d centerPoint(data[0], data[1]);
    double R = data[2];
    double step = 2 * M_PI / segmentsCount_;
    for (size_t i = 0; i < segmentsCount_; i++)
    {
      data_.push_back(centerPoint + Point2d(R * cos(step*i), R * sin(step * i)));
    }   

    boundingBox_ = BoundingBox(data_);

    double lineLength = getLineLength(data_, true);
    wDraw_.drawText(("Linearized length: " + std::to_string(lineLength)).c_str());
    draw();
    wDraw_.drawText("Bounding box:\n");
    boundingBox_.draw();
  }

  void Circle::draw(void)
  {
    wDraw_.drawText("draw Circle:");
    for (size_t i = 0; i < data_.size() - 1; i++)
    {
      wDraw_.drawSegment(data_[i], data_[i + 1]);
    }
    wDraw_.drawSegment(data_[data_.size() - 1], data_[0]);
    wDraw_.drawText("");
  }

  Arc::Arc(std::vector<double> data) :
    Shape("Arc")
  {
    if (data.size() != 5) 
    {
      throw std::invalid_argument("bad Arc data");
    }
    fileData_ = data;
    Point2d centerPoint(data[0], data[1]);
    double R = data[2];

    double startR = data[3];
    double endR = data[4];

    double step = (endR - startR) / segmentsCount_;
    for (size_t i = 0; i <= segmentsCount_; i++)
    {
      data_.push_back(centerPoint + 
        Point2d(R * cos(startR + step * i), R * sin(startR + step * i)));
    }

    boundingBox_ = BoundingBox(data_);
    
    double lineLength = getLineLength(data_, false);
    wDraw_.drawText(("Linearized length: " + std::to_string(lineLength)).c_str());
    draw();
    wDraw_.drawText("Bounding box:\n");
    boundingBox_.draw();
  }

  void Arc::draw(void)
  {
    wDraw_.drawText("draw Arc:");
    for (size_t i = 0; i < data_.size() - 1; i++)
    {
      wDraw_.drawSegment(data_[i], data_[i + 1]);
    }
    wDraw_.drawText("");
  }

  Polygon::Polygon(std::vector<double> data) :
    Shape("Polygon")
  {
    if (data.size() < 3)
    {
      throw std::invalid_argument("bad Polygon data");
    }
    fileData_ = data;
    for (size_t i = 0; i < data.size() - 1; i += 2)
    {
      data_.push_back(Point2d(data[i], data[i + 1]));
    }

    boundingBox_ = BoundingBox(data_); 
    
    double lineLength = getLineLength(data_, true);
    wDraw_.drawText(("Linearized length: " + std::to_string(lineLength)).c_str());
    draw();
    wDraw_.drawText("Bounding box:\n");
    boundingBox_.draw();
  }

  void Polygon::draw(void)
  {
    wDraw_.drawText("draw Polygon:");
    for (size_t i = 0; i < data_.size() - 1; i++)
    {
      wDraw_.drawSegment(data_[i], data_[i + 1]);
    }
    wDraw_.drawSegment(data_[data_.size() - 1], data_[0]);
    wDraw_.drawText("");
  }

  BrokenLine::BrokenLine(std::vector<double> data) :
    Shape("BrokenLine")
  {
    if (data.size() < 2)
    {
      throw std::invalid_argument("bad BrokenLine data");
    }
    fileData_ = data;
    for (size_t i = 0; i < data.size() - 1; i += 2)
    {
      data_.push_back(Point2d(data[i], data[i + 1]));
    }

    boundingBox_ = BoundingBox(data_);

    double lineLength = getLineLength(data_, false);
    wDraw_.drawText(("Linearized length: " + std::to_string(lineLength)).c_str());
    draw();
    wDraw_.drawText("Bounding box:\n");
    boundingBox_.draw();
  }

  void BrokenLine::draw(void)
  {
    wDraw_.drawText("draw BrokenLine:");
    for (size_t i = 0; i < data_.size() - 1; i++)
    {
      wDraw_.drawSegment(data_[i], data_[i + 1]);
    }
    wDraw_.drawText("");
  }
}
