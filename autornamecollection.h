#ifndef AUTORNAMECOLLECTION_H
#define AUTORNAMECOLLECTION_H

#include<QString>
class autorNameCollection
{
public:
    autorNameCollection();

    QString getUrl(const int& id);//获得该ID对应的文件夹地址
    QStringList getUrls(const QString& name);//get the urllist using autor name
    int getId(const QString& autorName);//获得作者名字对应的ID，暂时先一个作者只有一个文件夹
    QStringList getAutorNames();//get all name of the autors

    //add information of a autor into database
    void addAutor(const QString& name,const QString& path);


private:
    void populateDatabase();

};

#endif // AUTORNAMECOLLECTION_H
