#include "dialog.h"

#include <QApplication>

#include <QTextCodec>
int main(int argc, char *argv[])
{
  //  QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
