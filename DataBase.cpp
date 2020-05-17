#include "DataBase.h"

DataBase::DataBase( QString connectionName )
{
    m_connectionName = connectionName;
    m_processStarted = false;
    m_dataBase = new QSqlDatabase;
}

DataBase::~DataBase()
{	
    if(m_dataBase){
        closeDB();
        delete m_dataBase;
    }
    QSqlDatabase::removeDatabase(m_connectionName);
}

void DataBase::closeDB()
{
   m_dataBase->close();
}

bool DataBase::execDeleteQuery( QString sqlStr )
{
    if (!m_processStarted)
        if (!openDB())
            return false;
    
    //执行sql语句
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//输出错误信息
        if (m_processStarted == false){closeDB();}
        return false;
    }

    //关闭连接
    if (m_processStarted == false){closeDB();}
    return true;
}


bool DataBase::execInsertQuery( QString sqlStr )
{
    if (!m_processStarted)
        if (!openDB())
            return false;

    //执行sql语句
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//输出错误信息
        if (m_processStarted == false){closeDB();}
        return false;
    }

    if (m_processStarted == false){closeDB();}
    return true;
}


QList<QSqlRecord> DataBase::execSelectQuery( QString sqlStr )
{
    QList<QSqlRecord> records;
    if (!m_processStarted)
        if (!openDB())
            return records;
    
    //执行sql语句
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//输出错误信息
        if (m_processStarted == false){closeDB();}
        return records;
    }

    while (query.next()){
        QSqlRecord tmp_record = query.record();
        if (!tmp_record.isEmpty())
            records << tmp_record;
    }
    
    if (m_processStarted == false){closeDB();}
    return records;
}

bool DataBase::execUpdateQuery( QString sqlStr )
{
    if (m_processStarted == false)
        if (false == openDB())
            return false;
    

    //执行sql语句
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//输出错误信息
        if (m_processStarted == false){closeDB();}
        return false;
    }

    if (m_processStarted == false){closeDB();}
    return true;
}

//判断服务器是否可以连接 秒
/*
bool DataBase::isIPLive(int timeout)
{
    return IPLive::instance()->isLive(timeout);
}*/

bool DataBase::openDB()
{
/*
    if (isIPLive() == false){
		qDebug()<<QString::fromLocal8Bit("数据库服务器无法连接！");
		return false;
	}*/

    if (!m_dataBase->isValid()){
        if (QSqlDatabase::contains(m_connectionName)){
                *m_dataBase = QSqlDatabase::database(m_connectionName);
        }else{
            *m_dataBase = QSqlDatabase::addDatabase( "QMYSQL", m_connectionName );
            m_dataBase->setHostName( "localhost" );      //服务器
            m_dataBase->setDatabaseName( "radar" );  //数据库名字
            m_dataBase->setUserName( "root" );       //用户名
            m_dataBase->setPassword( "root" );       //密码
        }
    }

    //打开数据库
    m_dataBase->open(); 

	//调试状态判断
	//qDebug() << "isValid：" << m_dataBase->isValid();
	//qDebug() << "isOpen：" << m_dataBase->isOpen();

    return m_dataBase->isValid() && m_dataBase->isOpen();
}
//开启一次过程
bool DataBase::startProcess()
{
    if (!m_processStarted)
        m_processStarted = openDB();
    if (m_processStarted)
        m_processStarted = m_processStarted&&m_dataBase->transaction();
    return m_processStarted;
}
//结束一次过程
void DataBase::stopProcess()
{
    if (m_processStarted){
        if(!m_dataBase->commit()){
            qDebug()<<m_dataBase->lastError().text();
            if(!m_dataBase->rollback())
                qDebug()<<m_dataBase->lastError().text();
        }
        closeDB();
        m_processStarted = false;
    }
}

bool DataBase::transaction()
{
    if (!m_processStarted)
        if (!openDB())
            return false;
    return m_dataBase->transaction();
}

bool DataBase::commit()
{
    if (!m_processStarted)
        if (!openDB())
            return false;
    return m_dataBase->commit();
}

bool DataBase::rollback()
{
    if (!m_processStarted)
        if (!openDB())
            return false;
    return m_dataBase->rollback();
}

QSqlError DataBase::lastError()
{
    if (!m_processStarted)
        if (!openDB())
            return false;
    return m_dataBase->lastError();
}

