#ifndef INIREADER_H
#define INIREADER_H

#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QMap>
#include <QStringList>
#include <QTime>        // current time for seed
#include <QtGlobal>     // qsrand, qrand

class IniReader
{
  QMap<QString, QString>  m_dropboxDirs;
  QStringList             m_labels;
  bool                    m_isParsed;

 public:
  IniReader();
  ~IniReader();

  // meca
  bool isParsed() const { return m_isParsed; }
  bool parse(const QString& fileName = "spammer.ini");
  bool generateExampleIniFile();

  // accessors
  QString getDropboxDir(const QString& name) const;
  QString getRandomSentence(const QString& name) const;
  bool containsSentence(const QString& sentence, const QString& name) const;
};

#endif // INIREADER_H

