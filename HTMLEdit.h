#ifndef HTMLEDIT_H
#define HTMLEDIT_H

#include <QWidget>
#include <QPushButton>
#include <QWebView>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

class HTMLEdit : public QWidget
{
    Q_OBJECT
public:
    explicit HTMLEdit(QWidget *parent = 0);
    ~HTMLEdit();
    void editHTML();
    void viewHTML();
    QString path, name;
private:
    QLineEdit name_field;
    QPushButton save, load;
    QHBoxLayout panel;
    QWebView viewer;
    QWebView editor;
    QVBoxLayout *stack;

    void buildLayout();
signals:

public slots:
    void save_clicked();
    void load_clicked();
};

#endif // HTMLEDIT_H
