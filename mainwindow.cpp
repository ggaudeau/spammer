#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Read settings
  if (!m_settings.parse())
    {
      qDebug() << "[CRITICAL] Failed to load INI file";
    }

  // Init timer
  m_timer = new QTimer(this);
  m_timer->setInterval(1000 * 60 * 30);  // 30 minutes
  connect(m_timer, SIGNAL(timeout()), this, SLOT(onCreateNewAlert()));
  
  m_https = new QNetworkAccessManager(this);
  connect(m_https, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
	if (m_https)
    {
      m_https->deleteLater();
      m_https = NULL;
    }
	
  delete ui;
}

// TODO
void MainWindow::sendRequest()
{
  QUrl url("https://");

  QNetworkRequest request(url);

  // request.setRawHeader("");

  // GET
  //m_https->get(request);
  // PUT
  //m_https->put(request, data);
  // POST
  //m_https->put(request, data);
}

void MainWindow::requestFinished(QNetworkReply* reply)
{
  if (reply)
    {
      if (reply->error() == QNetworkReply::NoError)
	{
	  if (reply->bytesAvailable() > 0)
	    {
	      QByteArray data = reply->readAll();
	      
	      // TODO: data -> json -> object
	    }
	}
      reply->deleteLater();
      reply = NULL;
    }
}

void MainWindow::setProxy(const QString& host, int port, const QString& username, const QString& password)
{
  if (m_https)
    {
      QNetworkProxy proxy = QNetworkProxy(QNetworkProxy::HttpProxy, host, port);
      proxy.setUser(username);
      proxy.setPassword(password);
      m_https->setProxy(proxy);
    }
}

void MainWindow::removeUniqueSentenceFileInDirectory(QDir& dir) const
{
  dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
  QFileInfoList fileInfos = dir.entryInfoList();
  if (fileInfos.count() == 1)
    {
      foreach (const QFileInfo& fileInfo, fileInfos)
      {
        if (m_settings.containsSentence(fileInfo.fileName(), m_targetName))
          {
            qDebug() << "[INFO] Remove file " << fileInfo.absoluteFilePath();
            QFile(fileInfo.absoluteFilePath()).remove();
          }
      }
    }
}

void MainWindow::onCreateNewAlert()
{
  if (!m_settings.isParsed())
    return ;

  qDebug() << "[INFO] New alert for " << m_targetName;

  // remove file only if name exists in available sentences
  removeUniqueSentenceFileInDirectory(QDir(m_targetDir));

  QString sentence = m_settings.getRandomSentence(m_targetName);
  // create file whose name is sentence (check char and length)
  if (sentence.size() >= 1 && sentence.size() < 256)
    {
      QFile filePath = QDir(m_targetDir).absoluteFilePath(sentence);
      qDebug() << "[INFO] Create file " << filePath.fileName();
      if (!filePath.open(QIODevice::WriteOnly))
        qDebug() << "[WARNING] " << filePath.errorString();
    }
}

void MainWindow::on_tonyBtn_clicked()
{
  qDebug() << "[INFO] Tony turn";
  m_timer->stop();
  m_targetName = "Tony";
  m_targetDir = m_settings.getDropboxDir(m_targetName);
  // Force first call
  onCreateNewAlert();
  // Call every 30 minutes now
  m_timer->start();
}

void MainWindow::on_chrisBtn_clicked()
{
  qDebug() << "[INFO] Chris turn";
  m_timer->stop();
  m_targetName = "Chris";
  m_targetDir = m_settings.getDropboxDir(m_targetName);
  // Force first call
  onCreateNewAlert();
  // Call every 30 minutes now
  m_timer->start();
}

void MainWindow::on_gerardBtn_clicked()
{
  qDebug() << "[INFO] Gerard turn";
  m_timer->stop();
  m_targetName = "Gerard";
  m_targetDir = m_settings.getDropboxDir(m_targetName);
  // Force first call
  onCreateNewAlert();
  // Call every 30 minutes now
  m_timer->start();
}

void MainWindow::on_inProgressBtn_clicked()
{
  qDebug() << "[INFO] Turn in progress";
  m_timer->stop();
}
