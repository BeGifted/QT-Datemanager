#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDialog>
#include <QFile>
#include <QList>
#include <QString>
#include <QStandardItem>
#include <QFileSystemWatcher>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int readFromFile();
    void display(int row, QStringList t);
    void doQuery(QString cnt);

private slots:
    void on_action_A_2_triggered();

    void on_action_H_triggered();

    void on_calendarWidget_clicked(const QDate &date);

    void on_action_M_2_triggered();

    void on_action_M_triggered();

    void on_actiona_triggered();

    void filechange();

    void on_action_S_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel * model;
    QList<QString> date_lines;

    QTimer ptimer;
    QTime baseTime;
    QString showStr;

};

#endif // MAINWINDOW_H
