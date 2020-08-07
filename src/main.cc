#include <spdlog.h>

#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>
#include <iostream>


#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

QByteArray intToQByte(int var)
{
  cout << "int:" << var << endl;
  QByteArray out;
  out.append(static_cast<char>(((var & 0xFF000000) >> 24)));
  out.append(static_cast<char>(((var & 0x00FF0000) >> 16)));
  out.append(static_cast<char>(((var & 0x0000FF00) >> 8)));
  out.append(static_cast<char>(((var & 0x000000FF))));
  return out;
}

int QbyteToInt(QByteRef ref1, QByteRef ref2, QByteRef ref3, QByteRef ref4)
{
  int out = ((static_cast<int>(ref1) << 24) & 0xFF000000);
  out += ((static_cast<int>(ref2) << 16) & 0x00FF0000);
  out += ((static_cast<int>(ref3) << 8) & 0x0000FF00);
  out += ((static_cast<int>(ref4)) & 0x000000FF);
  cout << "int:" << out << endl;
  return out;
}

struct infoImage
{
  QByteArray image;
  int w;
  int h;
  int channels;
};

QByteArray setInfoToImage(QByteArray image, int w, int h, int channels)
{
  QByteArray out = image;
  out = intToQByte(w) + intToQByte(h) + intToQByte(channels) + out;
  return out;
}

infoImage getInfoToImage(QByteArray image)
{
  infoImage infoImageOutput;
  infoImageOutput.w = QbyteToInt(image[0], image[1], image[2], image[3]);
  infoImageOutput.h = QbyteToInt(image[4], image[5], image[6], image[7]);
  infoImageOutput.channels = QbyteToInt(image[8], image[9], image[10], image[11]);

  image.remove(1, 12);
  infoImageOutput.image = image;
  return infoImageOutput;
}

int main(int argc, char *argv[])
{
  // QCoreApplication application(argc, argv);
  auto messageLevel{ 0 };
  H_Logger->set_level(static_cast<spdlog::level::level_enum>(messageLevel));
  H_Logger->set_pattern("[%Y-%m-%d] [%H:%M:%S.%e] [%t] [%^%l%$] %v");
  H_Logger->debug("start main logger");
  H_Logger->debug("./QtFakeProcess (time in [s]) (name of process)");
  qint32 time = 1000;
  QString name = "";
  if(argc > 1)
  {
    QString timeStr =  QString::fromStdString( argv[1]);
    time = timeStr.toInt();
  }
  if(argc > 2)
  {
    name =  QString::fromStdString( argv[2]);
  }

  QTime now{};
  now.start();

  for(qint32 i = 0 ; i < time ; i++)
  {
    sleep(1);
    H_Logger->info("Fake proces {} spam msg: :{}",name.toStdString().c_str(),i);
  }
  

  return 0;
}
