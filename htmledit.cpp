#include "HTMLEdit.h"

HTMLEdit::HTMLEdit(QWidget *parent) : QWidget(parent)
{
    buildLayout();
}
HTMLEdit::~HTMLEdit(){

}
void HTMLEdit::buildLayout(){
    panel.addWidget(&name);
    panel.addWidget(&save);
    stack.addLayout(&panel);
    stack.addWidget(&viewer);
    this->setLayout(&stack);
}
#include <QWebFrame>
void HTMLEdit::editHTML(){
    QString arg="readFile('";
    arg+=path; arg+="');";

    viewer.page()->mainFrame()->evaluateJavaScript(arg);
}
void HTMLEdit::viewHTML(){
    viewer.setUrl(path);
}
void HTMLEdit::save_clicked(){
    QString arg="saveFile('";
    arg+=path; arg+="');";
    viewer.page()->mainFrame()->evaluateJavaScript(arg);
}
