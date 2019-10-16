#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class autorNameCollection;//forward declare
class QSqlTableModel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    autorNameCollection *pANC;
    QSqlTableModel *model;
    Ui::MainWindow *ui;  

private slots:
    void addAutor();
    void on_checkIdButton_clicked();
    void on_actionAdd_Path_triggered();
};

#endif // MAINWINDOW_H
