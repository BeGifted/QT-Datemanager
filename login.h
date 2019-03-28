#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QString str_1,str_2,str_3,str_4;
    QString RemeberPasswd;
    bool remeberPasswd,r;

private slots:


    void on_checkBox_stateChanged(int arg1);

    void on_le_pass_textChanged(const QString &arg1);

    void on_btn_login_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::login *ui;

};

#endif // LOGIN_H
