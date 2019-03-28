#include "adddate.h"
#include "ui_adddate.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QComboBox>
#include <QDateTime>
#include <QTime>
#include <QCheckBox>
#include <QCloseEvent>
#include <QDebug>

addDate::addDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDate)
{
    ui->setupUi(this);

    this->ui->le_theme->setClearButtonEnabled(true);
    this->ui->le_location->setClearButtonEnabled(true);
    this->ui->le_remark->setClearButtonEnabled(true);

    this->ui->dte_begin->setDateTime(QDateTime::currentDateTime());
    this->ui->dte_end->setDateTime(QDateTime::currentDateTime());

    QString ddd = this->ui->dte_begin->date().toString("ddd");
    this->ui->cbb_times->setItemText(4, "每" + ddd);
    this->ui->cbb_times->setItemText(5, "每月（" + QDateTime::currentDateTime().toString("dd") + "日）");
    this->ui->cbb_times->setItemText(6, "每年（" + QDateTime::currentDateTime().toString("M") + "月" + QDateTime::currentDateTime().toString("dd") + "日）");
}

addDate::~addDate()
{
    delete ui;
}

void addDate::on_btn_ok_clicked()
{
    QString theme = this->ui->le_theme->text();
    QString location = this->ui->le_location->text();
    QString remark = this->ui->le_remark->text();

    QString dateBegin_year = this->ui->dte_begin->sectionText(QDateTimeEdit::YearSection);
    QString dateBegin_month = this->ui->dte_begin->sectionText(QDateTimeEdit::MonthSection);
    if(dateBegin_month.length() <= 1){
        dateBegin_month = '0' + dateBegin_month;
    }
    QString dateBegin_day = this->ui->dte_begin->sectionText(QDateTimeEdit::DaySection);
    if(dateBegin_day.length() <= 1){
        dateBegin_day = '0' + dateBegin_day;
    }
    QString dateBegin_hour = this->ui->dte_begin->sectionText(QDateTimeEdit::HourSection);
    QString dateBegin_minute = this->ui->dte_begin->sectionText(QDateTimeEdit::MinuteSection);

    QString dateEnd_year = this->ui->dte_end->sectionText(QDateTimeEdit::YearSection);
    QString dateEnd_month = this->ui->dte_end->sectionText(QDateTimeEdit::MonthSection);
    if(dateEnd_month.length() <= 1){
        dateEnd_month = '0' + dateEnd_month;
    }
    QString dateEnd_day = this->ui->dte_end->sectionText(QDateTimeEdit::DaySection);
    if(dateEnd_day.length() <= 1){
        dateEnd_day = '0' + dateEnd_day;
    }
    QString dateEnd_hour = this->ui->dte_end->sectionText(QDateTimeEdit::HourSection);
    QString dateEnd_minute = this->ui->dte_end->sectionText(QDateTimeEdit::MinuteSection);

    QString remind = this->ui->cbb_remind->currentText();

    //根据活动时间更改提醒时间的下拉框
    QString ddd = this->ui->dte_begin->date().toString("ddd");
    //qDebug() << ddd;
    this->ui->cbb_times->setItemText(4, "每" + ddd);
    this->ui->cbb_times->setItemText(5, "每月（" + dateBegin_day + "）");
    this->ui->cbb_remind->setItemText(6, "每年（" + dateBegin_month + "月" + dateBegin_day + "日）");

    QString times = this->ui->cbb_times->currentText();
    QString zone = this->ui->cbb_zone->currentText();

    if(dateBegin_hour <= 1) {
        dateBegin_hour = "0" + dateBegin_hour;
    }
    if(dateBegin_minute <= 1) {
        dateBegin_minute = "0" + dateBegin_minute;
    }
    if(dateEnd_hour <= 1) {
        dateEnd_hour = "0" + dateEnd_hour;
    }
    if(dateEnd_minute <= 1) {
        dateEnd_minute = "0" + dateEnd_minute;
    }

    QString cnt = theme + " " + dateBegin_year + " " + dateBegin_month  + " " + dateBegin_day + " " + dateBegin_hour + " " +  dateBegin_minute  + " " + dateEnd_year + " " + dateEnd_month  + " " + dateEnd_day + " " + dateEnd_hour + " " +  dateEnd_minute  + " " + " " + remind + " " + location + " " + remark + " " + zone + '\n';

    if(theme.length() < 1){
        QMessageBox::critical(this, "ERROR","信息不完整，请重新检查！","确定");
    } else if(location.length() < 1) {
        QMessageBox::critical(this, "ERROR","信息不完整，请重新检查！","确定");
    }else if (remark.length() < 1) {
        QMessageBox::critical(this, "ERROR","信息不完整，请重新检查！","确定");
    }else {
        QMessageBox::information(this, "成功","亲 安排上了！","确定");
        clearUserFace();
        writeToFile(cnt);
    }
}

void addDate::on_btn_cancel_clicked()
{
    this->close();
}

void addDate::closeEvent(QCloseEvent *event)
{
    int choose;
    choose= QMessageBox::question(this, tr("Exit"), QString(tr("Are you sure you want to exit?")), QMessageBox::Yes | QMessageBox::No);
    if (choose== QMessageBox::No) {
        event->ignore();
    } else if (choose== QMessageBox::Yes) {
        event->accept();
    }
}

void addDate::writeToFile(QString cnt)
{
    QFile file("date.txt");
    if(! file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(this, "ERROR","文件打开失败");
        return;
    }
    QTextStream out(&file);
    out << cnt;
    file.close();
}

void addDate::clearUserFace()
{
    this->ui->le_theme->clear();
    this->ui->le_location->clear();
    this->ui->le_remark->clear();
    this->ui->checkBox->setChecked(false);
    this->ui->cbb_remind->setCurrentIndex(0);
    this->ui->cbb_times->setCurrentIndex(0);
    this->ui->cbb_zone->setCurrentIndex(0);
    this->ui->dte_begin->setDateTime(QDateTime::currentDateTime());
    this->ui->dte_end->setDateTime(QDateTime::currentDateTime());
    this->ui->le_theme->setFocus();    //设置焦点
}

void addDate::on_checkBox_stateChanged(int arg1)
{
    QTime currentTime = QTime::currentTime();
    if(arg1) {
        int x = currentTime.hour()*3600 + currentTime.minute()*60 + currentTime.second();
        int y = 86400 - x;
        this->ui->dte_begin->setDateTime(QDateTime::currentDateTime().addSecs(-x));
        this->ui->dte_end->setDateTime(QDateTime::currentDateTime().addSecs(y));
    }else {
        this->ui->dte_begin->setDateTime(QDateTime::currentDateTime());
        this->ui->dte_end->setDateTime(QDateTime::currentDateTime());
    }
}

void addDate::on_dte_begin_dateTimeChanged(const QDateTime &dateTime)
{
    QString ddd = this->ui->dte_begin->date().toString("ddd");
    QString dateBegin_month = this->ui->dte_begin->sectionText(QDateTimeEdit::MonthSection);
    QString dateBegin_day = this->ui->dte_begin->sectionText(QDateTimeEdit::DaySection);
    this->ui->cbb_times->setItemText(4, "每" + ddd);
    this->ui->cbb_times->setItemText(5, "每月（" + dateBegin_day + "日）");
    this->ui->cbb_times->setItemText(6, "每年（" + dateBegin_month + "月" + dateBegin_day + "日）");
}

