#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QMovie>
#include <QSoundEffect>

/**
 * @class Player
 * @brief Reprezentuje żołnierza w grze.
 *
 * Klasa ta zawiera logikę ruchu gracza, obsługę klawiszy i animację ataku.
 */
class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:

    /**
     * @brief Konstruktor klasy Player.
     * @param animationFile Ścieżka do pliku z animacją.
     * @param parent Wskaźnik do elementu nadrzędnego.
     */
    Player(const QString &animationFile, QGraphicsItem *parent = nullptr);

    /**
     * @brief Destruktor klasy Player.
     */
    ~Player();

    /**
     * @brief Ustawia kierunek strzału.
     * @param direction Kierunek strzału (0 - prawo, 1 - lewo, 2 - góra, 3 - dół).
     */
    void setShootDirection(int direction);

    /**
     * @brief Przesuwa o zadane wartości.
     * @param dx Przesunięcie w osi X.
     * @param dy Przesunięcie w osi Y.
     */
    void move(int dx, int dy);

    /**
     * @brief Obsługuje naciśnięcia klawiszy przez użytkownika.
     * @param event Zdarzenie klawiatury.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Aktualizuje aktualną klatkę animacji.
     */
    void updatePixmap();

    /**
     * @brief Wywołuje animację ataku .
     * @param animationFile Ścieżka do pliku z animacją ataku.
     * @param duration Czas trwania animacji w milisekundach.
     * @param basicAnimationFile Ścieżka do pliku z podstawową animacją.
     */
    void attack_animation(const QString &animationFile, int duration, const QString &basicAnimationFile);

public slots:
    /**
     * @brief Metoda odpowiedzialna za tworzenie wrogów w grze.
     */
    void spawn();

private:
    QMovie *movie; /**< Wskaźnik na animację. */
    int shootDirection; /**< Kierunek strzału. */
    int speed; /**< Prędkość poruszania się. */
    QSoundEffect *shootSound; /**< Dźwięk strzału. */
};

#endif // PLAYER_H
