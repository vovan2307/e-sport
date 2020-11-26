#include "Mpeg_Player.h"
#include "ui_mpeg_player.h"

Mpeg_Player::Mpeg_Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mpeg_player)
{
    ui->setupUi(this);
    buildLayout();
}

Mpeg_Player::~Mpeg_Player()
{
    delete ui;
}
void Mpeg_Player::play(){
    playbtn_clicked();
}
void Mpeg_Player::stop(){
    player->stop();
}
void Mpeg_Player::buildLayout(){
    central=new QSplitter(Qt::Vertical, this);

    player=new QMediaPlayer();
    player_widget = new QVideoWidget();

    player->setVideoOutput(player_widget);

    play_progress.setMinimum(0); play_progress.setMaximum(10000);
    play_progress.setValue(0); play_progress.setOrientation(Qt::Horizontal);
    play_speed.setMinimum(0); play_speed.setMaximum(100);
    play_speed.setValue(100); play_speed.setOrientation(Qt::Horizontal);

    control=new QHBoxLayout();

    central->setHandleWidth(2);
    central->setStyleSheet("QSplitter::handle:vertical { border: 1px solid blue; \
                                background: green; margin: 1px 2px;};" );
    central->resize(600, 480);
    central->addWidget(player_widget);
    central->addWidget(&play_progress);
    central->addWidget(&play_speed);
    player_widget->setStyleSheet("background-color:black;");
    player_widget->resize(600, 400);
    play_progress.resize(400, 20);
    play_speed.resize(120, 20);

    play_progress.setMaximumHeight(20);
    play_speed.setMaximumHeight(20);

    play_progress.setStyleSheet("QSlider::groove:horizontal {height: 10px; margin: 0 0;};");
    play_progress.setStyleSheet("QSlider::handle:horizontal {background-color: blue; border: 1px; height: 6px; width: 6px; margin: 0 0; border-radius:3px;}");

    buildControl();
    controlWidget=new QWidget();
    controlWidget->setLayout(control);
    controlWidget->setMaximumHeight(40);

    central->addWidget(controlWidget);
    central->addWidget(&bottom);
    bottom.setMaximumHeight(3);

    connect( player, SIGNAL(positionChanged(qint64)), this, SLOT(showPlayProgress()) );

    connect(&play_progress, SIGNAL(sliderPressed()), this, SLOT(progressBar_clicked()) );
    connect(&play_progress, SIGNAL(sliderReleased()), this, SLOT(progressBar_released()) );
    connect(&play_progress, SIGNAL(sliderMoved(int)), this, SLOT(progressBar_changed()) );

    connect(&play_speed, SIGNAL(sliderMoved(int)), this, SLOT(play_speed_changed()) );

    accept_progress=true;
    path="http://127.0.0.1/kuzia.mp4";
    this->setMinimumSize(640, 500);
}
void Mpeg_Player::buildControl(){
    backbtn.setText("back"); playbtn.setText("Play"); forwardbtn.setText("forward");
    backbtn.setEnabled(false); forwardbtn.setEnabled(false);

    prevvideobtn.setText("prev"); nextvideobtn.setText("next");
    setleftbtn.setText("Start"); setrightbtn.setText("End");
    clear_intervalbtn.setText("Clear");
    repeatbtn.setText("Repeat"); mutebtn.setText("Mute");

    prevvideobtn.setToolTip("Load previous video");
    nextvideobtn.setToolTip("Load next video");
    backbtn.setToolTip("Go to previous frame");
    forwardbtn.setToolTip("Go to next frame");
    setleftbtn.setToolTip("Set start of interval");
    setrightbtn.setToolTip("Set end of interval");
    clear_intervalbtn.setToolTip("Clear interval");
    repeatbtn.setToolTip("Repeat interval");
    mutebtn.setToolTip("Disable/Enable sound");

    control->addWidget(&prevvideobtn);

    control->addWidget(&backbtn);
    control->addWidget(&playbtn);
    control->addWidget(&forwardbtn);

    control->addWidget(&nextvideobtn);

    control->addWidget(&setleftbtn);
    control->addWidget(&setrightbtn);
    control->addWidget(&clear_intervalbtn);

    control->addWidget(&repeatbtn);
    control->addWidget(&mutebtn);

    left=right=0;repeat=false;

    connect( &playbtn, SIGNAL(clicked()), this, SLOT(playbtn_clicked()) );
    connect( &backbtn, SIGNAL(clicked()), this, SLOT(backbtn_clicked()) );
    connect( &forwardbtn, SIGNAL(clicked()), this, SLOT(forwardbtn_clicked()) );

    connect(&prevvideobtn, SIGNAL(clicked()), this, SLOT(prevvideobtn_clicked()) );
    connect(&nextvideobtn, SIGNAL(clicked()), this, SLOT(nextvideobtn_clicked()) );

    connect(&setleftbtn, SIGNAL(clicked()), this, SLOT(setleftbtn_clicked()) );
    connect(&setrightbtn, SIGNAL(clicked()), this, SLOT(setrightbtn_clicked()) );
    connect(&clear_intervalbtn, SIGNAL(clicked()), this, SLOT(clear_intervalbtn_clicked()) );

    connect(&repeatbtn, SIGNAL(clicked()), this, SLOT(repeatbtn_clicked()) );
    connect(&mutebtn, SIGNAL(clicked()), this, SLOT(mutebtn_clicked()) );
}
void Mpeg_Player::showPlayProgress(){
    if (accept_progress==false) return;

    qint64 playpos=player->position();
    qint64 duration=player->duration();

    if (playpos<0 || duration<1) return;
    playpos*=play_progress.maximum();
    playpos/=duration;

    play_progress.setValue(playpos);

}
void Mpeg_Player::progressBar_clicked(){
    accept_progress=false;
}
void Mpeg_Player::progressBar_released(){
    accept_progress=true;
}
void Mpeg_Player::progressBar_changed(){
    qint64 playpos=play_progress.value();
    qint64 duration=player->duration();
    playpos*=duration; playpos/=play_progress.maximum();
    player->setPosition(playpos);
}
void Mpeg_Player::play_speed_changed(){
    qreal speed=play_speed.value();
    speed/=100;
    player->setPlaybackRate(speed);
}
void Mpeg_Player::playbtn_clicked(){
    if (player->state()==QMediaPlayer::PlayingState){
        backbtn.setEnabled(true);forwardbtn.setEnabled(true);
        player->pause(); playbtn.setText("Play"); return;
    }
    if (player->state()==QMediaPlayer::PausedState){
        backbtn.setEnabled(false);forwardbtn.setEnabled(false);
        player->play(); playbtn.setText("Pause");return;
    }
    QUrl url=QUrl(path);
    player->setMedia(url);
    player->play();
    if (player->state()==QMediaPlayer::PlayingState){playbtn.setText("Pause");}
}
void Mpeg_Player::backbtn_clicked(){
    if (player->state()!=QMediaPlayer::PausedState) return;
}
void Mpeg_Player::forwardbtn_clicked(){
    if (player->state()!=QMediaPlayer::PausedState) return;
}
void Mpeg_Player::setleftbtn_clicked(){
    int pos=player->position();
    if (pos>=right) return;
    left=pos;
}
void Mpeg_Player::setrightbtn_clicked(){
    int pos=player->position();
    if (pos<=left) return;
    right=pos;
}
void Mpeg_Player::clear_intervalbtn_clicked(){
    left=right=0;
}
void Mpeg_Player::prevvideobtn_clicked(){}
void Mpeg_Player::nextvideobtn_clicked(){}
void Mpeg_Player::repeatbtn_clicked(){
    repeat=!repeat;
}
void Mpeg_Player::mutebtn_clicked(){
    bool muted=player->isMuted();
    player->setMuted(!muted);
}
