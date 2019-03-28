#include "login.h"
#include "ui_login.h"
#include <QSettings>   //储存设置
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    QSettings setting("E:/QTWorkPlace/DateManager/config.ini",QSettings::IniFormat);//读配置文件
    str_3=setting.value("Login/account").toString();
    this->ui->le_username->setText(str_3);
    str_4=setting.value("Login/password").toString();
    this->ui->le_pass->setText(str_4);
    this->ui->checkBox->setChecked(true);
}

login::~login()
{
    delete ui;
}

void login::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == ui->checkBox->isChecked()) {
        remeberPasswd=true;
        str_1 = ui->le_username->text();
        str_2 = ui->le_pass->text();
        QSettings setting("E:/QTWorkPlace/DateManager/config.ini",QSettings::IniFormat); //读配置文件
        setting.beginGroup(tr("Login"));
        setting.setValue("account",str_1);        //设置key和value，也就是参数和值
        setting.setValue("password",str_2);
        setting.setValue("remeber",true);
        setting.endGroup();         //节点结束
    } else {
        this->ui->le_pass->clear();
        remeberPasswd=false;
    }
}

void login::on_btn_login_clicked()
{
    str_1 = this->ui->le_username->text();
    str_2 = this->ui->le_pass->text();
    QSettings setting("E:/QTWorkPlace/DateManager/config.ini",QSettings::IniFormat);//读配置文件
    if(str_1 == "" || str_2 == "") {
        QMessageBox::information(this, "错误！", "用户名或者密码不能为空！", "确定");
        return;
    } else if(str_1 == str_3&&str_2 == str_4) {
        this->close();
    } else if(str_1 == str_3&&str_2 != str_4) {
        QMessageBox::information(this, "错误！", "您输入的密码有误！", "确定");
        return;
    }
}


void login::on_le_pass_textChanged(const QString &arg1)
{
    this->ui->le_pass->setEchoMode(QLineEdit::Password);
}

void login::on_btn_cancel_clicked()
{
    this->close();
}
