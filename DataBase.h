#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

/**************************************************************************
 *                            DataBase                                
 *  ���ݿ��ࡣ                                  
 *  @  1�����ݲ�ͬ���ݿ�                                               
 *  @  2��֧�ֶ������                                               
 */
class  DataBase
{
public:
    DataBase(QString connectionName);
    ~DataBase();//virtual ~DataBase();
    bool execDeleteQuery(QString sqlStr);                     //ִ��delete���
    bool execInsertQuery(QString sqlStr);                     //ִ��insert���
    bool execUpdateQuery(QString sqlStr);                     //ִ��update���
    QList<QSqlRecord> execSelectQuery(QString sqlStr);	      //ִ��select���
    bool startProcess();//����һ�ι���
    void stopProcess(); //����һ�ι���

    //������
    bool transaction();
    bool commit();
    bool rollback();
    QSqlError   lastError();

private:
    void closeDB();
    //bool isIPLive(int timeout = 3);
    bool openDB();
private:
    QSqlDatabase * m_dataBase;       //���ݿ�
    QString        m_connectionName; //��������
    bool           m_processStarted; //��������
};

#endif // DATABASE_H
