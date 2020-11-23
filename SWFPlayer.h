#ifndef SWFPLAYER_H
#define SWFPLAYER_H

#include <QWidget>
#include <QAxWidget>
#include <QSplitter>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QSlider>

class SWFPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit SWFPlayer(QWidget *parent = 0);
    ~SWFPlayer();
    void setVideo(QString path);
    void play();
private:
    bool playing;
    QString path;
    QAxWidget *player;
    QSplitter * central;
    QPushButton playbtn;// play/pause button
    QSlider play_progress;
    QHBoxLayout *control;
    QWidget *controlWidget;
    QWidget bottom;

    void buildLayout();
    void buildControl();
    bool accept_progress;
private slots:
    void playbtn_clicked();
};

#endif // SWFPLAYER_H
