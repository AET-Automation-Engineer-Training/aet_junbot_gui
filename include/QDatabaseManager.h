#ifndef QDATABASEMANAGER_H
#define QDATABASEMANAGER_H

#include <QObject>
#include <QMutex>
#include <QCoreApplication>

#include <memory>

#include "QUserDAO.h"
#include "QDeliveryTargetDAO.h"

#ifndef BUILD_DIR

#define BUILD_DIR QCoreApplication::applicationDirPath()

#endif

class QSqlDatabase;
class QSqlQuery;

// const QString DATABASE_FILENAME = BUILD_DIR + "/data/user.db";

const QString DATABASE_FILENAME = "/home/lacie/workspace/aet_ws/src/ate_junbot_gui/junbot_gui/data/user.db";

class QDatabaseManager
{

public:
    static void debugQuery(const QSqlQuery& query);

    QDatabaseManager(const QString& path = DATABASE_FILENAME);

    static QDatabaseManager& instance(char* path = nullptr);
    ~QDatabaseManager();

protected:
    QDatabaseManager& operator= (const QDatabaseManager& rhs);

public:
    const QUserDAO userDao;
    const QDeliveryTargetDAO deliveryTargetDao;

private:
    static QSqlDatabase* m_database;
};

#endif // QDATABASEMANAGER_H



