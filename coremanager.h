#ifndef COREMANAGER_H
#define COREMANAGER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QTimer>
#include <qdebug.h>
#include <addsourcedatapage.h>
#include <QMessageBox>
#include <QChart>

#include <QtCharts>

#include <QChartView>

#include <QSplineSeries>


namespace Ui {
class CoreManager;
}

class CoreManager : public QMainWindow
{
    Q_OBJECT

public:

    void initTbale();
    QString name;
    explicit CoreManager(QSqlDatabase *sqlData, QString name,QWidget *parent = nullptr);
    ~CoreManager();
    void selSourceData();

    void transactionManagement();
private slots:
    void show_menu(const QPoint pos);
    void show_menu2(const QPoint pos);
    void show_menu3(const QPoint pos);
    void UpDateTime();
    void addSourceData();
    void delSourceData();
    void updSourceData();
    void recvAddData(QString,QString,QString,QString,QString,QString,QString);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void leaveinformationFuc();
    void travelinformationFuc();
    void attendanceinformationFuc();
    void ComBoxSelectIndex(QString &str);
    void on_comboBox_currentIndexChanged(const QString &arg1);


    void ckeckWorkallow();
    void checkWorkCancel();
    void checkworkDelete();

    //-----------------
    void TransMangerTabler(int);
    void TransMangerTabler(QString,int);
    void SlectTabel(int);

    //获取部门信息插入到表格
    void getdepartMentinfo();
    void on_btn_Transmannager_pressed();

    void delDepartMentinfo();
    void updDepartMentinfo();
    void Chartinfo();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    //____________________


    void getPieSeries_1();
    void getPieSeries_2();
    void getPieSeries_3();
    void getPieSeries_4();



private:
    int status;
    addsourcedatapage *add;
    int row;
    QChart *mChart;
    QSqlDatabase sqldata;
    Ui::CoreManager *ui;
};

#endif // COREMANAGER_H
