#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Game.h"

extern Game * game;

Bullet::Bullet(int direction, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent), direction(direction) {

    setPixmap(QPixmap(":/images/bullet.png").scaled(10, 10)); //rysowanie grafiki

    // Timer do przesuwania pocisku
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    // Start timera
    timer->start(50);
}

void Bullet::move(){
    // lista wszystkich elementów kolidujących z pociskiem
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //jeśli jednym ze zderzających się przedmiotów jest wróg, usuwa zarówno pocisk, jak i wroga
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            game->score->increase(); //zwiększa punktację
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    // Ruch pocisku w zależności od kierunku
    switch (direction) {
    case 0: setPos(x() + 10, y()); break; // Prawo
    case 1: setPos(x() - 10, y()); break; // Lewo
    case 2: setPos(x(), y() - 10); break; // Góra
    case 3: setPos(x(), y() + 10); break; // Dół
    }

    // Usunięcie pocisku, jeśli jest poza ekranem
    if (pos().y() + pixmap().height() < 0 || pos().x() < 0 || pos().x() > scene()->width() || pos().y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
