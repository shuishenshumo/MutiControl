#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

/**************************************************************************
 *                            DataBase                                
 *  数据库类。                                  
 *  @  1、兼容不同数据库                                               
 *  @  2、支持多个连接                                               
 */
class  DataBase
{
public:
    DataBase(QString connectionName);
    ~DataBase();//virtual ~DataBase();
    bool execDeleteQuery(QString sqlStr);                     //执行delete语句
    bool execInsertQuery(QString sqlStr);                     //执行insert语句
    bool execUpdateQuery(QString sqlStr);                     //执行update语句
    QList<QSqlRecord> execSelectQuery(QString sqlStr);	      //执行select语句
    bool startProcess();//开启一次过程
    void stopProcess(); //结束一次过程

    //事务处理
    bool transaction();
    bool commit();
    bool rollback();
    QSqlError   lastError();

private:
    void closeDB();
    //bool isIPLive(int timeout = 3);
    bool openDB();
private:
    QSqlDatabase * m_dataBase;       //数据库
    QString        m_connectionName; //连接名字
    bool           m_processStarted; //开启过程
};

#endif // DATABASE_H
