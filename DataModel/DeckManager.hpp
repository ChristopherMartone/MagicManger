#ifndef DECKMANAGER_HPP
#define DECKMANAGER_HPP

#include "Deck.hpp"
#include "../Utils/DateTime.hpp"

enum class ExportFormat: u_int8_t {
    JSON,
    CSV,
    TXT,
    ARENA,
    TBD
};

class DeckManager {
    public:
    static DeckManager& instance();
    const Deck getDeckWithName(const std::string& name);
    void addDeck(const Deck& deck);
    void removeDeck(Deck& deck);
    void removeDeckWithName(std::string& name);
    const bool exportDeck(const Deck& deck, const ExportFormat format);
    const bool importDeck(const std::string& filePath);
    const std::vector<Deck>& getDecks() const;

    private:
    DeckManager();
    std::vector<Deck> decks;
    const void loadDecks();
    const void saveDecks();

    

};

#endif