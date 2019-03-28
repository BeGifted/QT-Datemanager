#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QWidget>
#include <QShowEvent>
#include <adddate.h>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QFileSystemWatcher>
#include <login.h>
#include <remind.h>
#include <queryandalter.h>
#include <tool.h>
//#include <search.h>
#include <dialog2.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //主界即时更新 todo
    QFileSystemWatcher * fc = new QFileSystemWatcher;
    connect(fc,  SIGNAL(fileChanged(:/date.txt)), this, SLOT(filechange()));

    if(readFromFile() == -1){
        QMessageBox::critical(this, "ERROR","文件打开失败");
        this->close();
    }

    QDateTime current = QDateTime::currentDateTime();
    QString cury = current.toString("yyyy");       //当前日期
    QString curm = current.toString("MM");
    QString curd = current.toString("dd");

    QTime current1 =QTime::currentTime();
    QString cur1 = current1.toString("hh mm ss");

    //h,m,s为当前时间
    QString h = current1.toString("hh");
    QString m = current1.toString("mm");
    QString s = current1.toString("ss");

    this->baseTime = QTime::currentTime();

    int i;
    //qDebug() << cur;

    for (i = 0;i < date_lines.length();i++) {         //遍历所有日程
        QString line = date_lines.at(i);              //一行的日程
        line = line.trimmed();                              //去除开头结尾空白字符串
        QStringList subs = line.split(' ');           //标准化

        QString time = subs.at(4) + " " + subs.at(5) + " 00";
        //qDebug() << time;
        QTime time1;
        time1 = QTime::fromString(time, "hh mm ss");    //日程中的时间转换为qtime

        //qDebug() << time1.toString();

        if(subs.at(1) == cury&&subs.at(2) == curm &&subs.at(3) == curd) {       //当天日期吻合
            if(current1.addSecs(10) == time1) {
                remind l;
                l.exec();
            }else if (current1.addSecs(300) == time1) {
                remind l;
                l.exec();
            }else if (current1.addSecs(600) == time1) {
                remind l;
                l.exec();
            }else if (current1.addSecs(900) == time1) {
                remind l;
                l.exec();
            }else if (current1.addSecs(1800) == time1) {
                remind l;
                l.exec();
            }else if (current1.addSecs(3600) == time1) {
                remind l;
                l.exec();
            }
        }
    }

    this->setWindowTitle("日程管理提醒系统");
    this->setWindowIcon(QIcon(":/ico/date.ico"));

    this->model = new QStandardItemModel;

    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("主题"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("备注"));

    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnWidth(0,175);
    this->ui->tableView->setColumnWidth(1,180);
    this->ui->tableView->setColumnWidth(2,180);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_A_2_triggered()
{
    addDate a;
    a.exec();
}

void MainWindow::on_action_H_triggered()
{
    QMessageBox::aboutQt(this, "鸣谢");
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    //调用doquery -> display
    this->model->clear();
    this->model->setHorizontalHeaderItem(0,new QStandardItem("主题"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("备注"));

    this->ui->tableView->setColumnWidth(0,175);
    this->ui->tableView->setColumnWidth(1,180);
    this->ui->tableView->setColumnWidth(2,180);

    QString cnt = date.toString("yyyy MM dd");
    qDebug() << cnt;
    doQuery(cnt);
}

void MainWindow::doQuery(QString cnt)  //cnt为点击tableview的日期
{
    int i, row = 0;
    for (i = 0;i < date_lines.length();i++) {
        QString line = date_lines.at(i);
        line = line.trimmed();      //去除开头结尾空白字符串
        QStringList subs = line.split(' ');
        if(cnt.left(4) == subs.at(1)&&cnt.mid(5,2) == subs.at(2)&&cnt.right(2) == subs.at(3)){
            display(row++, subs);
        }
    }
}

int MainWindow::readFromFile()
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
        qDebug() << date_lines.at(i);
    }
    return 0;
}

void MainWindow::display(int row, QStringList t)
{
    this->model->setItem(row, 0, new QStandardItem(t.at(0)));
    this->model->setItem(row, 1, new QStandardItem(t.at(12)));
    this->model->setItem(row, 2, new QStandardItem(t.at(13)));
}

void MainWindow::filechange()
{
    MainWindow s;
    s.show();
}

void MainWindow::on_action_M_2_triggered()
{
    login l;
    l.exec();
}

void MainWindow::on_action_M_triggered()
{
    Dialog t;
    t.exec();
}

void MainWindow::on_actiona_triggered()
{
    queryAndAlter q;
    q.exec();
}

void MainWindow::on_action_S_triggered()
{
    Dialog2 d;
    d.exec();
}
