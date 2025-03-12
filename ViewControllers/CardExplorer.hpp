#ifndef CARD_EXPLORER_HPP
#define CARD_EXPLORER_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <string>
#include <QListWidget>
#include "../DataModel/Card.hpp"
#include "../DataModel/Collection.hpp"

class CardExplorer : public QWidget {
public:
    explicit CardExplorer(const std::string& title, const std::vector<Card>& cards, QWidget *parent = nullptr);
    void addCard(const Card& card);
    Card getSelectedCard();
private:
    QLabel *label;
    QListWidget *listWidget;
    void initList(const std::vector<Card>& cards);
};
#endif