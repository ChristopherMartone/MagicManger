#include "DeckManager.hpp"

DeckManager& DeckManager::instance() {
    static DeckManager instance;
    return instance;
}

DeckManager::DeckManager() : decks(std::vector<Deck>()) {
    // TODO: Check for Deck data files and load if it exists
}


//MARK: Public methods
const Deck DeckManager::getDeckWithName(const std::string& name) {
    for (const Deck& deck : decks) {
        if (deck.getName() == name) {
            return deck;
        }
        std::printf("Deck not found: %s\n", name.c_str());
    }
    return Deck();
}

void DeckManager::addDeck(const Deck& deck) {
    decks.push_back(deck);
    saveDecks();
}

void DeckManager::removeDeck(Deck& deck) {
    decks.erase(std::remove(decks.begin(), decks.end(), deck), decks.end());
    saveDecks();
}

void DeckManager::removeDeckWithName(std::string& name) {
    decks.erase(std::remove_if(decks.begin(), decks.end(), [&name](const Deck& deck) {
        return deck.getName() == name;
    }), decks.end());
    saveDecks();
}

const bool DeckManager::exportDeck(const Deck& deck, const ExportFormat format) {
    // TOOD: Implement export functionality
    return false;
}

const bool DeckManager::importDeck(const std::string& filePath) {
    // TOOD: Implement import functionality
    return false;
}

const std::vector<Deck>& DeckManager::getDecks() const {
    return decks;
}

//MARK: Private methods

// Should save these as JSON files - so that changes to obj signatures don't break the save/load functionality
const void DeckManager::loadDecks() {
    // TOOD: Implement load functionality
}

const void DeckManager::saveDecks() {
    // TOOD: Implement save functionality
}