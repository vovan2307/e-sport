#ifndef MPEG_PLAYER_H
#define MPEG_PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QSlider>
#include <QSplitter>

namespace Ui {
class mpeg_player;
}

class Mpeg_Player : public QWidget
{
    Q_OBJECT

public:
    explicit Mpeg_Player(QWidget *parent = 0);
    ~Mpeg_Player();
    QString path;
    void play();
    void stop();
private:
    Ui::mpeg_player *ui;
    QMediaPlayer *player;
    QVideoWidget *player_widget;
    QSplitter * central;
    QPushButton setleftbtn, setrightbtn, clear_intervalbtn;
    QPushButton prevvideobtn, nextvideobtn;
    QPushButton repeatbtn, mutebtn;
    QPushButton backbtn, forwardbtn;
    QPushButton playbtn;// play/pause button
    QSlider play_progress, play_speed;
    QHBoxLayout *control;
    QWidget *controlWidget;
    QWidget bottom;

    qint64 left, right;
    bool repeat;

    void buildLayout();
    void buildControl();
    bool accept_progress;
private slots:
    void showPlayProgress();
    void progressBar_clicked();
    void progressBar_released();
    void progressBar_changed();
    void play_speed_changed();

    void setleftbtn_clicked();
    void setrightbtn_clicked();
    void clear_intervalbtn_clicked();

    void prevvideobtn_clicked();
    void nextvideobtn_clicked();

    void repeatbtn_clicked();
    void mutebtn_clicked();

    void playbtn_clicked();
    void backbtn_clicked();
    void forwardbtn_clicked();
};

#endif // MPEG_PLAYER_H
