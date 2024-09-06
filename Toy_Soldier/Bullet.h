#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

/**
 * @class Bullet
 * @brief Klasa reprezentująca pocisk w grze.
 *
 * Klasa Bullet odpowiada za obsługę pocisków wystrzeliwanych przez gracza w grze.
 */
class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy Bullet.
     *
     * Tworzy pocisk i ustawia jego kierunek.
     *
     * @param direction Kierunek poruszania się pocisku (0 - prawo, 1 - lewo, 2 - góra, 3 - dół).
     * @param parent Wskaźnik na rodzica obiektu graficznego.
     */
    Bullet(int direction, QGraphicsItem * parent=0);

public slots:
    /**
     * @brief Przesuwa pocisk w ustalonym kierunku i usuwa go, jeśli przekroczy granice sceny.
     */
    void move();

private:
    int direction; /**< Kierunek ruchu pocisku. */
};

#endif // BULLET_H
