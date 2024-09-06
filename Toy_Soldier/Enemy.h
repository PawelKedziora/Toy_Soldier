#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMovie>

/**
 * @class Enemy
 * @brief Klasa reprezentująca przeciwnika w grze.
 *
 * Klasa Enemy odpowiada za tworzenie i poruszanie przeciwników w grze.
 */
class Enemy: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy Enemy.
     *
     * Tworzy przeciwnika na losowej pozycji na krawędzi sceny.
     *
     * @param parent Wskaźnik na rodzica obiektu graficznego.
     */
    Enemy(QGraphicsItem *parent = nullptr);

    /**
     * @brief Destruktor klasy Enemy.
     *
     * Usuwa obiekt QMovie używany do animacji przeciwnika.
     */
    ~Enemy();

public slots:
    /**
     * @brief Slot odpowiedzialny za poruszanie przeciwnikiem.
     *
     * Przesuwa przeciwnika i usuwa go, jeśli przekroczy granice sceny.
     */
    void move();

    /**
     * @brief Slot aktualizujący grafikę przeciwnika.
     *
     * Ustawia odpowiednią klatkę animacji jako obraz przeciwnika.
     */
    void updatePixmap();
private:
    int dx, dy; /**< Prędkości ruchu w poziomie (dx) i pionie (dy). */
    QMovie *movie; /**< Wskaźnik na animację przeciwnika. */
};

#endif // ENEMY_H
