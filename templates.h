#ifndef TEMPLATES_H
#define TEMPLATES_H

// Qt
#include <QList>
#include <QString>
#include <QMap>

// UNUSED !

template <typename T>
QVariantList qlist2variantlist(const QList<T> list)
{
  QVariantMap varMap;

  typename QMap<QString, T>::const_iterator cit = map.cbegin();
  while (cit != map.cend())
    {
      varMap[cit.key()] = QVariant(cit.value());
      ++cit;
    }
  return varMap;
}

template <typename T>
QVariantMap qmap2variantmap(const QMap<QString, T> map)
{
  QVariantList varList;

  typename QList<T>::const_iterator cit = list.cbegin();
  while (cit != list.cend())
    {
      varList.append(*cit);
      ++cit;
    }
  return varList;
}

#endif
