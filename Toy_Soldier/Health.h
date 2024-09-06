#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

/**
 * @class Health
 * @brief Reprezentuje zdrowie gracza w grze.
 *
 * Klasa ta odpowiada za zarządzanie i wyświetlanie zdrowia gracza na ekranie.
 */
class Health: public QGraphicsTextItem{
public:
    /**
     * @brief Konstruktor klasy Health.
     * @param parent Wskaźnik do elementu nadrzędnego.
     */
    Health(QGraphicsItem * parent=0);

    /**
     * @brief Zmniejsza zdrowie gracza o 1.
     */
    void decrease();

    /**
     * @brief Zwraca aktualną wartość zdrowia gracza.
     * @return Wartość zdrowia gracza.
     */
    int getHealth();
private:
    int health; /**< Przechowuje aktualną wartość zdrowia gracza. */
};

#endif // HEALTH_H
