#include "search.h"
#include "ui_search.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include <fstream>
#include <QByteArray>
#include <QByteArrayData>
#define N 1000

search::search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);

    if(readFromFile() == -1){
        QMessageBox::critical(this, "ERROR","文件打开失败");
        this->close();
    }

    this->model = new QStandardItemModel;

    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("主题"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("开始时间"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("结束时间"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("提醒时间"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("备注"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("时区"));

    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnWidth(0,200);
    this->ui->tableView->setColumnWidth(1,200);
    this->ui->tableView->setColumnWidth(2,200);
    this->ui->tableView->setColumnWidth(3,200);
    this->ui->tableView->setColumnWidth(4,200);
    this->ui->tableView->setColumnWidth(5,200);
    this->ui->tableView->setColumnWidth(6,200);
}

search::~search()
{
    delete ui;
}


void search::on_pushButton_clicked()
{
    this->model->clear();
    this->model->setHorizontalHeaderItem(0,new QStandardItem("主题"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("开始时间"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("结束时间"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("提醒时间"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("备注"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("时区"));

    this->ui->tableView->setColumnWidth(0,200);
    this->ui->tableView->setColumnWidth(1,200);
    this->ui->tableView->setColumnWidth(2,200);
    this->ui->tableView->setColumnWidth(3,200);
    this->ui->tableView->setColumnWidth(4,200);
    this->ui->tableView->setColumnWidth(5,200);
    this->ui->tableView->setColumnWidth(6,200);

    QString cnt = this->ui->lineEdit->text();
    char*  s;
    QByteArray ba = cnt.toLatin1();
    s = ba.data();
    qDebug() << s;

    doQuery(s);
}

int search::readFromFile()
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

void search::doQuery(const char* s2)             //模糊搜索
{
    int row;
    int r = 0;

    char* s;
    QString  str;
    QFile file("date.txt");
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return ;
    }
    while (1){
        for (row = 0; row < date_lines.length(); row++){
            str = date_lines.at(row);
            QByteArray ba = str.toLatin1();
            s = ba.data();

            char* res;
            res = (char *)memchr(s, s2[0], strlen(s));
            if (res == nullptr){
                continue;
            }
            int n;
            n = memcmp(res, s2, strlen(s2) - 1);
            if (n != 0){
                if (strlen(res) <= strlen(s2))
                    return;
                else{
                        res = (char*)memchr(res + 1, s2[0], strlen(res));
                        if (res == nullptr)
                            return;
                    }
                }
                else{
                        display(r++, s);
                }
            }
        }
}

void search::display(int row, char* str)
{
    const char s[2] = " ";
    char *token;
    token = strtok(str, s);
    this->model->setItem(row, 0, new QStandardItem(token));
    token = strtok(nullptr, s);
    this->model->setItem(row, 1, new QStandardItem(token));
    token = strtok(nullptr, s);
    this->model->setItem(row, 2, new QStandardItem(token));
    token = strtok(nullptr, s);
    this->model->setItem(row, 3, new QStandardItem(token));
    token = strtok(nullptr, s);
    this->model->setItem(row, 4, new QStandardItem(token));
    token = strtok(nullptr, s);
    this->model->setItem(row, 5, new QStandardItem(token));
    token = strtok(nullptr, s);
    this->model->setItem(row, 6, new QStandardItem(token));
}

