#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/**
 * @class Score
 * @brief Reprezentuje punktację gracza w grze.
 *
 * Klasa ta zarządza aktualną punktacją oraz jej wyświetlaniem na ekranie.
 */
class Score: public QGraphicsTextItem{
public:

    /**
     * @brief Konstruktor klasy Score.
     * @param parent Wskaźnik do elementu nadrzędnego.
     */
    Score(QGraphicsItem * parent=0);

    /**
     * @brief Zwiększa aktualną punktację o 1.
     */
    void increase();

    /**
     * @brief Zwraca aktualną punktację.
     * @return Aktualna punktacja gracza.
     */
    int getScore();

private:
    int score; /**< Przechowuje aktualną punktację.*/
};

#endif // SCORE_H
