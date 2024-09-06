#include "PlayerOfficer.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include "Enemy.h"
#include "Bullet.h"
#include "Game.h"

PlayerOfficer::PlayerOfficer(Game *gameInstance, QGraphicsItem *parent)
    : Player(":/images/OfficerMove.gif", parent), game(gameInstance) {
}

void PlayerOfficer::keyPressEvent(QKeyEvent *event) {
    // Wywołanie obsługi klawiszy z klasy Player
    Player::keyPressEvent(event);

    // Dodatkowe wezwanie wsparcia na klawisz H
    if (event->key() == Qt::Key_H) {
        callForSupport();
    }
    // Inna animacja ataku dla spacji
    else if (event->key() == Qt::Key_Space) {
        // Wywołanie animacji ataku
        attack_animation(":/images/OfficerShoot.gif", 500, ":/images/OfficerMove.gif");
    }
}

void PlayerOfficer::callForSupport() {
    // animacja wezwania wsparcia
    attack_animation(":/images/OfficerCallForSupport.gif", 2000, ":/images/OfficerMove.gif");

    if (game) {
        game->addPlayer();  // Wywołaj metodę addPlayer() z Game
    }
}
