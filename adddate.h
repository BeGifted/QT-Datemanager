#ifndef ADDDATE_H
#define ADDDATE_H

#include <QDialog>
#include <QString>
#include <QCloseEvent>

namespace Ui {
class addDate;
}

class addDate : public QDialog
{
    Q_OBJECT

public:
    explicit addDate(QWidget *parent = nullptr);
    ~addDate();


private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

    void writeToFile(QString cnt);
    void clearUserFace();
    void closeEvent(QCloseEvent *event);

    void on_checkBox_stateChanged(int arg1);

    void on_dte_begin_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::addDate *ui;
};

#endif // ADDDATE_H
