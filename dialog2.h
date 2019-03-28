#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QString>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = nullptr);
    ~Dialog2();
    int readFromFile();
    void doQuery(int index, QString cnt);
    void display(int row, QStringList subs);

private slots:
    void on_btn_search_clicked();

private:
    Ui::Dialog2 *ui;
    QList<QString> asdf;
    QStandardItemModel  * model;
};

#endif // DIALOG2_H
