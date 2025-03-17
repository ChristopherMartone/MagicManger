#include "./DeckExplorer.hpp"

DeckExplorer::DeckExplorer(const std::string& title, QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    label = new QLabel(QString::fromStdString(title), this); 
    QLabel *debugLabel = new QLabel("Selected: None", this);
    QLabel *debugLabel2 = new QLabel("DeckFormat: None", this);

    
    // List View
    listWidget = new QListWidget(this);
    initList();

    // Enable single selection mode (default, but explicitly set)
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Connect selection change signal to update the label
    connect(listWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            [this, debugLabel, debugLabel2]() {
                QListWidgetItem *selectedItem = listWidget->currentItem();
                if (selectedItem) {
                    debugLabel->setText("Selected: " + selectedItem->text());
                    
                    Deck deck = selectedItem->data(Qt::UserRole).value<Deck>();
                    debugLabel2->setText("DeckFormat: " + QString::fromStdString(deck.getFormat()));
                }
            });

    // Add widgets to the layout
    layout->addWidget(listWidget);
    layout->addWidget(debugLabel);
    layout->addWidget(debugLabel2);
    layout->addWidget(label);
}

void DeckExplorer::initList() {
    for (const Deck& deck : deckManager.getDecks()) {
        addDeck(deck);
    }
}

void DeckExplorer::addDeck(const Deck &deck) {
    deckManager.addDeck(deck);
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(deck.getName()), listWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(deck));
}

void DeckExplorer::removeDeck() {
    Deck l_deck = getSelectedDeck();
    deckManager.removeDeck(l_deck);
}

Deck DeckExplorer::getSelectedDeck() {
    QListWidgetItem *selectedItem = listWidget->currentItem();
    if (selectedItem) {
        return selectedItem->data(Qt::UserRole).value<Deck>();
    }
    return Deck();
}