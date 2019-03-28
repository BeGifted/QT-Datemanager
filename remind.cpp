#include "remind.h"
#include "ui_remind.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

remind::remind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remind)
{
    ui->setupUi(this);
    connect(&this->ptimer , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay()));

    if(readFromFile() == -1){
        QMessageBox::critical(this, "ERROR","文件打开失败");
        this->close();
    }

    QDateTime current = QDateTime::currentDateTime();
    QString cur = current.toString("yyyy MM dd");       //当前日期
    QTime current1 =QTime::currentTime();
    QString cur1 = current1.toString("hh mm ss");

    //h,m,s为当前时间
    h = current1.toString("hh");
    m = current1.toString("mm");
    s = current1.toString("ss");

    this->baseTime = QTime::currentTime();

    int i;
    qDebug() << cur;

    for (i = 0;i < date_lines.length();i++) {         //遍历所有日程
        QString line = date_lines.at(i);              //一行的日程
        line = line.trimmed();                              //去除开头结尾空白字符串
        QStringList subs = line.split(' ');           //标准化
        QString date = subs.at(1) + " " + subs.at(2) + " " + subs.at(3);  //日程中的几年几月几日
        QString time = subs.at(4) + " " + subs.at(5);
        if(date == cur) {                                      //如果日期吻合
            if(subs.at(11) == "活动开始前") {
                updateDateTimeAndDisplay(0);
            }else if (subs.at(11) == "5分钟前") {
                updateDateTimeAndDisplay(1);
            }else if (subs.at(11) == "10分钟前") {
                updateDateTimeAndDisplay(2);
            }else if (subs.at(11) == "15分钟前") {
                updateDateTimeAndDisplay(3);
            }else if (subs.at(11) == "30分钟前") {
                updateDateTimeAndDisplay(4);
            }else if (subs.at(11) == "1小时前") {
                updateDateTimeAndDisplay(5);
            }
        }
    }
}

remind::~remind()
{
    delete ui;
}

void remind::updateDateTimeAndDisplay(int index)
{
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
//    int H = h.toInt();       //当前时间
//    int M = m.toInt();
//    int S = s.toInt();
    if(index == 0){
        QTime showTime(0,0,10,0);
        showTime = showTime.addMSecs(-t);
        showStr = showTime.toString("hh:mm:ss:zzz");
    }else if (index == 1) {
        QTime showTime(0,5,0,0);
        showTime = showTime.addMSecs(-t);
        showStr = showTime.toString("hh:mm:ss:zzz");
    }else if (index == 2) {
        QTime showTime(0,10,0,0);
        showTime = showTime.addMSecs(-t);
        showStr = showTime.toString("hh:mm:ss:zzz");
    }else if (index == 3) {
        QTime showTime(0,15,0,0);
        showTime = showTime.addMSecs(-t);
        showStr = showTime.toString("hh:mm:ss:zzz");
    }else if (index == 4) {
        QTime showTime(0,30,0,0);
        showTime = showTime.addMSecs(-t);
        showStr = showTime.toString("hh:mm:ss:zzz");
    }else if (index == 5) {
        QTime showTime(1,0,0,0);
        showTime = showTime.addMSecs(-t);
        showStr = showTime.toString("hh:mm:ss:zzz");
    }
    this->ui->lcdNumber->display(showStr);
}

void remind::on_btn_cancel_clicked()
{
    int choose;
    choose= QMessageBox::question(this, tr("取消"), QString(tr("你确定要取消吗?")), QMessageBox::Yes | QMessageBox::No);
    if (choose == QMessageBox::Yes) {
        int choose2 = QMessageBox::question(this, tr("取消"), QString(tr("你真的确定不会忘记吗?")), QMessageBox::Yes | QMessageBox::No);
        if(choose2 == QMessageBox::Yes) {
            this->ui->lcdNumber->display("00:00:00:000");
            this->close();
        }
    } else if (choose == QMessageBox::No) {
        //do nothing
    }
}

int remind::readFromFile()
{
    QFile file("date.txt");
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        date_lines.append(line);
    }
    file.close();
    int i;
    for (i = 0;i < date_lines.length();i++) {
        qDebug() << date_lines.at(i);                //输出所有日程安排
    }
    return 0;
}
