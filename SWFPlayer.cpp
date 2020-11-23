#include "SWFPlayer.h"

SWFPlayer::SWFPlayer(QWidget *parent) :
    QWidget(parent)
{
    buildLayout();
}

SWFPlayer::~SWFPlayer()
{

}
void SWFPlayer::play(){

}
void SWFPlayer::buildLayout(){
    central=new QSplitter(Qt::Vertical, this);

    player=new QAxWidget();
    player->setControl("ShockwaveFlash.ShockwaveFlash");

    play_progress.setMinimum(0); play_progress.setMaximum(10000);
    play_progress.setValue(0); play_progress.setOrientation(Qt::Horizontal);

    control=new QHBoxLayout();

    central->setHandleWidth(2);
    central->setStyleSheet("QSplitter::handle:vertical { border: 1px solid blue; \
                                background: green; margin: 1px 2px;};" );
    central->resize(600, 480);
    central->addWidget(player);
    central->addWidget(&play_progress);
    play_progress.resize(400, 20);

    play_progress.setMaximumHeight(20);

    play_progress.setStyleSheet("QSlider::groove:horizontal {height: 10px; margin: 0 0;};");
    play_progress.setStyleSheet("QSlider::handle:horizontal {background-color: blue; border: 1px; height: 6px; width: 6px; margin: 0 0; border-radius:3px;}");

    buildControl();
    controlWidget=new QWidget();
    controlWidget->setLayout(control);
    controlWidget->setMaximumHeight(40);

    central->addWidget(controlWidget);
    central->addWidget(&bottom);
    bottom.setMaximumHeight(3);

    path="http://127.0.0.1/624.swf";
    this->setMinimumSize(640, 500);
}
void SWFPlayer::buildControl(){
    playbtn.setText("Play");

    control->addWidget(&playbtn);

    connect( &playbtn, SIGNAL(clicked()), this, SLOT(playbtn_clicked()) );
}
void SWFPlayer::playbtn_clicked(){
    if (playing){
        player->dynamicCall("stop()"); playing=false;
        playbtn.setText("Play"); return;
    }else{
        player->dynamicCall("play()"); playing=true;
        playbtn.setText("Pause"); return;
    }
}
void SWFPlayer::setVideo(QString path){
    this->path=path;
    player->dynamicCall("loadMovie(long, String)", 0, path);
    playbtn.setText("Pause");
}
