#ifndef DECK_EXPLORER_HPP
#define DECK_EXPLORER_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>

#include "../DataModel/Deck.hpp"
#include "../DataModel/DeckManager.hpp"

class DeckExplorer : public QWidget {
    public:
        explicit DeckExplorer(const std::string& title, QWidget *parent = nullptr);
        void addDeck(const Deck& deck);
        void removeDeck();
        Deck getSelectedDeck();
    private:
        DeckManager& deckManager = DeckManager::instance();
        QLabel *label;
        QListWidget *listWidget;
        void initList();

};
#endif