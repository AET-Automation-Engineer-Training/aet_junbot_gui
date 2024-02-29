#include "QDatabaseManager.h"
#include "AppConstants.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

QSqlDatabase* QDatabaseManager::m_database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));


void QDatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        // CONSOLE << "Query OK:"  << query.lastQuery();
    } else {
        CONSOLE << "Query KO:" << query.lastError().text();
        CONSOLE << "Query text:" << query.lastQuery();
    }
}

QDatabaseManager& QDatabaseManager::instance(char* path)
{
    static QDatabaseManager instance = QDatabaseManager(path);
    CONSOLE << "QDatabaseManager Init";
    return instance;
}

QDatabaseManager::QDatabaseManager(const QString& path)
    : userDao(*m_database),
      deliveryTargetDao(*m_database)

{
    CONSOLE << "Database path: " << path;

    m_database->setDatabaseName(path);

    bool openStatus = m_database->open();
    CONSOLE << "Database connection: " << (openStatus ? "OK" : "Error");

    userDao.init(); 
    deliveryTargetDao.init();
}

QDatabaseManager::~QDatabaseManager()
{
    m_database->close();
}


