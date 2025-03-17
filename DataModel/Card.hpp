#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <QMetaType>
#include <QDataStream>
#include <QString>
#include <QStringList>

struct Card {
    std::string name;
    std::string colorIdentity;
    std::string colors;
    int convertedManaCost;
    bool isFunny;
    std::string manaCost;
    int manaValue;
    std::vector<std::string> subTypes;
    std::vector<std::string> superTypes;
    std::string text;
    std::vector<std::string> types;

    // ✅ Default Constructor
    Card() = default;
    
    // ✅ Parameterized Constructor
    Card(const std::string& name, const std::string& colorIdentity, const std::string& colors, int convertedManaCost, 
         bool isFunny, const std::string& manaCost, int manaValue, const std::vector<std::string>& subTypes, 
         const std::vector<std::string>& superTypes, const std::string& text, const std::vector<std::string>& types);

    // ✅ Comparison operator (needed for std::remove in Collection)
    bool operator==(const Card& other) const;

    // ✅ Serialization operators
    friend QDataStream& operator<<(QDataStream& out, const Card& card);
    friend QDataStream& operator>>(QDataStream& in, Card& card);
};

Q_DECLARE_METATYPE(Card);
#endif // CARD_HPP