#include "Card.hpp"

Card::Card(const std::string& name, const std::string& colorIdentity, const std::string& colors, const int convertedManaCost, const bool isFunny, const std::string& manaCost, const int manaValue, const std::vector<std::string>& subTypes, const std::vector<std::string>& superTypes, const std::string& text, const std::vector<std::string>& types)
    : name(name), colorIdentity(colorIdentity), colors(colors), convertedManaCost(convertedManaCost), isFunny(isFunny), manaCost(manaCost), manaValue(manaValue), subTypes(subTypes), superTypes(superTypes), text(text), types(types) {}

bool Card::operator==(const Card& other) const {
    return name == other.name &&
           colorIdentity == other.colorIdentity &&
           colors == other.colors &&
           convertedManaCost == other.convertedManaCost &&
           isFunny == other.isFunny &&
           manaCost == other.manaCost &&
           manaValue == other.manaValue &&
           subTypes == other.subTypes &&
           superTypes == other.superTypes &&
           text == other.text &&
           types == other.types; 
}

// Helper function to convert std::vector<std::string> to QStringList
QStringList vectorToQStringList(const std::vector<std::string>& vec) {
    QStringList list;
    for (const auto& str : vec) {
        list.append(QString::fromStdString(str));
    }
    return list;
}

// Helper function to convert QStringList to std::vector<std::string>
std::vector<std::string> qStringListToVector(const QStringList& list) {
    std::vector<std::string> vec;
    for (const auto& str : list) {
        vec.push_back(str.toStdString());
    }
    return vec;
}

// Save Card to QDataStream
QDataStream& operator<<(QDataStream& out, const Card& card) {
    out << QString::fromStdString(card.name);
    out << QString::fromStdString(card.colorIdentity);
    out << QString::fromStdString(card.colors);
    out << static_cast<qint32>(card.convertedManaCost);
    out << static_cast<quint8>(card.isFunny);  // Store bool as quint8 (1 byte)
    out << QString::fromStdString(card.manaCost);
    out << static_cast<qint32>(card.manaValue);
    out << vectorToQStringList(card.subTypes);
    out << vectorToQStringList(card.superTypes);
    out << QString::fromStdString(card.text);
    out << vectorToQStringList(card.types);
    return out;
}

// Load Card from QDataStream
QDataStream& operator>>(QDataStream& in, Card& card) {
    QString qName, qColorIdentity, qColors, qManaCost, qText;
    qint32 qConvertedManaCost, qManaValue;
    quint8 qIsFunny;
    QStringList qSubTypes, qSuperTypes, qTypes;

    in >> qName >> qColorIdentity >> qColors >> qConvertedManaCost >> qIsFunny
       >> qManaCost >> qManaValue >> qSubTypes >> qSuperTypes >> qText >> qTypes;

    card.name = qName.toStdString();
    card.colorIdentity = qColorIdentity.toStdString();
    card.colors = qColors.toStdString();
    card.convertedManaCost = qConvertedManaCost;
    card.isFunny = (qIsFunny != 0);  // Convert quint8 to bool
    card.manaCost = qManaCost.toStdString();
    card.manaValue = qManaValue;
    card.subTypes = qStringListToVector(qSubTypes);
    card.superTypes = qStringListToVector(qSuperTypes);
    card.text = qText.toStdString();
    card.types = qStringListToVector(qTypes);

    return in;
}

const std::string& Card::getName() const {
    return name;
}

std::string& Card::getColorIdentity() {
    return colorIdentity;
}

std::string& Card::getColors() {
    return colors;
}

int Card::getConvertedManaCost() {
    return convertedManaCost;
}

bool Card::getIsFunny() {
    return isFunny;
}

std::string& Card::getManaCost() {
    return manaCost;
}

int Card::getManaValue() {
    return manaValue;
}

std::vector<std::string>& Card::getSubTypes() {
    return subTypes;
}

std::vector<std::string>& Card::getSuperTypes() {
    return superTypes;
}

std::string& Card::getText() {
    return text;
}

std::vector<std::string>& Card::getTypes() {
    return types;
}