#ifndef TOOLS_H
#define TOOLS_H

// Qt
#include <QString>
#include <QByteArray>
#include <QFile>
// Own
#include "qlogger.h"

struct Tools
{
  static void saveJsonDataInFile(const QByteArray& jsonData, const QString& path)
  {
    QFile file(path);
    QIODevice::OpenMode mode = QFile::WriteOnly | QFile::Text;
    if (file.exists())
      mode |= QFile::Truncate;

    if (file.open(mode))
      {
	file.write(jsonData);
	if (mode & QFile::Truncate)
	  QLogger::QLog_Info(THREAD_ID, QString("File %1 truncated").arg(path));
	file.close();
      }
    else
      QLogger::QLog_Error(THREAD_ID, QString("Failed to open %1 because %2").arg(path).arg(file.errorString()));
  }

  static void loadJsonDataFromFile(const QString& path, QByteArray& jsonData)
  {
    QFile file(path);
    if (file.exists())
      {
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	jsonData = file.readAll();
	QLogger::QLog_Info(THREAD_ID, QString("LOAD: file %1 loaded").arg(path));
	file.close();
      }
    else
      QLogger::QLog_Error(THREAD_ID, QString("LOAD: file %1 does not exist").arg(path));
  }
};

#endif
