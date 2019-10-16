#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"autornamecollection.h"
#include<QDebug>
#include<QSqlTableModel>
#include<QFileDialog>
#include<QListView>
#include<QTreeView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pANC(new autorNameCollection),
    model(new QSqlTableModel(this))

{
    ui->setupUi(this);

    connect(ui->addButton,&QPushButton::clicked,this,&MainWindow::addAutor);


//    pANC->addAutor("momi","D:/add/");
//    pANC->addAutor("savan","D:/sub/");
//    pANC->addAutor("savan","D:/sxxub/");
//    pANC->addAutor("women","D:/ds/");
//    qDebug()<<"the name from database:"<<pANC->getAutorNames();
//    qDebug()<<"the id of savan:"<<pANC->getId("savan");
//    qDebug()<<"The path of id of savan:"<<pANC->getUrl(2);
//    QList<QString>lis = pANC->getUrls("savan");
//    qDebug()<<&lis;
//    qDebug()<<"the paths of savan:"<<lis;

    model->setTable("autors");
    model->select();//refresh the table view
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui,pANC;

}

void MainWindow::addAutor()
{
    pANC->addAutor(ui->nameLine->text(),ui->pathLine->text());
    model->select();
}


void MainWindow::on_checkIdButton_clicked()
{
    qDebug()<<"Now what is the path of id1"<<pANC->getUrl(1);
}

//用于打开文件夹选取界面
void MainWindow::on_actionAdd_Path_triggered()
{
    QRegularExpression pattern("\\[(?<fileName>.*)\\]");//设定中括号内容匹配模式
    //设定最小匹配模式
    pattern.setPatternOptions(QRegularExpression::InvertedGreedinessOption);

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QDir::homePath());
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();//get the absolute path of the directory
    //if get a directory that do something
    if(fileNames.length()!=0)
    {
        QDir dir(fileNames.first());//In this file mode we can only get one path
        QStringList pathList = dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Hidden);

        foreach (QString var, pathList)
        {
            QString tempPath = fileNames.first()+"/"+var;//迭代得到拼接好的文件夹地址
            QString tempAutorName;
            QRegularExpressionMatch match = pattern.match(var);
            if(match.hasMatch())
            {
                tempAutorName = match.captured("fileName");//指定分组的方法获取匹配字段的特定部分;

            }
            else
                tempAutorName = "Jane Doe";
            pANC->addAutor(tempAutorName,tempPath);
        }
    }
    model->select();

}
