#include "CardExplorer.hpp"

CardExplorer::CardExplorer(const std::string& title, const std::vector<Card>& cards, QWidget *parent) : QWidget(parent) {
    qRegisterMetaType<Card>("Card");
    QVBoxLayout *layout = new QVBoxLayout(this);
    label = new QLabel(QString::fromStdString(title), this); 
    QLabel *debugLabel = new QLabel("Selected: None", this);
    QLabel *debugLabel2 = new QLabel("CardColor: None", this);

    
    // List View
    // TODO: Add Card Injest here
    listWidget = new QListWidget(this);
    initList(cards);

    // Enable single selection mode (default, but explicitly set)
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Connect selection change signal to update the label
    connect(listWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            [this, debugLabel, debugLabel2]() {
                QListWidgetItem *selectedItem = listWidget->currentItem();
                if (selectedItem) {
                    debugLabel->setText("Selected: " + selectedItem->text());
                    
                    Card card = selectedItem->data(Qt::UserRole).value<Card>();
                    debugLabel2->setText("CardColor: " + QString::fromStdString(card.getColors()));
                }
            });

    // Add widgets to the layout
    layout->addWidget(listWidget);
    layout->addWidget(debugLabel);
    layout->addWidget(debugLabel2);
    layout->addWidget(label);
}

void CardExplorer::addCard(const Card& card) {
    QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(card.getName()), listWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(card));
}

void CardExplorer::initList(const std::vector<Card>& cards) {
    for (const Card& card : cards) {
        addCard(card);
    }
}

Card CardExplorer::getSelectedCard() {
    QListWidgetItem *selectedItem = listWidget->currentItem();
    if (selectedItem) {
        return selectedItem->data(Qt::UserRole).value<Card>();
    }
    return Card();
}