#include "dialog.h"
#include "ui_dialog.h"

#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //初始化数据库
    this->setWindowTitle("登录");
    InitDataBase();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::InitDataBase()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("managerDB");      //连接数据库名，与设置一致
    db.setUserName("root");          //数据库用户名，与设置一致
    db.setPassword("123456");    //数据库密码，与设置一致
    if(!db.open())
    {
        QMessageBox::information(this,"TIPS","数据库初始化失败");
        qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        return;
    }
    else
    {
        QMessageBox::information(this,"TIPS","数据库初始化成功");
        qDebug()<<"连接成功"<<"connect to mysql OK";
    }
}


void Dialog::on_btn_Login_clicked()
{
    QSqlQuery query(db);
    QString username = ui->line_username->text();
    QString password=ui->line_password->text();
    ui->line_password->text();
    query.exec("select Name,Password from user");
    bool T1=false;
    while(query.next())
    {
        QString user = query.value(0).toString();
        QString pass = query.value(1).toString();
      //  qDebug() << user << pass ;
        if(username.compare(user)==0&&password.compare(pass)==0){

            qDebug()<<"Check True";
            T1=true;
            this->hide();
            manager=new CoreManager(&db,user,this);
            manager->show();
        }


    }


    if(T1==false)
        QMessageBox::information(this, "警告", "用户名或密码错误");


}

