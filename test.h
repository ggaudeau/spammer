#ifndef TEST_H
#define TEST_H

// Qt
#include <QObject>
#include <QString>
#include <QStringList>
//
#include <QByteArray>
#include <QJsonDocument>
#include <QVariantMap>
// Own
#include "qlogger.h"
#include "qobjecthelper.h"

class Test : public QObject
{
  Q_OBJECT
    
  Q_ENUMS(EnumType)
  Q_PROPERTY(EnumType type READ getType WRITE setType)
  Q_PROPERTY(QString str READ getStr WRITE setStr)
  Q_PROPERTY(QStringList strLst READ getStrLst WRITE setStrLst)
  Q_PROPERTY(quint64 number READ getNumber WRITE setNumber)
  Q_PROPERTY(qreal floatting READ getFloatting WRITE setFloatting)

public:
  enum EnumType
  {
    eNone = 0,
    eReady
  };

  EnumType	m_type;
  QString	m_str;
  QStringList	m_strLst;
  quint64	m_number;
  qreal		m_floatting;
    
  EnumType	getType() const { return m_type; }
  void		setType(EnumType type) { m_type = type; }
  QString	getStr() const { return m_str; }
  void		setStr(const QString& str) { m_str = str; }
  QStringList	getStrLst() const { return m_strLst; }
  void		setStrLst(const QStringList& strLst) { m_strLst = strLst; }
  quint64	getNumber() const { return m_number; }
  void		setNumber(quint64 number) { m_number = number; }
  qreal		getFloatting() const { return m_floatting; }
  void		setFloatting(qreal floatting) { m_floatting = floatting; }  

  Test()
    : m_type(eReady)
    , m_str("Super")
    , m_strLst(QStringList() << "vive" << "la" << "France" << "!")
    , m_number(42)
    , m_floatting(3.14159)
    {
      QLogger::QLog_Debug(THREAD_ID, "Construct instance of Test's class");
    }

  QByteArray serialize()
  {
    QVariantMap		resultMap;
    QJsonDocument	jsonDocument;

    QJson::QObjectHelper::qobject2qvariant(this, QStringList("objectName"));
    jsonDocument = QJsonDocument::fromVariant(resultMap);
    enum QJsonDocument::JsonFormat fmt = QJsonDocument::Indented; // QJsonDocument::Compact
    return jsonDocument.toJson(fmt);
  }

  void deserialize(const QByteArray& jsonData)
  {
    const QJsonDocument jsonDocument(QJsonDocument::fromJson(jsonData));
    const QVariantMap variantMap(jsonDocument.toVariant().toMap());
    QJson::QObjectHelper::qvariant2qobject(variantMap, this);
  }
};

Q_DECLARE_METATYPE(Test::EnumType)

#endif
