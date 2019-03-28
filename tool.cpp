#include "tool.h"
#include "ui_tool.h"
#include <QTime>
#include <QTimer>
#include<QString>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&this->ptimer , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay()));
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::updateDateTimeAndDisplay()
{
//    this->baseTime = this->baseTime.addMSecs(1);
//    QString showStr = this->baseTime.toString("hh:mm:ss:zzz");
//    this->ui->lcdNumber->display(showStr);

    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    int H = h.toInt();
    int M = m.toInt();
    int S = s.toInt();
    QTime showTime(H,M,S,0);
    showTime = showTime.addMSecs(t);
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
}

void Dialog::on_btn_start_clicked()
{
    h = this->ui->le_h->text();
    m = this->ui->le_m->text();
    s = this->ui->le_s->text();
     // this->ui->lcdNumber->display(h+':'+m+':'+s);
    this->baseTime = QTime::currentTime();
    this->ptimer.start(1);
    this->ui->btn_start->setEnabled(false);
}

void Dialog::on_btn_stop_clicked()
{
    if(this->ui->btn_stop->text() == "停止"){
        this->ui->btn_stop->setText("清零");
        this->ptimer.stop();
        this->ui->btn_pause->setEnabled(false);
    }else{
        this->ui->lcdNumber->display("00:00:00:000");
        this->ui->textBrowser->clear();
        this->ui->btn_stop->setText("停止");
        this->ui->btn_start->setEnabled(true);
        this->ui->btn_pause->setEnabled(true);
    }
}

void Dialog::on_btn_pause_clicked()
{
    static QTime pauseTime;
    if(this->ui->btn_pause->text() == "暂停"){
        pauseTime = QTime::currentTime();
        this->ptimer.stop();
        this->ui->btn_pause->setText("继续");
        this->ui->btn_stop->setEnabled(false);
    }else{
        QTime cut = QTime::currentTime();
        int t = pauseTime.msecsTo(cut);
        this->baseTime = this->baseTime.addMSecs(t);
        this->ptimer.start(1);
        this->ui->btn_pause->setText("暂停");
        this->ui->btn_stop->setEnabled(true);
    }
}

void Dialog::on_btn_log_clicked()
{
    this->ui->textBrowser->append(this->showStr);
}

void Dialog::on_btn_add_clicked()
{
    QString  s_add = this->ui->le_change->text();
    int a = s_add.toInt();
    this->baseTime = this->baseTime.addSecs(-a);
}

void Dialog::on_btn_reduce_clicked()
{
    QString s_reduce = this->ui->le_change->text();
    int a = s_reduce.toInt();
    this->baseTime = this->baseTime.addSecs(a);
}


