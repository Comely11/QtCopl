#ifndef ADDSOURCEDATAPAGE_H
#define ADDSOURCEDATAPAGE_H

#include <QWidget>
#pragma execution_character_set("utf-8");
namespace Ui {
class addsourcedatapage;
}

class addsourcedatapage : public QWidget
{
    Q_OBJECT

public:
    explicit addsourcedatapage(QWidget *parent = nullptr);
    ~addsourcedatapage();

signals:

    void SendAddData(QString,QString,QString,QString,QString,QString,QString);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addsourcedatapage *ui;
};

#endif // ADDSOURCEDATAPAGE_H
