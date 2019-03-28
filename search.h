#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QList>
#include <QFile>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class search;
}

class search : public QDialog
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();
    int readFromFile();
    void doQuery(const char* cnt);
    void display(int, char*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::search *ui;

    QList<QString> date_lines;
    QStandardItemModel  * model;
};

#endif // SEARCH_H
