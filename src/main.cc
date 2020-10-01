#include "configreader.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

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

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

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
  spdlog::set_level(static_cast<spdlog::level::level_enum>(messageLevel));
  spdlog::set_pattern("[%Y-%m-%d] [%H:%M:%S.%e] [%t] [%^%l%$] %v");
  spdlog::debug("start main logger");
  spdlog::debug("./QtFakeProcess (time in [s]) (name of process)");
  qint32 time = 20;
  QString name = "none";
  if(argc > 1)
  {
    QString timeStr =  QString::fromStdString( argv[1]);
    time = timeStr.toInt();
  }
  if(argc > 2)
  {
    name =  QString::fromStdString( argv[2]);
  }
  spdlog::debug("./QtFakeProcess ({}[s]) ({})", time, name.toStdString());
  QTime now{};
  now.start();

  for(qint32 i = 0 ; i < time ; i++)
  {
    //sleep(1);
#ifdef Q_OS_WIN
      Sleep(uint(1000));
#else
      struct timespec ts = { 1 / 1000, (1 % 1000) * 1000 * 1000 };
      nanosleep(&ts, NULL);
#endif
      
    spdlog::debug("Fake proces {} spam msg: :{}",name.toStdString().c_str(),i);
  }
  

  return 0;
}
