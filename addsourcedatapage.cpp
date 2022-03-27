#include "addsourcedatapage.h"
#include "ui_addsourcedatapage.h"

#include <QDateTime>
addsourcedatapage::addsourcedatapage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addsourcedatapage)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    setWindowFlags(Qt::WindowFullscreenButtonHint|Qt::FramelessWindowHint);
}

addsourcedatapage::~addsourcedatapage()
{
    delete ui;
}

void addsourcedatapage::on_pushButton_clicked()
{
    emit SendAddData(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_4->text(),ui->lineEdit_5->text(),ui->lineEdit_6->text(),ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),ui->lineEdit_8->text());
}


void addsourcedatapage::on_pushButton_2_clicked()
{
    this->hide();
}

