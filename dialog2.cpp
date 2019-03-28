#include "dialog2.h"
#include "ui_dialog2.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QStringList>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    if(readFromFile() == -1){
        QMessageBox::critical(this, "ERROR","文件打开失败");
        this->close();
    }

    this->model = new QStandardItemModel;

    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("开始时间"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("结束时间"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("提示时间"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("备注"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("时区"));
    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,200);
    this->ui->tableView->setColumnWidth(2,200);
    this->ui->tableView->setColumnWidth(3,100);
    this->ui->tableView->setColumnWidth(4,100);
    this->ui->tableView->setColumnWidth(5,100);
    this->ui->tableView->setColumnWidth(6,200);
}

Dialog2::~Dialog2()
{
    delete ui;
}

int Dialog2::readFromFile()
{
    QFile file("date.txt");
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        asdf.append(line);
    }
    file.close();
    int i;
    for (i = 0;i < asdf.length();i++) {
        qDebug() << asdf.at(i);
    }
    return 0;
}

void Dialog2::on_btn_search_clicked()
{
    this->model->clear();
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("开始时间"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("结束时间"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("提示时间"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("备注"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("时区"));



    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,200);
    this->ui->tableView->setColumnWidth(2,200);
    this->ui->tableView->setColumnWidth(3,100);
    this->ui->tableView->setColumnWidth(4,100);
    this->ui->tableView->setColumnWidth(5,100);
    this->ui->tableView->setColumnWidth(6,200);

    int index = this->ui->cbb_method->currentIndex();
    QString cnt = this->ui->le_cnt->text();
    doQuery(index, cnt);
}

void Dialog2::doQuery(int index, QString cnt)
{
    int i, row = 0;
    for (i = 0;i < asdf.length();i++) {
        QString line = asdf.at(i);
        line = line.trimmed();      //去除开头结尾空白字符串
        QStringList subs = line.split(' ');
        switch(index){
        case 1:
            if(cnt == subs.at(0)){
                display(row++, subs);
            }
            break;
        case 2:
            if(cnt == subs.at(12)){
                display(row++, subs);
            }
            break;
        case 3:
            if(cnt == subs.at(13)){
                display(row++, subs);
            }
            break;
        }
    }
}

void Dialog2::display(int row, QStringList subs)
{
    int i,j;
    for(i = 0;i < 1;i++){
        this->model->setItem(row, i, new QStandardItem(subs.at(i)));
    }
    QString ins1,ins2;
    for(i = 1;i < 6;i++){
        ins1+= subs.at(i) + " ";
    }
    this->model->setItem(row, 1, new QStandardItem(ins1));
    for(i=6;i<11;i++)
        ins2+=subs.at(i)+" ";
    this->model->setItem(row, 2, new QStandardItem(ins2));
    for(i=11,j=3;i<subs.length();i++){
        this->model->setItem(row, j++, new QStandardItem(subs.at(i)));
    }

}
