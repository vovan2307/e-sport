#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QSslSocket>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QHBoxLayout>
#include <QByteArray>
#include <QFile>
#include <QBuffer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testmp4();
}
void MainWindow::testmp4(){
    player = new QMediaPlayer;
    QMediaPlaylist *playlist = new QMediaPlaylist;
    QVideoWidget *videoWidget = new QVideoWidget;

    player->setPlaylist(playlist);
    player->setVideoOutput(videoWidget);
    //E:\\HTTP_Server\\home\\localhost\\www\\624.swf
    //E:\\Films\\Gruz_200_480.mp4
    playlist->addMedia(QUrl::fromLocalFile("E:\\HTTP_Server\\home\\localhost\\www\\624.swf"));

    videoWidget->show();
    playlist->setCurrentIndex(0);
    player->play();

    ui->verticalLayout->addWidget(videoWidget);

    qDebug() << "mediaStatus: " << player->mediaStatus() << "error: " << player->error();
}
void MainWindow::testswf(){

}
MainWindow::~MainWindow()
{
    delete ui;
}

