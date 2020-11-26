#include "HTMLEdit.h"

HTMLEdit::HTMLEdit(QWidget *parent) : QWidget(parent)
{
    buildLayout();
}
HTMLEdit::~HTMLEdit(){

}
void HTMLEdit::buildLayout(){
    stack=new QVBoxLayout();

    save.setText("Save"); load.setText("Load");

    editor.setUrl(QString("http://127.0.0.1/tinymce"));
    editor.hide();
    viewer.show();

    panel.addWidget(&name_field);
    panel.addWidget(&load);
    panel.addWidget(&save);

    stack->addLayout(&panel);
    stack->addWidget(&viewer);
    stack->addWidget(&editor);

    this->setLayout(stack);

    connect(&load, SIGNAL(clicked(bool)), this, SLOT(load_clicked()) );
    connect(&save, SIGNAL(clicked(bool)), this, SLOT(save_clicked()) );
}
#include <QWebFrame>
void HTMLEdit::editHTML(){
    name_field.setText(name);
    QString arg="readFile('";
    arg+=path; arg+="');";

    editor.page()->mainFrame()->evaluateJavaScript(arg);
}
void HTMLEdit::viewHTML(){
    editor.hide();
    viewer.show();
    QString arg="http://127.0.0.1";
    arg+=path;
    viewer.setUrl(path);
}
void HTMLEdit::save_clicked(){
    name=name_field.text();
    name=name.replace("'", "\\'");
    QString arg="saveFile('";
    arg+=path; arg+="','"; arg+=name; arg+="');";
    editor.page()->mainFrame()->evaluateJavaScript(arg);
}

void HTMLEdit::load_clicked(){
    viewer.hide();
    editor.show();
    editHTML();
}
