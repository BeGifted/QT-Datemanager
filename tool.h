#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTime>
#include <QTimer>
#include<QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QTimer ptimer;
    QTime baseTime;
    QString showStr;
    QString h;
    QString m;
    QString s;

private slots:
    void updateDateTimeAndDisplay();

    void on_btn_start_clicked();

    void on_btn_stop_clicked();

    void on_btn_pause_clicked();

    void on_btn_log_clicked();

    void on_btn_add_clicked();

    void on_btn_reduce_clicked();


};

#endif // DIALOG_H
