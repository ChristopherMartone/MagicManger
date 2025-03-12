#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include "ViewControllers/CardExplorer.hpp"
#include "DataModel/Card.hpp"
#include "DataModel/Collection.hpp"
#include "AssetManagers/DatabaseManager.cpp"
#include "string"
#include <QFile>
#include <iostream> 


void printMemoryUsage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        #ifdef __APPLE__z
            std::cout << "Memory Usage: " << (usage.ru_maxrss / 1024) << " KB" << std::endl;
        #else
            std::cout << "Memory Usage: " << usage.ru_maxrss << " KB" << std::endl;
        #endif
    } else {
        std::cerr << "Error getting memory usage!" << std::endl;
    }
}

// Save collection to file
void saveCollectionToFile(const Collection& collection, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening file for saving:" << file.errorString();
        return;
    }
    QDataStream out(&file);
    out << collection;
    file.close();
}

// Load collection from file
Collection loadCollectionFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file for loading:" << file.errorString();
        return Collection("All Cards", "All cards in the database");
    }
    QDataStream in(&file);
    Collection collection;
    in >> collection;
    file.close();
    return collection;
}


int main(int argc, char *argv[]) {
    std::printf("Starting Magic Manager Pro\n");
    QApplication app(argc, argv);

    QString savePath = "./Data/AllCards.dat";

    // Try to load collection from file
    Collection allCards = loadCollectionFromFile(savePath);

    if (allCards.getCards().empty()) {
        qDebug() << "No saved data found, loading from database...";
        // Connect to database
        if (!DatabaseManager::instance().connectDatabase("./Data/AllPrintings.sqlite")) {
            return -1;
        }
        QVector<Card> cards = DatabaseManager::instance().getAllCards();
        for (Card &card : cards) {
            allCards.addCard(card);
        }
        // Save collection to file
        saveCollectionToFile(allCards, savePath);
    } else {
        qDebug() << "Loaded collection from file!";
    } 

    // Create the main window
    QMainWindow window;
    window.setWindowTitle("Magic Manager Pro");
    window.resize(1400, 800);

    // Create a QTabWidget
    QTabWidget *tabWidget = new QTabWidget();

    // All Card Explorer Tab + Add CE Widget to it
    QWidget *allCardsTab = new QWidget();
    QVBoxLayout *allCardsLayout = new QVBoxLayout(allCardsTab);

    CardExplorer *cardEx = new CardExplorer("CE #1", allCards.getCards());
    allCardsLayout->addWidget(cardEx);


    // Create the Library Manager Tab
    QWidget *libraryManagerTab = new QWidget();
    QVBoxLayout *libraryManagerLayout = new QVBoxLayout(libraryManagerTab);

    // Create Deck Manager Tab
    QWidget *deckManagerTab = new QWidget();
    QVBoxLayout *deckManagerLayout = new QVBoxLayout(deckManagerTab);
    QLabel *label3 = new QLabel("This tab does not use the subview");
    deckManagerLayout->addWidget(label3);

    // Add the tabs to the QTabWidget
    tabWidget->addTab(allCardsTab, "Card Explorer");
    tabWidget->addTab(libraryManagerTab, "Library Manager");
    tabWidget->addTab(deckManagerTab, "Deck Manager");

    // Set QTabWidget as the central widget of the main window
    window.setCentralWidget(tabWidget);

    // Show the main window
    window.show();
    printMemoryUsage();

    return app.exec();
}