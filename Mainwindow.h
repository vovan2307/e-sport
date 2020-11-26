#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QSplitter>
#include "Mpeg_Player.h"
#include "SWFPlayer.h"
#include "htmledit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //QWebView *htmlRender;
    HTMLEdit *htmlRender;

    Mpeg_Player *child;
    SWFPlayer *swfPlayer;
    QSplitter central;

    void buildTable();
    void testHTML();
    void testMPEG();
    void testSWF();
    void testChild();
    void testHTTP();
protected:
    virtual void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
