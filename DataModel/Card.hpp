#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <QMetaType>
#include <QDataStream>
#include <QString>
#include <QStringList>

class Card {
public:
    Card() = default;
    Card(const std::string& name, const std::string& colorIdentity, const std::string& colors, const int convertedManaCost, const bool isFunny, const std::string& manaCost, const int manaValue, const std::vector<std::string>& subTypes, const std::vector<std::string>& superTypes, const std::string& text, const std::vector<std::string>& types);
    
    bool operator==(const Card& other) const;

    // Getters
    const std::string& getName() const;
    std::string& getColorIdentity();
    std::string& getColors();
    int getConvertedManaCost();
    bool getIsFunny();
    std::string& getManaCost();
    int getManaValue();
    std::vector<std::string>& getSubTypes();
    std::vector<std::string>& getSuperTypes();
    std::string& getText();
    std::vector<std::string>& getTypes();

    // Serialization operators
    friend QDataStream& operator<<(QDataStream& out, const Card& card);
    friend QDataStream& operator>>(QDataStream& in, Card& card);

private:
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
};

Q_DECLARE_METATYPE(Card);
#endif