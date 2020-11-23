#include "Mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buildTable();
}

MainWindow::~MainWindow()
{
    QWebSettings::clearMemoryCaches();
    delete ui;
}
void MainWindow::buildTable(){
    central.setParent(ui->centralWidget);
    central.setOrientation(Qt::Horizontal);
    testChild();
    int minw=0, minh=0;
    minw=central.minimumWidth(); minh=central.minimumHeight();
    this->resize(minw+4, minh+40);
    this->setMinimumSize(minw+4, minh+40);
    //testHTML();
    //testSWF();
}
void MainWindow::testHTML(){
    QString path("http://127.0.0.1/tinymce");
    QUrl url(path);
    htmlRender=new QWebView();
    htmlRender->setUrl(url);
}
void MainWindow::testSWF(){
    /*swfRender=new QAxWidget();
    swfRender->setControl("ShockwaveFlash.ShockwaveFlash");
    swfRender->dynamicCall("loadMovie(long, String)", 0, "http://127.0.0.1/basket3.swf");
    swfRender->show();*/
    swfPlayer=new SWFPlayer();
    central.resize(600,600);
    central.addWidget(swfPlayer);
    swfPlayer->setVideo("http://127.0.0.1/624.swf");
}
void MainWindow::testChild(){
    child=new Mpeg_Player();
    int minw=0, minh=0;
    minw=child->minimumWidth(); minh=child->minimumHeight();
    central.addWidget(child);
    central.resize(minw+4, minh+4);
    central.setMinimumSize(minw+4, minh+4);
}
#include <QResizeEvent>
void MainWindow::resizeEvent(QResizeEvent *event){
    int w=this->width(), h=this->height();
    //child->resize(w, h);
}
