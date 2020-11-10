#include "mainwindow.h"

#include <QApplication>
/*#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
