#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include <QPushButton>
#include "ui_UiForm.h"
#include <vector>
#include <QMediaPlayer>
#include <QAudioOutput>

/**
 * @enum Formation
 * @brief Enum opisujący różne formacje graczy.
 */
enum class Formation {
    Line,
    Column,
    Wave,
    Square
};

/**
 * @class Game
 * @brief Klasa główna gry.
 *
 * Klasa Game odpowiada za główną logikę gry, zarządzanie sceną, oddziałem, przeciwnikami, muzyką itp.
 */
class Game : public QGraphicsView {
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy Game.
     *
     * Inicjalizuje scenę, tworzy gracza, ustawia tło i uruchamia muzykę w tle.
     *
     * @param parent Wskaźnik na rodzica widoku graficznego.
     */
    Game(QWidget * parent=0);

    QGraphicsScene * scene;   /**< Scena, na której odbywa się gra. */
    Player * player;          /**< Wskaźnik na głównego gracza. */
    Score * score;            /**< Wskaźnik na obiekt zarządzający punktacją. */
    Health * health;          /**< Wskaźnik na obiekt zarządzający zdrowiem gracza. */

    /**
     * @brief Dodaje nowego żołnierza do oddziału.
     */
    void addPlayer();

    /**
     * @brief Dodaje nowego oficera do oddziału.
     */
    void addPlayerOfficer();

    /**
     * @brief Usuwa ostatnio dodanego członka oddziału z gry.
     */
    void removeLastPlayer();
private slots:
    /**
     * @brief Ustawia formację oddziału.
     *
     * @param formation Formacja, która ma zostać ustawiona.
     */
    void setFormation(Formation formation);

    /**
     * @brief Obsługuje kliknięcie przycisku dodania żołnierza.
     */
    void on_pushButton_clicked();

    /**
     * @brief Reaguje na wybór formacji oddziału w comboBoxie.
     *
     * @param index Indeks wybranej formacji oddziału w comboBoxie.
     */
    void on_comboBox_activated(int index);

    /**
     * @brief Obsługuje kliknięcie przycisku usuwania ostatniego członka oddziału.
     */
    void on_pushButton_2_clicked();

    /**
     * @brief Obsługuje kliknięcie przycisku dodania oficera do oddział.
     */
    void on_pushButton_3_clicked();
private:
    /**
     * @brief Zmiana pozycji oddziału w określoną formację.
     *
     * @param formation Formacja, w której ma zostać ustawiony oddział.
     */
    void arrangeFormation(Formation formation);  // Deklaracja metody arrangeFormation

    QWidget *uiContainer; /**< Kontener UI dla widoku. */
    QPushButton *addPlayerButton; /**< Przycisk dodawania gracza. */
    Ui::Form ui; /**< Obiekt formularza UI. */
    std::vector<Player *> players; /**< Wektor przechowujący wskaźniki na graczy. */
    QMediaPlayer *backgroundMusic; /**< Wskaźnik na odtwarzacz muzyki. */
    Formation currentFormation = Formation::Line; /**< Aktualnie ustawiona formacja graczy. */

protected:
    /**
     * @brief Obsługuje zdarzenia naciśnięcia klawisza.
     *
     * @param event Wskaźnik na obiekt zdarzenia klawiatury.
     */
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAME_H
