#include "Deck.hpp"

Deck::Deck(const std::string& name, const std::string& description, const std::string& format, const std::string& author)
    : name(name), description(description), format(format), author(author) {
        this->dateCreated = DateTime::instance().getCurrentDateTimeString();
        this->dateModified = DateTime::instance().getCurrentDateTimeString();
        this->mainBoard = Collection(name, description);
        this->sideBoard = Collection(name, description);
    }

bool Deck::operator==(const Deck& other) const {
    return name == other.name &&
           description == other.description &&
           dateCreated == other.dateCreated &&
           dateModified == other.dateModified &&
           format == other.format &&
           author == other.author &&
           mainBoard == other.mainBoard &&
           sideBoard == other.sideBoard;
}

void Deck::updateDateModified() {
    this->dateModified = DateTime::instance().getCurrentDateTimeString();
}

void Deck::addCard(const Card& card) {
    mainBoard.addCard(card);
    updateDateModified();
}

void Deck::removeCard(const Card& card) {
    mainBoard.removeCard(card);
    updateDateModified();
}

void Deck::addSideboardCard(const Card& card) {
    sideBoard.addCard(card);
    updateDateModified();
}

void Deck::removeSideboardCard(const Card& card) {
    sideBoard.removeCard(card);
    updateDateModified();
}

void Deck::setName(const std::string& name) {
    this->name = name;
    updateDateModified();
}

void Deck::setDescription(const std::string& description) {
    this->description = description;
    updateDateModified();
}

void Deck::setFormat(const std::string& format) {
    this->format = format;
    updateDateModified();
}

void Deck::setAuthor(const std::string& author) {
    this->author = author;
    updateDateModified();
}

// MARK: Getters
const std::string& Deck::getName() const {
    return name;
}

const std::string& Deck::getDescription() const {
    return description;
}

const std::string& Deck::getDateCreated() const {
    return dateCreated;
}

const std::string& Deck::getDateModified() const {
    return dateModified;
}

const std::string& Deck::getFormat() const {
    return format;
}

const std::string& Deck::getAuthor() const {
    return author;
}

const Collection& Deck::getMainBoard() const {
    return mainBoard;
}

const Collection& Deck::getSideBoard() const {
    return sideBoard;
}

// MARK: Serialization operators
QDataStream& operator<<(QDataStream& out, const Deck& deck) {
    out << QString::fromStdString(deck.name);
    out << QString::fromStdString(deck.description);
    out << QString::fromStdString(deck.dateCreated);
    out << QString::fromStdString(deck.dateModified);
    out << QString::fromStdString(deck.format);
    out << QString::fromStdString(deck.author);
    out << deck.mainBoard;
    out << deck.sideBoard;

    return out;
}

QDataStream& operator>>(QDataStream& in, Deck& deck) {
    QString qName, qDescription, qDateCreated, qDateModified, qFormat, qAuthor;
    in >> qName >> qDescription >> qDateCreated >> qDateModified >> qFormat >> qAuthor;

    deck.name = qName.toStdString();
    deck.description = qDescription.toStdString();
    deck.dateCreated = qDateCreated.toStdString();
    deck.dateModified = qDateModified.toStdString();
    deck.format = qFormat.toStdString();
    deck.author = qAuthor.toStdString();

    in >> deck.mainBoard;
    in >> deck.sideBoard;

    return in;
}


