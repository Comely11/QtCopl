#ifndef DIALOG_H
#define DIALOG_H

#include <coremanager.h>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
QSqlDatabase db;
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void InitDataBase();
CoreManager* manager;
private slots:
    void on_btn_Login_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
