#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVector>
#include <QDebug>
#include "../DataModel/Card.hpp"

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool connectDatabase(const QString& dbPath);
    QVector<Card> getAllCards();
    Card getCardByName(const QString& name); 

private:
    DatabaseManager();  // Private constructor (Singleton)
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_HPP