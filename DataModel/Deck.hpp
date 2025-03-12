#ifndef DECK_HPP
#define DECK_HPP

#include "Collection.hpp"
#include "../Utils/DateTime.hpp"
#include <QDataStream>

class Deck {
  public:
    Deck() = default;
    Deck(const std::string& name, const std::string& description, const std::string& format, const 
    std::string& author);

    bool operator==(const Deck& other) const;

    void addCard(const Card& card);
    void removeCard(const Card& card);
    void addSideboardCard(const Card& card);
    void removeSideboardCard(const Card& card);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void updateDateModified();
    void setFormat(const std::string& format);
    void setAuthor(const std::string& author);

    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::string& getDateCreated() const;
    const std::string& getDateModified() const;
    const std::string& getFormat() const;
    const std::string& getAuthor() const;
    const Collection& getMainBoard() const;
    const Collection& getSideBoard() const;

    friend QDataStream& operator<<(QDataStream& out, const Deck& deck);
    friend QDataStream& operator>>(QDataStream& in, Deck& deck);
    
  private: 
    Collection mainBoard;
    Collection sideBoard;
    std::string name;
    std::string description;
    std::string dateCreated;
    std::string dateModified;
    std::string format;
    std::string author;
};

#endif