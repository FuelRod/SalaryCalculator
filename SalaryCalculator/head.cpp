#include "head.h"
#include "ui_head.h"

Head::Head(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Head)
{
    ui->setupUi(this);

    //禁止拖拽
    setFixedSize(this->width(),this->height());
}

Head::~Head()
{
    delete ui;
}
