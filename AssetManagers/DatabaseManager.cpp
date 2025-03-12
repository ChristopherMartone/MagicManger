#include "DatabaseManager.hpp"

// Singleton instance
DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

// Private constructor
DatabaseManager::DatabaseManager() {}

// Connect to SQLite Database
bool DatabaseManager::connectDatabase(const QString& dbPath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Error: Unable to open database:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connected successfully!";
    return true;
}

// Helper function to convert QStringList to std::vector<std::string>
std::vector<std::string> convertQStringListToStdVector(const QStringList& list) {
    std::vector<std::string> result;
    for (const QString &str : list) {
        result.push_back(str.toStdString());
    }
    return result;
}

// Retrieve all cards from the database
QVector<Card> DatabaseManager::getAllCards() {
    QVector<Card> cards;
    QSqlQuery query("SELECT name, colorIdentity, colors, faceConvertedManaCost, manaCost, manaValue, isFunny, subtypes, supertypes, text, types FROM cards");

    if (!query.exec()) {
        qDebug() << "Error retrieving cards:" << query.lastError().text();
        return cards;
    }

    while (query.next()) {
        std::string name = query.value("name").toString().toStdString();
        std::string colorIdentity = query.value("colorIdentity").toString().toStdString();
        std::string colors = query.value("colors").toString().toStdString();
        int convertedManaCost = query.value("faceConvertedManaCost").toInt();
        std::string manaCost = query.value("manaCost").toString().toStdString();
        float manaValue = query.value("manaValue").toFloat();
        bool isFunny = query.value("isFunny").toBool();
        std::vector<std::string> subTypes = convertQStringListToStdVector(query.value("subtypes").toString().split(","));
        std::vector<std::string> superTypes = convertQStringListToStdVector(query.value("supertypes").toString().split(","));
        std::string text = query.value("text").toString().toStdString();
        std::vector<std::string> types = convertQStringListToStdVector(query.value("types").toString().split(","));

        cards.append(Card(name, colorIdentity, colors, convertedManaCost, isFunny, manaCost, manaValue, subTypes, superTypes, text, types));
    }

    return cards;
}

// Retrieve a specific card by UUID
Card DatabaseManager::getCardByName(const QString& name) {
    QSqlQuery query;
    query.prepare("SELECT name, colorIdentity, colors, faceConvertedManaCost, manaCost, manaValue, isFunny, subtypes, supertypes, text, types FROM cards WHERE name = :name");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Error retrieving card:" << query.lastError().text();
        return Card();  // Return empty card on failure
    }

    if (query.next()) {
        return Card(
            query.value("name").toString().toStdString(),
            query.value("colorIdentity").toString().toStdString(),
            query.value("colors").toString().toStdString(),
            query.value("faceConvertedManaCost").toInt(),
            query.value("isFunny").toBool(),
            query.value("manaCost").toString().toStdString(),
            query.value("manaValue").toFloat(),
            convertQStringListToStdVector(query.value("subtypes").toString().split(",")),
            convertQStringListToStdVector(query.value("supertypes").toString().split(",")),
            query.value("text").toString().toStdString(),
            convertQStringListToStdVector(query.value("types").toString().split(","))
        );
    }

    return Card();  // Return empty card if not found
}