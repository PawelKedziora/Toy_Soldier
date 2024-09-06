#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include <QMovie>
#include <QTimer>

Player::Player(const QString &animationFile, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), movie(nullptr), shootDirection(0), speed(10) {
    // Inicjalizacja QMovie z podanym plikiem GIF
    movie = new QMovie(animationFile);
    connect(movie, &QMovie::frameChanged, this, &Player::updatePixmap);
    movie->start(); // Rozpocznij animację

    QTimer * timer = new QTimer(this);
    timer->start(50);

    // Inicjalizacja dźwięku strzału
    shootSound = new QSoundEffect(this);
    shootSound->setSource(QUrl::fromLocalFile(":/sounds/bullet.wav"));
    shootSound->setVolume(0.25);  // Ustawienie głośności (0.0 - 1.0)
}

Player::~Player() {
    delete movie;
}

void Player::setShootDirection(int direction) {
    shootDirection = direction;
}

void Player::move(int dx, int dy) {
    setPos(x() + dx, y() + dy);
}

void Player::updatePixmap() {
    setPixmap(movie->currentPixmap().scaled(125, 125));
}

void Player::attack_animation(const QString &animationFile, int duration, const QString &basicAnimationFile) {
    if (movie) {
        movie->stop();
        movie->deleteLater();
        movie = nullptr;
    }

    // Inicjalizacja nowego QMovie z dostarczonym plikiem animacji
    movie = new QMovie(animationFile, QByteArray(), this);

    // Podłączemoe sygnał QMovie frameChanged, aby zaktualizować pixmapę playera
    connect(movie, &QMovie::frameChanged, this, &Player::updatePixmap);

    // uruchomienie animacji
    movie->start();

    // timer single shot aby powrócić do bazowej animacji po określonym czasie
    QTimer::singleShot(duration, this, [this, basicAnimationFile]() {
        // usunięcie bieżącego filmu po animacji ataku
        if (movie) {
            movie->stop();
            movie->deleteLater();  // usuwanie po przetworzeniu
            movie = nullptr;
        }

        // Inicjalizacja nowego QMovie z dostarczonym bazowym plikiem animacji
        movie = new QMovie(basicAnimationFile, QByteArray(), this);

        // Podłączenie sygnału QMovie frameChanged, aby zaktualizować pixmapę odtwarzacza
        connect(movie, &QMovie::frameChanged, this, &Player::updatePixmap);

        // uruchomienie bazowej animacji
        movie->start();
    });
}

void Player::keyPressEvent(QKeyEvent *event) {
    int sceneWidth = static_cast<int>(scene()->width());
    int sceneHeight = static_cast<int>(scene()->height());

    // Akcja gracza
    if (event->key() == Qt::Key_Left) {
        if (pos().x() > 0)
            move(-speed, 0);
    }
    else if (event->key() == Qt::Key_Right) {
        if (pos().x() + pixmap().width() < sceneWidth)
            move(speed, 0);
    }
    else if (event->key() == Qt::Key_Up) {
        if (pos().y() > 0)
            move(0, -speed);
    }
    else if (event->key() == Qt::Key_Down) {
        if (pos().y() + pixmap().height() < sceneHeight)
            move(0, speed);
    }
    // Strzał
    else if (event->key() == Qt::Key_Space) {
        Bullet *bullet = new Bullet(shootDirection);
        bullet->setPos(x()+125, y()+45);
        scene()->addItem(bullet);

        // Odtwórz dźwięk strzału
        shootSound->play();

        // Wywołanie animacji ataku
        attack_animation(":/images/PlayerShoot.gif", 500, ":/images/PlayerMove.gif");  // Plik GIF i czas trwania animacji (w milisekundach)
    }
}

void Player::spawn() {
    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);
}
