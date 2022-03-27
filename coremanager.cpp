#include "coremanager.h"
#include "ui_coremanager.h"
#include "addsourcedatapage.h"

#include <QAbstractItemView>
#include <QAbstractItemView>
#include <QMenu>
#include <QSqlRecord>


CoreManager::CoreManager(QSqlDatabase *sqlData,QString name,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CoreManager)
{
    ui->setupUi(this);
    this->sqldata=*sqlData;
    this->name=name;
    initTbale();
    selSourceData();
    getdepartMentinfo();
    transactionManagement();
    Chartinfo();
    QStringList headerText;
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setContextMenuPolicy (Qt::CustomContextMenu);
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu(QPoint)));

    disconnect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu2(QPoint)));


    ui->tableWidget_2->setContextMenuPolicy (Qt::CustomContextMenu);
    connect(ui->tableWidget_2,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu3(QPoint)));




}

//这是在用户管理的界面上添加3个ACTION
void CoreManager::show_menu(const QPoint pos)
{
    //设置菜单选项
    QMenu *menu = new QMenu(ui->tableWidget);
    QAction *addData = new QAction("添加",ui->tableWidget);
    QAction *deletData = new QAction("删除",ui->tableWidget);
    QAction *upData = new QAction("更新",ui->tableWidget);
    connect (addData,SIGNAL(triggered()),this,SLOT(addSourceData()));
    connect (upData,SIGNAL(triggered()),this,SLOT(updSourceData()));
    connect (deletData,SIGNAL(triggered()),this,SLOT(delSourceData()));
    menu->addAction(addData);
    menu->addAction(deletData);
    menu->addAction(upData);
    menu->move (cursor ().pos ());
    menu->setStyleSheet("    QMenu{background:rgba(255,255,255,1);border:none;}QMenu::item{padding:11px 32px;color:rgba(51,51,51,1);font-size:12px;}QMenu::item:hover{background-color:#409CE1;}QMenu::item:selected{background-color:#409CE1;}");
    menu->show ();
    //获得鼠标点击的x，y坐标点
    int x = pos.x ();
    int y = pos.y ();
    QModelIndex index = ui->tableWidget->indexAt (QPoint(0,y));
    row= index.data().toUInt();
    // qDebug()<<row;
}

void CoreManager::show_menu2(const QPoint pos)
{
    QMenu *menu = new QMenu(ui->tableWidget);
    QAction *addcheckData = new QAction("批准申请",ui->tableWidget);
    QAction *deletcheckData = new QAction("取消申请",ui->tableWidget);
    QAction *upcheckData = new QAction("删除申请",ui->tableWidget);
    connect (addcheckData,SIGNAL(triggered()),this,SLOT(ckeckWorkallow()));
    connect (deletcheckData,SIGNAL(triggered()),this,SLOT(checkWorkCancel()));
    connect (upcheckData,SIGNAL(triggered()),this,SLOT(checkworkDelete()));



    menu->addAction(addcheckData);
    menu->addAction(deletcheckData);
    menu->addAction(upcheckData);
    menu->move (cursor ().pos ());
      menu->setStyleSheet("    QMenu{background:rgba(255,255,255,1);border:none;}QMenu::item{padding:11px 32px;color:rgba(51,51,51,1);font-size:12px;}QMenu::item:hover{background-color:#409CE1;}QMenu::item:selected{background-color:#409CE1;}");
    menu->show ();
    //获得鼠标点击的x，y坐标点
    int x = pos.x ();
    int y = pos.y ();
    qDebug()<<x;
    QModelIndex index = ui->tableWidget->indexAt (QPoint(40,y));
    row= index.data().toUInt();
    //qDebug()<<row;
}

void CoreManager::show_menu3(const QPoint pos)
{

    QMenu *menu = new QMenu(ui->tableWidget_2);

    QAction *delDepartMentData = new QAction("删除部门",ui->tableWidget_2);
    QAction *updDepartMentData = new QAction("更新部门",ui->tableWidget_2);
    connect (updDepartMentData,SIGNAL(triggered()),this,SLOT(updDepartMentinfo()));
    connect (delDepartMentData,SIGNAL(triggered()),this,SLOT(delDepartMentinfo()));

    menu->addAction(delDepartMentData);
    menu->addAction(updDepartMentData);
    menu->move (cursor ().pos ());
      menu->setStyleSheet("    QMenu{background:rgba(255,255,255,1);border:none;}QMenu::item{padding:11px 32px;color:rgba(51,51,51,1);font-size:12px;}QMenu::item:hover{background-color:#409CE1;}QMenu::item:selected{background-color:#409CE1;}");
    menu->show ();
    //获得鼠标点击的x，y坐标点
    int x = pos.x ();
    int y = pos.y ();
    //qDebug()<<x;
    QModelIndex index = ui->tableWidget_2->indexAt (QPoint(0,y));
    row= index.data().toUInt();
    qDebug()<<"当前首行"<<row;
}



CoreManager::~CoreManager()
{
    delete ui;
}
//返回及查询信息
void CoreManager::selSourceData()
{
    QSqlQuery query(sqldata);
    query.exec("SELECT * FROM `user`");

    QSqlRecord rec = query.record();
    qDebug()<<rec.count()<<__LINE__;
    //    //设置行数
    ui->tableWidget->setRowCount(query.size());

    qDebug()<<"__________________________";
    ui->tableWidget->clear();

    QStringList headerText;
    headerText<<"编号"<<"名字"<<"Email"<<"密码"<<"权限"<<"创建时间"<<"部门"<<"手机号";
    ui->tableWidget->setHorizontalHeaderLabels(headerText);

    // QSqlQuery query(sqldata);
    query.exec("SELECT Id,Name,Email,Password,Role_id,Create_time,Department_id,Phone FROM `user`");
    int i=0;
    while(query.next())
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem( query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem( query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem( query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem( query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem( query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(5).toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(6).toString()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem( query.value(7).toString()));
        i++;
    }
    //  i=0;
}
//在人员事务管理上添加QMenu达到菜单的效果
void CoreManager::transactionManagement()
{

    QMenu *menu = new QMenu(ui->btn_Transmannager);
    QAction *leaveinformation = new QAction("请假信息",ui->btn_Transmannager);
    QAction *travelinformation = new QAction("出差信息",ui->btn_Transmannager);
    QAction *attendanceinformation = new QAction("考勤信息",ui->btn_Transmannager);
    menu->addAction(leaveinformation);
    menu->addAction(travelinformation);
    menu->addAction(attendanceinformation);

     menu->setStyleSheet("QMenu{background:rgba(255,255,255,1);border:none;border-radius:5px;}QMenu::item{padding:11px 32px;color:rgba(51,51,51,1);font-size:12px;}QMenu::item:hover{background-color:#409CE1;}QMenu::item:selected{background-color:#409CE1;}");
    ui->btn_Transmannager->setMenu(menu);

    connect (leaveinformation,SIGNAL(triggered()),this,SLOT(leaveinformationFuc()));
    connect (travelinformation,SIGNAL(triggered()),this,SLOT(travelinformationFuc()));
    connect (attendanceinformation,SIGNAL(triggered()),this,SLOT(attendanceinformationFuc()));

}
//更新标题栏的日期函数
void CoreManager::UpDateTime()
{
    setWindowTitle("欢迎你!"+name+"现在是北京时间:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void CoreManager::addSourceData()
{

    add->show();
    connect(add,&addsourcedatapage::SendAddData,this,&CoreManager::recvAddData);
}
//删除员工信息的函数
void CoreManager::delSourceData()
{
    QSqlQuery query(sqldata);
    qDebug()<<"Run Delete Data";

    QString SQL="DELETE  FROM `user` WHERE Id="+QString("%1").arg(row);
    qDebug()<< SQL;
    query.exec(SQL)? QMessageBox::information(this,"删除成功","成功删除该用户"): QMessageBox::warning(this,"删除失败","请重新尝试该操作");
    selSourceData();
}
//更新员工信息的函数
void CoreManager::updSourceData()
{
    QSqlQuery query(sqldata);
    qDebug()<<"Run UP Data";


    qDebug()<<ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),2).data().toString();
    if(!ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),2).data().toString().contains('@'))
    {
        QMessageBox::warning(this,"警告","邮箱错误,请检查是否有@符号");
        if(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),2).data().toString().length()<6)
        {
            QMessageBox::warning(this,"警告","邮箱错误,请检查长度");
        }
        else if(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),2).data().toString().length()>50)
        {
            QMessageBox::warning(this,"警告","邮箱错误,长度超过预设长度50");
        }
    }
    else
    {
        ui->tableWidget->model()->index(1,1).data().toInt();
        qDebug()<<   ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),0).data().toInt()<<__LINE__;
        QString SQL=QString("UPDATE `user`SET Name='%1',Email='%2',Password='%3',Role_id='%4',Create_time='%5',Department_id=%6,Phone=%7 WHERE Id=%8")
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),1).data().toString())
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),2).data().toString())
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),3).data().toString())
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),4).data().toString())
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),5).data().toString())
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),6).data().toInt())
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),7).data().toInt())
                .arg(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),0).data().toInt());

        qDebug()<<SQL;
        query.exec(SQL)? QMessageBox::information(this,"更新成功","成功更新该用户"): QMessageBox::warning(this,"更新失败","请重新尝试该操作");

    }
    selSourceData();
}
//添加成员员工信息的函数
void CoreManager::recvAddData( QString str1,  QString  str2, QString  str3, QString  str4, QString  str5, QString  str6,QString  str7)
{

    QSqlQuery query(sqldata);
    // qDebug()<<"Run Delete Data";

    QString SQL=QString("INSERT INTO `user`(Name,Email,Password,Role_id,Create_time,Department_id,Phone)"
                        " VALUES ('%1', '%2' , '%3', '%4', '%5', '%6','%7' )")
            .arg(str1).arg(str2).arg(str3).arg(str4).arg(str6).arg(str5).arg(str7);

    if(query.exec(SQL))
    {
        QMessageBox::information(this,"添加成功","成功添加该用户");
        add->hide();
    }
    else{
        QMessageBox::warning(this,"添加失败","请重新尝试该操作");
    };

    qDebug()<< SQL;
    selSourceData();
}
//初始化表格的函数
void CoreManager::initTbale()
{
    QTimer *timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpDateTime()));
    timer->start();
    timer->setInterval(1000);


    //第一张表是用户管理的表

    //获取数据库表的行数
    QSqlQuery query(sqldata);
    query.exec("SELECT * FROM `user`");

    QSqlRecord rec = query.record();
    qDebug()<<rec.count()<<__LINE__;

    ui->tableWidget->setColumnCount(rec.count());
    //    //设置行数
    ui->tableWidget->setRowCount(1000);

    ui->comboBox->insertItems(4,QStringList()<<"10"<<"50"<<"100"<<"200"<<"500");
    //  ui->tableWidge
    //    //去除选中虚线框
    //  ui->tableWidget->setFocusPolicy(Qt::NoFocus);

    //    //表头标题用QStringList来表示

    //    //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //    //然后设置要根据内容使用宽度的列
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    //    //设置为可以选中多个目标,按ctrl键
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位

    //    //开启交替行背景色,在设置style为交替颜色时必须开启
    ui->tableWidget->setAlternatingRowColors(true);

    //第一张表是部门管理的表




    query.exec("SELECT * FROM `department`");

    rec = query.record();
    qDebug()<<rec.count()<<__LINE__;


    QStringList headerText;
    //ui->tableWidget_2->setRowCount(5);



    ui->tableWidget_2->setColumnCount(rec.count());

    headerText<<"部门编号"<<"部门名称"<<"部门介绍"<<"创建时间"<<"用户编号"<<"创建时间";
    ui->tableWidget_2->setHorizontalHeaderLabels(headerText);
    //    //设置行数
    //  ui->tableWidget_2->setRowCount(1000);

    //  ui->tableWidge
    //    //去除选中虚线框
    //  ui->tableWidget->setFocusPolicy(Qt::NoFocus);

    //    //表头标题用QStringList来表示

    //    //x先自适应宽度
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //    //然后设置要根据内容使用宽度的列
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    //    //设置为可以选中多个目标,按ctrl键
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->tableWidget_2->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位

    //    //开启交替行背景色,在设置style为交替颜色时必须开启
    ui->tableWidget_2->setAlternatingRowColors(true);



     add=new addsourcedatapage;
}
//查询
void CoreManager::on_pushButton_clicked()
{

    qDebug()<<"void CoreManager::on_pushButton_clicked()";
    if(ui->label_2->text()== "当前位置:员工事务管理>考勤信息管理")
    {


        SlectTabel(3);
        return;
    }
    if(ui->label_2->text()== "当前位置:员工事务管理>出差信息管理")
    {


        SlectTabel(2);
        return;
    }
    if(ui->label_2->text()== "当前位置:员工事务管理>请假信息管理")
    {


        SlectTabel(1);
        return;
    }
    else
    {

        if(ui->lineEdit->text().length()!=0)
        {
            ui->tableWidget->clear();
            qDebug()<<"Run selSourceData()111;";
            QString SQL;
            QSqlQuery query(sqldata);
            QStringList headerText;
            headerText<<"编号"<<"名字"<<"Email"<<"密码"<<"权限"<<"创建时间"<<"部门"<<"手机号";
            ui->tableWidget->setHorizontalHeaderLabels(headerText);
            SQL=QString("SELECT Id,Name,Email,Password,Role_id,Create_time,Department_id,Phone FROM `user` where Name LIKE'%1%'").arg(ui->lineEdit->text());

            query.exec(SQL);
            int i=0;
            while(query.next())
            {
                ui->tableWidget->setItem(i,0,new QTableWidgetItem( query.value(0).toString()));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem( query.value(1).toString()));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem( query.value(2).toString()));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem( query.value(3).toString()));
                ui->tableWidget->setItem(i,4,new QTableWidgetItem( query.value(4).toString()));
                ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(5).toString()));
                ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(6).toString()));
                ui->tableWidget->setItem(i,7,new QTableWidgetItem( query.value(7).toString()));
                i++;
            }
        }
        else
        {
            selSourceData();
        }
    }
}

//设置页面 且刷新页面
void CoreManager::on_pushButton_2_clicked()
{
    ui->label_2->setText("当前位置:员工信息管理");
    ui->tableWidget->setColumnCount(8);
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu(QPoint)));
    disconnect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu2(QPoint)));
    selSourceData();
    ui->stackedWidget->setCurrentIndex(0);
}

//设置页面三
void CoreManager::on_pushButton_3_clicked()
{
    QSqlQuery query(sqldata);
    // qDebug()<<"Run ADD Data";


    qDebug()<<ui->textEdit->toPlainText();

    // QString SQL=QString( "INSERT INTO `managerdb`.`department`( `Name`, `Desc`, `Create_time`, `User_id`) VALUES (:str1, :str2, :str3,:str4);")
    //       .arg(ui->lineEdit_2->text()).arg(ui->textEdit->toPlainText()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->lineEdit_3->text().data());
    QString SQL=QString( "INSERT INTO `managerdb`.`department`( `Name`, `Desc`, `Create_time`, `User_id`) VALUES (:str1, :str2, :str3,:str4);");

    query.prepare(SQL);
    query.bindValue(":str1",ui->lineEdit_2->text());
    query.bindValue(":str2",ui->textEdit->toPlainText());
    query.bindValue(":str3",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":str4",ui->lineEdit_3->text());
    if(query.exec())
    {
        QMessageBox::information(this,"添加成功","成功添加该用户");
    }
    else{
        QMessageBox::warning(this,"添加失败","请重新尝试该操作");
    };

    getdepartMentinfo();
    qDebug()<<SQL;


}
//请假信息的处理函数
void CoreManager::leaveinformationFuc()
{


    qDebug()<< "请假信息";
    ui->lineEdit->clear();
    ui->stackedWidget->setCurrentIndex(0);
    // QSqlQuery query(sqldata);
    ui->label_2->setText("当前位置:员工事务管理>请假信息管理");
    status=1;
    SlectTabel(1);

}
//出差信息的处理函数
void CoreManager::travelinformationFuc()
{
    qDebug()<< "出差信息";
    ui->lineEdit->clear();
    status=2;
    ui->stackedWidget->setCurrentIndex(0);
    ui->label_2->setText("当前位置:员工事务管理>出差信息管理");
    SlectTabel(2);
}
//考勤信息的处理函数
void CoreManager::attendanceinformationFuc()
{
    qDebug()<< "考勤信息";
    status=3;
    ui->lineEdit->clear();
    ui->label_2->setText("当前位置:员工事务管理>考勤信息管理");
    ui->stackedWidget->setCurrentIndex(0);
    SlectTabel(3);
}
//查询指定行的函数
void CoreManager::ComBoxSelectIndex(QString &str)
{
    ui->tableWidget->clear();

    qDebug()<<"RUN data";
    if(ui->label_2->text()== "当前位置:员工事务管理>考勤信息管理")
    {
        qDebug()<<"Run TransMangerTabler(str,3) ";
        TransMangerTabler(str,3);
        return;
    }
    if(ui->label_2->text()== "当前位置:员工事务管理>出差信息管理")
    {
        qDebug()<<"Run TransMangerTabler(str,2) ";
        ui->lineEdit->clear();
        TransMangerTabler(str,2);
        return;
    }
    if(ui->label_2->text()== "当前位置:员工事务管理>请假信息管理")
    {
        qDebug()<<"Run TransMangerTabler(str,1) ";
        TransMangerTabler(str,1);
        return;
    }
    else
    {
        qDebug()<<"Run TransMangerTabler(str,4) ";
        QStringList headerText;
        headerText<<"编号"<<"名字"<<"Email"<<"密码"<<"权限"<<"创建时间"<<"部门"<<"手机号";
        QSqlQuery query;
        ui->tableWidget->setHorizontalHeaderLabels(headerText);
        QString SQL=QString("SELECT Id,Name,Email,Password,Role_id,Create_time,Department_id,Phone FROM `user`  limit 0,%1").arg(str.toInt());

        query.exec(SQL);
        int i=0;
        while(query.next())
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem( query.value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem( query.value(1).toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem( query.value(2).toString()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem( query.value(3).toString()));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem( query.value(4).toString()));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(5).toString()));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(6).toString()));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem( query.value(7).toString()));
            i++;
        }
    }
}
//查询指定行的函数
void CoreManager::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString str=arg1;
    ComBoxSelectIndex(str);
}

void CoreManager::ckeckWorkallow()
{

    qDebug()<<"void CoreManager::ckeckWorkallow()";
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(7);
    QStringList headerText;
    headerText<<""<<"ID"<<"名字"<<"请假原因"<<"起始时间"<<"结束时间"<<"状态";
    QSqlQuery query;
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    QString  SQL=QString("UPDATE schedule SET schedule.Status=%1 WHERE Id=%2;").arg(1).arg(row);
    qDebug()<<"_________________";
    qDebug()<<SQL;
    qDebug()<<"_________________";

    if(query.exec(SQL))
    {
        qDebug()<<"更新成功admin";
    }

    query.clear();
    SQL=QString("SELECT `schedule`.Id,`Name`,`Reason`,`Start`,`End`,`Type`,`Status` FROM `user` INNER JOIN `schedule` ON`user`.Id = `schedule`.User_id");

    query.exec(SQL);

    qDebug()<<"status this:"<<status;
    SlectTabel(status);

}

void CoreManager::checkWorkCancel()
{
    qDebug()<<"void CoreManager::checkWorkCancel()";
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(7);
    QStringList headerText;
    headerText<<""<<"ID"<<"名字"<<"请假原因"<<"起始时间"<<"结束时间"<<"状态";
    QSqlQuery query;
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    QString  SQL=QString("UPDATE schedule SET schedule.Status=%1 WHERE Id=%2;").arg(0).arg(row);
    qDebug()<<"_________________";
    qDebug()<<SQL;
    qDebug()<<"_________________";

    if(query.exec(SQL))
    {
        qDebug()<<"更新成功admin";
    }

    query.clear();
    SQL=QString("SELECT `schedule`.Id,`Name`,`Reason`,`Start`,`End`,`Type`,`Status` FROM `user` INNER JOIN `schedule` ON`user`.Id = `schedule`.User_id");
    query.exec(SQL);

    SlectTabel(status);
}

void CoreManager::checkworkDelete()
{
    qDebug()<<"void CoreManager::checkWorkCancel()";
    QSqlQuery query(sqldata);
    qDebug()<<"Run Delete Data";

    qDebug()<<"++++++++++++++++++++++++++++++++++++++";
    query.clear();
    QString SQL=QString("SELECT Id FROM `schedule` WHERE Id=%1").arg(row);

    if(status==3)
    {
        SQL=QString("SELECT Id FROM `work_check` WHERE Id=%1").arg(row);
    }
    query.prepare(SQL);
    query.exec();
    if(query.first())
    {
        QString namestr=query.value(0).toString(); //放在此处则正确
        qDebug()<<"this row line:"<<row<<"this Sql"<< namestr;
    }

    SQL="DELETE FROM `schedule` WHERE Id="+QString("%1").arg(query.value(0).toString());

    if(status==3)
    {
        SQL="DELETE FROM `work_check` WHERE Id="+QString("%1").arg(query.value(0).toString());
    }


    qDebug()<< SQL;

    query.exec(SQL)? QMessageBox::information(this,"删除成功","成功删除该用户"): QMessageBox::warning(this,"删除失败","请重新尝试该操作");
    SlectTabel(status);
}

void CoreManager::TransMangerTabler(int type)
{
}

void CoreManager::TransMangerTabler(QString str,int type)
{

    qDebug()<<"void CoreManager::TransMangerTabler(QString str,int type)";
    QStringList headerText;
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(7);
    headerText<<""<<"ID"<<"名字"<<"请假原因"<<"起始时间"<<"结束时间"<<"状态";
    QSqlQuery query;
    ui->tableWidget->setHorizontalHeaderLabels(headerText);

    QString  SQL=QString("SELECT `schedule`.Id,`Name`,`Reason`,`Start`,`End`,`Type`,`Status` FROM `user` INNER JOIN `schedule` ON`user`.Id = `schedule`.User_id  WHERE Type='%1' limit 0,%2 ;").arg(type).arg(str.toInt());
    if(type==3)
    {
        headerText.clear();
        ui->tableWidget->setColumnCount(9);
        headerText<<""<<"ID"<<"日期"<<"姓名"<<"类型"<<"上班时间"<<"下班时间"<<"工作时常"<<"备注";
        ui->tableWidget->setHorizontalHeaderLabels(headerText);
        SQL=QString("SELECT  `work_check`.Id,`Time`,`Name`,`Start_check`,`End_check`,`Work_time` FROM `user` INNER JOIN `work_check` ON`user`.Id = `work_check`.User_id  limit 0,%2 ;").arg(str.toInt());
    }

    query.exec(SQL);
    int i=0;
    while(query.next())
    {
        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Unchecked);
        ui->tableWidget->setItem(i,0,check); //插入复选框
        ui->tableWidget->setItem(i,1,new QTableWidgetItem( query.value(0).toString()));
        //query.value(1).toByteArray() 数据库存在中文 需要按照这种方式来解析
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(4).toString()));
        if((type==1)||(type==2))
        {

            if((query.value(6).toString().toLocal8Bit().toHex().toInt()==1))
            {
                ui->tableWidget->setItem(i,6,new QTableWidgetItem("已批准"));
                ui->tableWidget->item(i,6)->setTextColor(Qt::GlobalColor::darkGreen);
            }
            else
            {
                ui->tableWidget->setItem(i,6,new QTableWidgetItem("未批准"));
                ui->tableWidget->item(i,6)->setTextColor(Qt::GlobalColor::darkRed);
            }
        }
        else
        {
            ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(4).toString()));
        }

        if(type==3)
        {
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem( query.value(1).toString()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem("WorkDay"));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(3).toString()));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(4).toString()));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem(QDateTime::fromMSecsSinceEpoch(query.value(2).toDateTime().toMSecsSinceEpoch() - query.value(3).toDateTime().toMSecsSinceEpoch()).toString("hh")));
        }
        i++;
    }
}

void CoreManager::SlectTabel(int type)
{
    qDebug()<<"void CoreManager::SlectTabel(int type)";

    QSqlQuery query;

    QString  SQL;


    if(ui->lineEdit->text().length()!=0)
    {
        if(type==1)
        {
            QStringList headerText;
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(7);
            headerText<<""<<"ID"<<"名字"<<"请假原因"<<"起始时间"<<"结束时间"<<"状态";
            ui->tableWidget->setHorizontalHeaderLabels(headerText);
            qDebug()<<"______1";
            SQL=QString("SELECT `schedule`.Id,`Name`,`Reason`,`Start`,`End`,`Type`,`Status` FROM `user` INNER JOIN `schedule` ON`user`.Id = `schedule`.User_id WHERE Type=1 AND `Name` LIKE '%1%'").arg(ui->lineEdit->text());
        }
        else if(type==2)
        {
            QStringList headerText;
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(7);
            headerText<<""<<"ID"<<"名字"<<"出差原因"<<"起始时间"<<"结束时间"<<"状态";
            ui->tableWidget->setHorizontalHeaderLabels(headerText);
            qDebug()<<"______2";
            SQL=QString("SELECT `schedule`.Id,`Name`,`Reason`,`Start`,`End`,`Type`,`Status` FROM `user` INNER JOIN `schedule` ON`user`.Id = `schedule`.User_id WHERE Type=2 AND `Name` LIKE '%1%'").arg(ui->lineEdit->text());
        }
        else if(type==3)
        {
            qDebug()<<"Run select tyoe";
            QStringList headerText;
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(9);
            headerText<<""<<"ID"<<"日期"<<"姓名"<<"类型"<<"上班时间"<<"下班时间"<<"工作时常"<<"备注";
            ui->tableWidget->setHorizontalHeaderLabels(headerText);
            qDebug()<<"______3";
            SQL=QString("SELECT  `work_check`.Id,`Time`,`Name`,`Start_check`,`End_check`,`Work_time` FROM `user` INNER JOIN `work_check` ON`user`.Id = `work_check`.User_id WHERE `Name` LIKE '%1%'").arg(ui->lineEdit->text());

        }

        query.clear();
        query.exec(SQL);

        if(query.size()<=0)
        {
            QMessageBox::information(this,"提示","暂无数据需要手动添加");
        }
        int i=0;
        while(query.next())
        {


            QTableWidgetItem *check=new QTableWidgetItem;
            check->setCheckState (Qt::Unchecked);
            ui->tableWidget->setItem(i,0,check); //插入复选框
            ui->tableWidget->setItem(i,1,new QTableWidgetItem( query.value(0).toString()));
            //QString::fromLocal8Bit(query.value(1).toByteArray() 数据库存在中文 需要按照这种方式来解析
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem( query.value(3).toString()));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(4).toString()));

            if((type==1)||(type==2))
            {

                if((query.value(6).toString().toLocal8Bit().toHex().toInt()==1))
                {
                    ui->tableWidget->setItem(i,6,new QTableWidgetItem("已批准"));
                    ui->tableWidget->item(i,6)->setTextColor(Qt::GlobalColor::darkGreen);
                }
                else
                {
                    ui->tableWidget->setItem(i,6,new QTableWidgetItem("未批准"));
                    ui->tableWidget->item(i,6)->setTextColor(Qt::GlobalColor::darkRed);
                }
            }
            else
            {
                ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(4).toString()));
            }


            if(type==3)
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
                ui->tableWidget->setItem(i,4,new QTableWidgetItem("WorkDay"));
                ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(3).toString()));
                ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(4).toString()));
                ui->tableWidget->setItem(i,7,new QTableWidgetItem(QDateTime::fromMSecsSinceEpoch(query.value(2).toDateTime().toMSecsSinceEpoch() - query.value(3).toDateTime().toMSecsSinceEpoch()).toString("hh")));
            }
            i++;
        }




    }
    else
    {
        if(type==1)
        {
            QStringList headerText;
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(7);
            query.exec("SELECT * FROM `schedule`");

            QSqlRecord rec = query.record();
            qDebug()<<rec.count()<<__LINE__;
            //    //设置行数
            ui->tableWidget->setRowCount(query.size());
            headerText<<""<<"ID"<<"名字"<<"请假原因"<<"起始时间"<<"结束时间"<<"状态";
            ui->tableWidget->setHorizontalHeaderLabels(headerText);
            qDebug()<<"______1";
            SQL=QString("SELECT `schedule`.Id,`Name`,`Reason`,`Start`,`End`,`Type`,`Status` FROM `user` INNER JOIN `schedule` ON`user`.Id = `schedule`.User_id  WHERE Type='%1'").arg(type);
        }
        else if(type==2)
        {
            QStringList headerText;
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(7);
            query.exec("SELECT * FROM `schedule`");

            QSqlRecord rec = query.record();
            qDebug()<<rec.count()<<__LINE__;
            //    //设置行数
            ui->tableWidget->setRowCount(query.size());
            headerText<<""<<"ID"<<"名字"<<"出差原因"<<"起始时间"<<"结束时间"<<"状态";
            ui->tableWidget->setHorizontalHeaderLabels(headerText);
            qDebug()<<"______2";
            SQL=QString("SELECT `schedule`.Id,`Name`,`Reason`,`Start`,`End`,`Type`,`Status` FROM `user` INNER JOIN `schedule` ON`user`.Id = `schedule`.User_id  WHERE Type='%1'").arg(type);
        }
        else if(type==3)
        {
            QStringList headerText;
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(9);
            query.exec("SELECT * FROM `work_check`");

            QSqlRecord rec = query.record();
            qDebug()<<rec.count()<<__LINE__;
            //    //设置行数
            ui->tableWidget->setRowCount(query.size());
            headerText<<""<<"ID"<<"日期"<<"姓名"<<"类型"<<"上班时间"<<"下班时间"<<"工作时常"<<"备注";
            ui->tableWidget->setHorizontalHeaderLabels(headerText);
            qDebug()<<"______3";
            SQL=QString("SELECT  `work_check`.Id,`Time`,`Name`,`Start_check`,`End_check`,`Work_time` FROM `user` INNER JOIN `work_check` ON`user`.Id = `work_check`.User_id ");
        }

        query.exec(SQL);

        qDebug()<<SQL;

        if(query.size()<=0)
        {
            QMessageBox::information(this,"提示","暂无数据需要手动添加");
        }
        int i=0;
        while(query.next())
        {


            QTableWidgetItem *check=new QTableWidgetItem;
            check->setCheckState (Qt::Unchecked);
            ui->tableWidget->setItem(i,0,check); //插入复选框
            ui->tableWidget->setItem(i,1,new QTableWidgetItem( query.value(0).toString()));
            //QString::fromLocal8Bit(query.value(1).toByteArray() 数据库存在中文 需要按照这种方式来解析
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem( query.value(3).toString()));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(4).toString()));

            if((type==1)||(type==2))
            {
                qDebug()<<"``````"<<query.value(6).toString().toLocal8Bit().toHex().toInt();
                if((query.value(6).toString().toLocal8Bit().toHex().toInt()==1))
                {
                    ui->tableWidget->setItem(i,6,new QTableWidgetItem("已批准"));
                    ui->tableWidget->item(i,6)->setTextColor(Qt::GlobalColor::darkGreen);
                }
                else
                {
                    ui->tableWidget->setItem(i,6,new QTableWidgetItem("未批准"));
                    ui->tableWidget->item(i,6)->setTextColor(Qt::GlobalColor::darkRed);
                }
            }
            else
            {
                ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(4).toString()));
            }


            if(type==3)
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem( query.value(1).toString()));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(2).toString()));
                ui->tableWidget->setItem(i,4,new QTableWidgetItem("WorkDay"));
                ui->tableWidget->setItem(i,5,new QTableWidgetItem( query.value(3).toString()));
                ui->tableWidget->setItem(i,6,new QTableWidgetItem( query.value(4).toString()));
                ui->tableWidget->setItem(i,7,new QTableWidgetItem(QDateTime::fromMSecsSinceEpoch(query.value(2).toDateTime().toMSecsSinceEpoch() - query.value(3).toDateTime().toMSecsSinceEpoch()).toString("hh")));
            }
            i++;
        }
    }
}

void CoreManager::getdepartMentinfo()
{
    QSqlQuery query(sqldata);
    query.exec("SELECT * FROM `department`");

    QSqlRecord rec = query.record();
    qDebug()<<rec.count()<<__LINE__;
    //    //设置行数
    ui->tableWidget_2->setRowCount(query.size());

    qDebug()<<"__________________________";
    ui->tableWidget_2->clear();

    QStringList headerText;
    headerText<<"部门编号"<<"部门名称"<<"部门介绍"<<"创建时间"<<"用户编号";
    ui->tableWidget_2->setHorizontalHeaderLabels(headerText);

    // QSqlQuery query(sqldata);
    query.exec("SELECT *  FROM `department`");
    int i=0;
    while(query.next())
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        i++;
    }
}


void CoreManager::on_btn_Transmannager_pressed()
{
    qDebug()<<"run :on_btn_Transmannager_clicked()";
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu2(QPoint)),Qt::UniqueConnection);

    disconnect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu(QPoint)));
}

void CoreManager::delDepartMentinfo()
{

    qDebug()<<"void CoreManager::delDepartMentinfo()";
    QSqlQuery query(sqldata);
    qDebug()<<"Run delDepartMentinfo";

    qDebug()<<"++++++++++++++++++++++++++++++++++++++";
    query.clear();

    QString  SQL= QString("DELETE FROM department WHERE Id =%1").arg(row);
    qDebug()<<SQL;
    if(query.exec(SQL))
    {
        QMessageBox::information(this,"TIPS","删除成功");
    }
    else
    {
        QMessageBox::warning(this,"TIPS","删除失败");
    }
    getdepartMentinfo();
}

void CoreManager::updDepartMentinfo()
{
    qDebug()<<"void CoreManager::updDepartMentinfo()";
    QSqlQuery query(sqldata);
    qDebug()<<"Run updDepartMentinfo()";

    qDebug()<<"++++++++++++++++++++++++++++++++++++++";
    query.clear();

    QString  SQL= QString("UPDATE department SET `Name`='%1',`Desc`='%2',Create_time= '%3' ,User_id=%4 WHERE Id =%5")
            .arg(ui->tableWidget_2->model()->index(ui->tableWidget_2->currentIndex().row(),1).data().toString())
            .arg(ui->tableWidget_2->model()->index(ui->tableWidget_2->currentIndex().row(),2).data().toString())
            .arg(ui->tableWidget_2->model()->index(ui->tableWidget_2->currentIndex().row(),3).data().toString())
            .arg(ui->tableWidget_2->model()->index(ui->tableWidget_2->currentIndex().row(),4).data().toString()).arg(row);
    qDebug()<<SQL;
    if(query.exec(SQL))
    {
        QMessageBox::information(this,"TIPS","更新成功");
    }
    else
    {
        QMessageBox::warning(this,"TIPS","更新失败");
    }
    getdepartMentinfo();
}

void CoreManager::Chartinfo()
{


    getPieSeries_1();
    getPieSeries_2();
    getPieSeries_3();
    getPieSeries_4();


    //      chartView->resize(100, 100);
    //      chartView2->resize(100, 100);
    //      chartView3->resize(100, 100);
    //      chartView4->resize(100, 100);


}




//添加部门
void CoreManager::on_pushButton_4_clicked()
{

    ui->label_2->setText("当前位置:部门管理");
    ui->stackedWidget->setCurrentIndex(1);
}


void CoreManager::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
//Chartinfo();
}

void CoreManager::getPieSeries_1()
{



    qDebug()<<"void getPieSeries_1()";
    QSqlQuery query(sqldata);
    qDebug()<<"Run getPieSeries_1()";

    qDebug()<<"++++++++++++++++++++++++++++++++++++++";
    query.clear();

    QPieSeries *series = new QPieSeries();

    QString  SQL= QString(" select department.`Name` ,COUNT(*) from work_check,department WHERE work_check.User_id=department.User_id group by work_check.User_id;");

    qDebug()<<SQL;
    if(query.exec(SQL))
    {
        int i=0;
        while(query.next())
        {
            qDebug()<<"部门信息"<<query.value(0).toString()<<"部门打卡数"<<query.value(1).toString();
            series->append(QString(query.value(0).toString()+"部门打卡数"+query.value(1).toString()), query.value(1).toInt());
            QPieSlice *slice = series->slices().at(i);
            //   slice->setExploded();
            slice->setLabelVisible();
            i++;
        }
    }
    else
    {
        QMessageBox::warning(this,"TIPS","更新失败");
    }

    //   QPieSlice *slice = series->slices().at(2);
    // slice->setExploded();
    //slice->setLabelVisible();
    //slice->setPen(QPen(Qt::darkGreen, 2));
    //slice->setBrush(Qt::green);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("部门月考勤记录统计");
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    ui->horizontalLayout_5->addWidget(chartView);

}

void CoreManager::getPieSeries_2()
{
    qDebug()<<"void getPieSeries_1()";
    QSqlQuery query(sqldata);
    qDebug()<<"Run getPieSeries_1()";

    qDebug()<<"++++++++++++++++++++++++++++++++++++++";
    query.clear();

    QPieSeries *series = new QPieSeries();

    QString  SQL= QString("SELECT  c.`Name`,COUNT(*) AS '出差总数' FROM `user` a RIGHT JOIN `schedule` b  ON a.Id =b.User_id RIGHT JOIN department c ON c.Id=a.Department_id  WHERE b.`Status`=1 GROUP BY a.Id");

    qDebug()<<SQL;
    if(query.exec(SQL))
    {
        int i=0;
        while(query.next())
        {
            qDebug()<<"部门信息"<<query.value(0).toString()<<"数"<<query.value(1).toString();
            series->append(QString(query.value(0).toString()+"请假数"+query.value(1).toString()), query.value(1).toInt());
            QPieSlice *slice = series->slices().at(i);
            //   slice->setExploded();
            slice->setLabelVisible();
            i++;
        }
    }
    else
    {
        QMessageBox::warning(this,"TIPS","更新失败");
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("请假记录统计");
    chart->legend()->hide();

    QChartView *chartView2 = new QChartView(chart);
    chartView2->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_6->addWidget(chartView2);


}

void CoreManager::getPieSeries_3()
{
    qDebug()<<"void getPieSeries_3()";
    QSqlQuery query(sqldata);
    qDebug()<<"Run getPieSeries_3()";

    qDebug()<<"++++++++++++++++++++++++++++++++++++++";
    query.clear();

    QPieSeries *series = new QPieSeries();

    QString  SQL= QString("SELECT c.`Name`,COUNT(c.Id)AS'部门出差人数' FROM `user` a RIGHT JOIN `schedule` b  ON a.Id =b.User_id RIGHT JOIN department c ON c.Id=a.Department_id  WHERE b.`Status`=1 AND b.Type =2 GROUP BY  c.Id ");

    qDebug()<<SQL;
    if(query.exec(SQL))
    {
        int i=0;
        while(query.next())
        {
            qDebug()<<"部门信息"<<query.value(0).toString()<<"数"<<query.value(1).toString();
            series->append(QString(query.value(0).toString()+"出差数"+query.value(1).toString()), query.value(1).toInt());
            QPieSlice *slice = series->slices().at(i);
            //   slice->setExploded();
            slice->setLabelVisible();
            i++;
        }
    }
    else
    {
        QMessageBox::warning(this,"TIPS","更新失败");
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("出差记录统计");
    chart->legend()->hide();

    QChartView *chartView3 = new QChartView(chart);
    chartView3->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_7->addWidget(chartView3);


}

void CoreManager::getPieSeries_4()
{



    qDebug()<<"void getPieSeries_4()";
    QSqlQuery query(sqldata);
    qDebug()<<"Run getPieSeries_4()";

    qDebug()<<"++++++++++++++++++++++++++++++++++++++";
    query.clear();

    QPieSeries *series = new QPieSeries();

    QString  SQL= QString("SELECT b.`Name`,count(a.Id) FROM `user` a RIGHT JOIN department b ON a.Department_id = b.Id GROUP BY b.Id");

    qDebug()<<SQL;
    if(query.exec(SQL))
    {
        int i=0;
        while(query.next())
        {
            qDebug()<<"部门信息"<<query.value(0).toString()<<"数"<<query.value(1).toString();
            series->append(QString(query.value(0).toString()+"部门人数"+query.value(1).toString()), query.value(1).toInt());
            QPieSlice *slice = series->slices().at(i);
            //   slice->setExploded();
            slice->setLabelVisible();
            i++;
        }
    }
    else
    {
        QMessageBox::warning(this,"TIPS","更新失败");
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("综合统计");
    chart->legend()->hide();

    QChartView *chartView4 = new QChartView(chart);
    chartView4->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_8->addWidget(chartView4);


}



