#ifndef PLAYEROFFICER_H
#define PLAYEROFFICER_H

#include "Player.h"

/**
 * @brief Deklaracja wstępna klasy Game.
 *
 * Używana do zadeklarowania klasy Game bez jej pełnej definicji.
 * Pozwala klasie PlayerOfficer na korzystanie ze wskaźnika na instancję Game
 */
class Game;

/**
 * @class PlayerOfficer
 * @brief Reprezentuje oficera w grze, który dziedziczy po klasie Player.
 *
 * Klasa ta posiada inne animacje oraz dodatkową możliwość wezwania wsparcia.
 */
class PlayerOfficer : public Player {
    Q_OBJECT
public:

    /**
     * @brief Konstruktor klasy PlayerOfficer.
     * @param gameInstance Wskaźnik na obiekt klasy Game.
     * @param parent Wskaźnik do elementu nadrzędnego.
     */
    PlayerOfficer(Game *gameInstance, QGraphicsItem *parent = nullptr);

    /**
     * @brief Obsługuje naciśnięcia klawiszy przez użytkownika, w tym specjalną zdolnośc oficera.
     * @param event Zdarzenie klawiatury.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Wywołuje metodę wezwania wsparcia.
     */
    void callForSupport();
private:
    Game *game;  /**< Wskaźnik na instancję klasy Game. */
};

#endif // PLAYEROFFICER_H
