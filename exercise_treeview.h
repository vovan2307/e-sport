#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QObject>
#include <QTreeWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QMap>
#include <QList>

class Page_Record{
public:
    QString title, swfids;
    int id, type, parent, isdouble;
};
class Exercise_TreeView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Exercise_TreeView(QWidget *parent = 0);
    ~Exercise_TreeView();
    int error, port;
    QString error_str;
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    void readTree();
    void readPage(int pageid);
    void renamePage(QTreeWidgetItem *item);
    void buildTree();
    void parseTree();
    QString xml;
    QTreeWidgetItem *activeItem;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QMap<int, Page_Record> pagelist;
    QMap<int, QList<int> > pagetree;
    QList<int>swfids;
    bool readPageRecord(QDomNode &node, Page_Record *output);
    bool buildViewOfTree(QTreeWidgetItem *node, QList<int> &list);

signals:

public slots:
    void item_clicked(QTreeWidgetItem*,int);
    void double_clicked(QTreeWidgetItem*, int);
    void item_edited(QTreeWidgetItem*, int);
    void treeRead(QNetworkReply *reply);
    void pageRead(QNetworkReply *reply);
    void renameRead(QNetworkReply *reply);
};

#endif // TREEVIEW_H
