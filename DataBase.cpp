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
    
    //ִ��sql���
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//���������Ϣ
        if (m_processStarted == false){closeDB();}
        return false;
    }

    //�ر�����
    if (m_processStarted == false){closeDB();}
    return true;
}


bool DataBase::execInsertQuery( QString sqlStr )
{
    if (!m_processStarted)
        if (!openDB())
            return false;

    //ִ��sql���
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//���������Ϣ
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
    
    //ִ��sql���
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//���������Ϣ
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
    

    //ִ��sql���
    QSqlQuery query(*m_dataBase);
    if (query.exec(sqlStr) == false){
        qDebug() << query.lastError().text();		//���������Ϣ
        if (m_processStarted == false){closeDB();}
        return false;
    }

    if (m_processStarted == false){closeDB();}
    return true;
}

//�жϷ������Ƿ�������� ��
/*
bool DataBase::isIPLive(int timeout)
{
    return IPLive::instance()->isLive(timeout);
}*/

bool DataBase::openDB()
{
/*
    if (isIPLive() == false){
		qDebug()<<QString::fromLocal8Bit("���ݿ�������޷����ӣ�");
		return false;
	}*/

    if (!m_dataBase->isValid()){
        if (QSqlDatabase::contains(m_connectionName)){
                *m_dataBase = QSqlDatabase::database(m_connectionName);
        }else{
            *m_dataBase = QSqlDatabase::addDatabase( "QMYSQL", m_connectionName );
            m_dataBase->setHostName( "localhost" );      //������
            m_dataBase->setDatabaseName( "radar" );  //���ݿ�����
            m_dataBase->setUserName( "root" );       //�û���
            m_dataBase->setPassword( "root" );       //����
        }
    }

    //�����ݿ�
    m_dataBase->open(); 

	//����״̬�ж�
	//qDebug() << "isValid��" << m_dataBase->isValid();
	//qDebug() << "isOpen��" << m_dataBase->isOpen();

    return m_dataBase->isValid() && m_dataBase->isOpen();
}
//����һ�ι���
bool DataBase::startProcess()
{
    if (!m_processStarted)
        m_processStarted = openDB();
    if (m_processStarted)
        m_processStarted = m_processStarted&&m_dataBase->transaction();
    return m_processStarted;
}
//����һ�ι���
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

