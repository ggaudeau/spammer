#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QFile>      				// create, remove file
#include <QDir>
#include <QFileInfo>  				// list directory
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>
// Own
#include "inireader.h"
#include "qlogger.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

  IniReader m_settings;
  QTimer*   m_timer;
  QString   m_targetName;
  QString   m_targetDir;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  // Tools
  void removeUniqueSentenceFileInDirectory(QDir& dir) const;

private slots:
  void onCreateNewAlert();
  // Form auto Qt connections
  void on_tonyBtn_clicked();
  void on_chrisBtn_clicked();
  void on_gerardBtn_clicked();
  void on_inProgressBtn_clicked();
  //
  void requestFinished(QNetworkReply*);
  
private:
  Ui::MainWindow *ui;
  QNetworkAccessManager* m_https;
};

#endif // MAINWINDOW_H
