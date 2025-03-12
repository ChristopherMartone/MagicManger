#include "Collection.hpp"
#include <algorithm>  // Required for std::remove

Collection::Collection(const std::string& name, const std::string& description, 
                       const std::string& dateCreated, const std::string& dateModified)
    : name(name), description(description), dateCreated(dateCreated), dateModified(dateModified) {}

// Save Collection to QDataStream
QDataStream& operator<<(QDataStream& out, const Collection& collection) {
    out << QString::fromStdString(collection.name);
    out << QString::fromStdString(collection.description);
    out << QString::fromStdString(collection.dateCreated);
    out << QString::fromStdString(collection.dateModified);

    // Serialize number of cards
    out << static_cast<qint32>(collection.cards.size());

    // Serialize each card (using Card's operator<<)
    for (const Card& card : collection.cards) {
        out << card;
    }

    return out;
}

// Load Collection from QDataStream
QDataStream& operator>>(QDataStream& in, Collection& collection) {
    QString qName, qDescription, qDateCreated, qDateModified;
    in >> qName >> qDescription >> qDateCreated >> qDateModified;

    collection.name = qName.toStdString();
    collection.description = qDescription.toStdString();
    collection.dateCreated = qDateCreated.toStdString();
    collection.dateModified = qDateModified.toStdString();

    // Deserialize number of cards
    qint32 cardCount;
    in >> cardCount;

    collection.cards.clear();
    for (qint32 i = 0; i < cardCount; i++) {
        Card card;
        in >> card;  // Uses Card's operator>>
        collection.cards.push_back(card);
    }

    return in;
}

const std::string& Collection::getName() const {
    return name;
}

const std::string& Collection::getDescription() const {
    return description;
}           

const std::string& Collection::getDateCreated() const {
    return dateCreated;
}       

const std::string& Collection::getDateModified() const {
    return dateModified;
}   

void Collection::addCard(const Card& card) {
    cards.push_back(card);
}

void Collection::removeCard(const Card& card) {
    auto it = std::remove(cards.begin(), cards.end(), card);
    if (it != cards.end()) {
        cards.erase(it, cards.end());
    }
}

const std::vector<Card>& Collection::getCards() const {
    return cards;
}

void Collection::getCardNames(std::vector<std::string>& outNames) const {
    outNames.clear();
    for (const Card& card : cards) {
        outNames.push_back(card.getName());
    }
}