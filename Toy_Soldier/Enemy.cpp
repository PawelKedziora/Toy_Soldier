#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <cstdlib> // rand() -> really large int
#include "Game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), dx(0), dy(0) {

    // Losowanie początkowej pozycji i kierunku ruchu
    int edge = rand() % 4; // Losowanie jednej z czterech krawędzi: 0 = góra, 1 = dół, 2 = lewa, 3 = prawa
    int sceneWidth = 1920; // szerokość sceny
    int sceneHeight = 1080; // wysokość sceny

    // Ustawienie początkowej pozycji i kierunku w zależności od losowanej krawędzi
    switch(edge) {
    case 0: // Góra
        setPos(rand() % sceneWidth, 0);  // Pojawia się losowo na górnej krawędzi
        dx = 0;   // Ruch tylko w dół
        dy = rand() % 5 + 1; // losowa prędkość w dół
        break;
    case 1: // Dół
        setPos(rand() % sceneWidth, sceneHeight);  // Pojawia się losowo na dolnej krawędzi
        dx = 0;   // Ruch tylko w górę
        dy = -(rand() % 5 + 1); // losowa prędkość w górę
        break;
    case 2: // Lewa
        setPos(0, rand() % sceneHeight);  // Pojawia się losowo na lewej krawędzi
        dx = rand() % 5 + 1; // losowa prędkość w prawo
        dy = 0;   // Brak ruchu pionowego
        break;
    case 3: // Prawa krawędź
        setPos(sceneWidth - 100, rand() % sceneHeight);  // Ustaw pozycję tak, aby przeciwnik nie był poza ekranem
        dx = -(rand() % 5 + 1); // losowa prędkość w lewo
        dy = 0;   // Brak ruchu pionowego
        break;
    }

    // Inicjalizacja QMovie z plikiem GIF
    movie = new QMovie(":/images/enemy.gif"); // Ścieżka do pliku GIF
    connect(movie, &QMovie::frameChanged, this, &Enemy::updatePixmap);
    movie->start(); // Rozpocznij animację

    // Podłączenie timera do metody move()
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);

    // Uruchomienie timera do przesuwania przeciwnika
    timer->start(50);
}

Enemy::~Enemy() {
    delete movie; // Usuwanie QMovie w destruktorze
}

void Enemy::move() {
    // Poruszanie przeciwnikiem zgodnie z losowymi wartościami dx i dy
    setPos(x() + dx, y() + dy);

    // Jeśli przeciwnik wyjdzie poza ekran
    if (x() < 0 || x() > 1920 || y() < 0 || y() > 1080) {
        // Zmniejszenie zdrowia
        game->health->decrease();

        // Usunięcie przeciwnika ze sceny i zwolnienie pamięci
        scene()->removeItem(this);
        delete this;
    }
}

void Enemy::updatePixmap() {
    // Ustawia aktualną klatkę animacji jako obrazek przeciwnika
    setPixmap(movie->currentPixmap().scaled(100, 100)); // Dopasowanie rozmiaru
    }
