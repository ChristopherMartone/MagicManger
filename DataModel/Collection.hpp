#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <string>
#include <vector>
#include "Card.hpp"
#include <QDataStream>
#include <QString>
#include "../Utils/DateTime.hpp" 

class Collection {
public:
    Collection() = default;
    Collection(const std::string& name, const std::string& description);

    bool operator==(const Collection& other) const;

    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::string& getDateCreated() const;
    const std::string& getDateModified() const;

    void addCard(const Card& card);
    void removeCard(const Card& card);
    void updateDateModified();
    
    const std::vector<Card>& getCards() const;
    void getCardNames(std::vector<std::string>& outNames) const;

    // Serialization operators
    friend QDataStream& operator<<(QDataStream& out, const Collection& collection);
    friend QDataStream& operator>>(QDataStream& in, Collection& collection);

private:
    std::string name;
    std::string description;
    std::string dateCreated;
    std::string dateModified;
    std::vector<Card> cards;
};

#endif // COLLECTION_HPP