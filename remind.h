#ifndef REMIND_H
#define REMIND_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QTimer>

namespace Ui {
class remind;
}

class remind : public QDialog
{
    Q_OBJECT

public:
    explicit remind(QWidget *parent = nullptr);
    ~remind();

private slots:
    void on_btn_cancel_clicked();

    int readFromFile();

    void updateDateTimeAndDisplay(int index);

private:
    Ui::remind *ui;
    QString h;
    QString m;
    QString s;
    QList<QString> date_lines;
    QTimer ptimer;
    QTime baseTime;
    QString showStr;

};

#endif // REMIND_H
