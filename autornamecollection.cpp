#include "autornamecollection.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include<QList>
autorNameCollection::autorNameCollection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");//firstly do some test in memory,we will get a real file later
    if(!db.open())
        qDebug()<<db.lastError().text();

    populateDatabase();
}

QString autorNameCollection::getUrl(const int &id)
{
    QSqlQuery query;
    query.prepare("SELECT path FROM autors WHERE id = :id");
    query.bindValue(":id",id);
    if(!query.exec())
        qDebug()<<query.lastError().text();
    QString path;
    while(query.next())
        path = query.value(0).toString();
    return path;
}

QStringList autorNameCollection::getUrls(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT path FROM autors WHERE name = :name");
    query.bindValue(":name",name);
    if(!query.exec())
        qDebug()<<query.lastError().text();
    QList<QString> paths;
    while(query.next())
        paths<<query.value(0).toString();
    qDebug()<<&paths;
    return paths;
}

int autorNameCollection::getId(const QString &autorName)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM autors WHERE name = :name");
    query.bindValue(":name",autorName);
    if(!query.exec())
        qDebug()<<query.lastError().text();
    QList<int> Ids;
    while(query.next())
        Ids<<query.value(0).toInt();
    return Ids.first();
}

QStringList autorNameCollection::getAutorNames()
{
    QSqlQuery query;
    query.prepare("SELECT DISTINCT name FROM autors");//DISTINCT is used to avoid duplication
    if(!query.exec())
        qDebug()<<query.lastError().text();
    QStringList result;
    while(query.next())
        result<<query.value(0).toString();//get the select name value list
    return result;

}

void autorNameCollection::addAutor(const QString &name, const QString &path)
{
    QSqlQuery query;

    query.prepare("INSERT INTO autors(name,path)VALUES(:name,:path)");

    query.bindValue(":name",name);
    query.bindValue(":path",path);
    if(!query.exec())
        qDebug()<<query.lastError().text();
}

void autorNameCollection::populateDatabase()//create a table
{
    QSqlQuery query;
    //because id is primary key so it can inc automately
    query.prepare("CREATE TABLE IF NOT EXISTS autors"
                  "(id INTEGER PRIMARY KEY,name VARCHAR,path VARCHAR)");
    if(!query.exec())
        qDebug()<<query.lastError().text();
}

