#include "exercise_treeview.h"

Exercise_TreeView::Exercise_TreeView(QWidget *parent) : QTreeWidget(parent)
{
    activeItem=0;
    buildTree();
}
Exercise_TreeView::~Exercise_TreeView(){}
#include <QThread>

void Exercise_TreeView::buildTree(){
    setColumnCount(1);
    port=8680;
    this->headerItem()->setText(0, "");
    readTree();
    this->setStyleSheet(
        "QTreeView::item:selected:active{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
         stop: 0 #6ea1f1, stop: 1 #567dbc);}"
    );
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(item_clicked(QTreeWidgetItem*,int)) );
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(double_clicked(QTreeWidgetItem*,int)) );
};
void Exercise_TreeView::readTree(){
    QString contentType="application/x-www-form-urlencoded";
    QString url="http://127.0.0.1:";
    url+=QString("%1").arg(port); url+="/page";

    QString body="operation=getPageTree";
    QByteArray rawdata=body.toUtf8();

    manager=new QNetworkAccessManager();
    request=new QNetworkRequest();

    request->setUrl(url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(treeRead(QNetworkReply*)) );
    manager->post(request[0], rawdata);
}
void Exercise_TreeView::treeRead(QNetworkReply *reply){
    this->error=0;
    if (reply->error()){
        error=reply->error(); reply->close();
        return;
    }
    xml=reply->readAll(); reply->close();
    parseTree();
}
void Exercise_TreeView::parseTree(){
    QDomDocument doc;
    doc.setContent(xml);
    QDomNodeList list=doc.elementsByTagName("page");
    int count=list.count();
    count=count;
    QDomNode node;

    Page_Record record;
    for (int i=0;i<count;i++){
        node=list.at(i);
        readPageRecord(node, &record);
        pagelist.insert(record.id, record);
        if (pagetree.contains(record.parent)){ pagetree[record.parent].append(record.id); continue; }
        QList<int> list;
        list.append(record.id);
        pagetree.insert(record.parent, list);
    }
    count=pagetree[0].count();

    for (int i=0;i<count;i++){
        QTreeWidgetItem *level0=new QTreeWidgetItem(this);
        record=pagelist[pagetree[0][i]];
        level0->setData(0, Qt::UserRole, record.id);
        level0->setText(0, record.title);
        this->addTopLevelItem(level0);
        if (record.type==0) buildViewOfTree(level0, pagetree[record.id]);
    }
}
bool Exercise_TreeView::readPageRecord(QDomNode &node, Page_Record *output){
    QDomNode parent=node.parentNode();
    QString key="", val="";
    QDomNamedNodeMap attr=node.attributes();

    key="title";output->title=attr.namedItem(key).nodeValue();
    key="id"; val=attr.namedItem(key).nodeValue(); output->id=val.toInt();
    key="type"; val=attr.namedItem(key).nodeValue(); output->type=val.toInt();

    output->parent=output->isdouble=0;
    if (parent.isNull()) return true;
    key="id"; val=parent.attributes().namedItem(key).nodeValue(); output->parent=val.toInt();
    return true;
}
bool Exercise_TreeView::buildViewOfTree(QTreeWidgetItem *node, QList<int> &list){
    int count=list.count();
    Page_Record record;
    for (int i=0;i<count;i++){
        record=pagelist[list[i]];
        QTreeWidgetItem *item=new QTreeWidgetItem(node);
        item->setData(0, Qt::UserRole, record.id);
        item->setText(0, record.title);
        node->addChild(item);
        if (record.type==0) buildViewOfTree(item, pagetree[record.id]);
    }
    return true;
}
#include <QMessageBox>
void Exercise_TreeView::item_clicked(QTreeWidgetItem *item, int param){
    item=item;
    int id=item->data(0, Qt::UserRole).toInt();
    readPage(id);
}
void Exercise_TreeView::double_clicked(QTreeWidgetItem *item, int param){
    if (activeItem) return;
    this->openPersistentEditor(item, 0);
    activeItem=item;
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(item_edited(QTreeWidgetItem*,int)) );
}
void Exercise_TreeView::item_edited(QTreeWidgetItem *item, int param){
    this->closePersistentEditor(item, 0);
    activeItem=0;
    disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(item_edited(QTreeWidgetItem*,int)) );
    renamePage(item);
}
void Exercise_TreeView::readPage(int pageid){
    Page_Record record=pagelist[pageid];
    if (record.type!=2) return;

    QString contentType="application/x-www-form-urlencoded";
    QString url="http://127.0.0.1:";
    url+=QString("%1").arg(port); url+="/page";

    QString body="operation=getPage&id=";
    body+=QString("%1").arg(pageid);
    QByteArray rawdata=body.toUtf8();

    delete manager; delete request;
    manager=new QNetworkAccessManager();
    request=new QNetworkRequest();

    request->setUrl(url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(pageRead(QNetworkReply*)) );
    manager->post(request[0], rawdata);
}
void Exercise_TreeView::pageRead(QNetworkReply *reply){
    this->error=0;
    if (reply->error()){
        error=reply->error(); reply->close();
        return;
    }
    xml=reply->readAll(); reply->close();
    QDomDocument doc;
    doc.setContent(xml);
    QDomNode node=doc.elementsByTagName("swfContent").at(0);
    QString str=node.firstChild().nodeValue();
    QStringList list = str.split(",", QString::SkipEmptyParts);
    QList<int>ids;

    for (int i=0;i<list.count();i++) ids.append(list.at(i).toInt());
    swfids=ids;
}
#include <QUrlQuery>
void Exercise_TreeView::renamePage(QTreeWidgetItem *item){
    int id=item->data(0, Qt::UserRole).toInt();
    Page_Record record=pagelist[id];
    record.title=item->text(0); pagelist[id].title=record.title;

    delete manager; delete request;
    manager=new QNetworkAccessManager();
    request=new QNetworkRequest();

    QString url="http://127.0.0.1:";
    url+=QString("%1").arg(port); url+="/page";
    QString contentType="application/x-www-form-urlencoded";
    request->setUrl(url);
    request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QUrlQuery params;
    params.addQueryItem("operation","savePage");
    params.addQueryItem("id", QString("%1").arg(id));
    params.addQueryItem("type",QString("%1").arg(record.type));
    params.addQueryItem("title", record.title);
    QString query=params.toString(QUrl::FullyEncoded);
    QByteArray rawdata=query.toUtf8();
    rawdata=rawdata;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(renameRead(QNetworkReply*)) );
    manager->post(request[0], rawdata);
}
void Exercise_TreeView::renameRead(QNetworkReply *reply){
    this->error=0;
    if (reply->error()){
        error=reply->error(); error_str=reply->errorString(); reply->close();
        return;
    }
    xml=reply->readAll(); reply->close();
    xml=xml;
}
#include <QKeyEvent>
void Exercise_TreeView::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    key=key;
    event->ignore();
    if (key==Qt::Key_Escape){
        if (activeItem){ this->closePersistentEditor(activeItem); activeItem=0;}
    }
    if (key=='+'){
        key=key;
    }
    if (key==Qt::Key_Delete){

    }
}
