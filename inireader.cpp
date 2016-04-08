#include "inireader.h"
#include <QDebug>

IniReader::IniReader()
  : m_isParsed(false)
{
  qsrand((uint)QTime::currentTime().msec());
}

IniReader::~IniReader()
{
}

bool IniReader::parse(const QString& fileName)
{
  QDir      applicationDir  = QApplication::applicationDirPath();
  QString   filePath        = applicationDir.absoluteFilePath(fileName);
  QSettings settings(filePath, QSettings::IniFormat);

  // List available keys in QSettings instance
  QStringList availablekeys = settings.allKeys();
  foreach(const QString& key, availablekeys)
    qDebug() << "[DEBUG] Found available key whose name is " << key;

  // Check if all needed keys exist
  QStringList keys = QStringList() << "Dropbox/tonyDir"
                                   << "Dropbox/chrisDir"
                                   << "Dropbox/gerardDir"
                                   << "Sentences/labels";
  foreach(const QString& key, keys)
    {
      if (!settings.contains(key))
        {
          qDebug() << "[WARNING] Failed to find key " << key;
          return false;
        }
    }

  // Extract infos from INI file
  m_dropboxDirs["Tony"]   = settings.value("Dropbox/tonyDir").toString();
  m_dropboxDirs["Chris"]  = settings.value("Dropbox/chrisDir").toString();
  m_dropboxDirs["Gerard"] = settings.value("Dropbox/gerardDir").toString();
  m_labels                = settings.value("Sentences/labels").toStringList();

  m_isParsed = true;
  return true;
}

bool IniReader::generateExampleIniFile()
{
  QDir      applicationDir  = QApplication::applicationDirPath();
  QString   filePath        = applicationDir.absoluteFilePath("spammer.ini.example");
  QSettings settings(filePath, QSettings::IniFormat);

  settings.beginGroup("Dropbox");
  settings.setValue("tonyDir", "dir_1");
  settings.setValue("chrisDir", "dir_2");
  settings.setValue("gerardDir", "dir_3");
  settings.endGroup();

  settings.beginGroup("Sentences");
  QStringList labels = QStringList() << "label_1" << "label_2";
  settings.setValue("labels", labels);
  settings.endGroup();

  return true;
}

QString IniReader::getDropboxDir(const QString& name) const
{
  return m_dropboxDirs.find(name).value();
}

QString IniReader::getRandomSentence(const QString& name) const
{
  int min     = 0;
  int max     = m_labels.size() - 1;
  int index   = qrand() % ((max + 1) - min) + min;

  // format sentence with name if it is allowed
  QString sentence = m_labels.at(index);
  if (sentence.contains("%1"))
    sentence = sentence.arg(name);

  return sentence;
}

bool IniReader::containsSentence(const QString& sentence, const QString& name) const
{
  QString copySentence = sentence;
  if (sentence.contains(name))
    copySentence = copySentence.replace(name, QString("%1"));

  return m_labels.contains(copySentence);
}
