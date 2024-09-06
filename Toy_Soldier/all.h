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

