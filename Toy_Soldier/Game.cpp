#include "Game.h"
#include "PlayerOfficer.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QMediaPlayer>

Game::Game(QWidget *parent) : QGraphicsView(parent) {
    ui.setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1920, 1080);

    // Ustawienie tła sceny
    QPixmap background(":/images/background.png");  // Ścieżka do pliku tła
    scene->setBackgroundBrush(background.scaled(1920, 1080, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920, 1080);

    // Inicjalizacja i odtwarzanie muzyki w tle
    backgroundMusic = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);  // nowy obiekt klasy QAudioOutput, który jest używany do odtwarzania dźwięku
    backgroundMusic->setAudioOutput(audioOutput);
    backgroundMusic->setSource(QUrl("qrc:/sounds/bgsound.mp3"));  // Ścieżka do pliku muzyki
    audioOutput->setVolume(0.5);  // Ustawienie głośności (0.0 - 1.0)
    backgroundMusic->play();  // Odtwarzanie muzyki

    //tworzenie gracza
    player = new PlayerOfficer(this);
    player->setPos(910, 490);
    scene->addItem(player);

    players.push_back(player); //dodaje element na końcu wektora

    //punktacja, życie
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);

    //Po wybraniu opcji z comboBox, slot on_comboBox_activated(int) zostanie wywołany
    connect(ui.comboBox, SIGNAL(activated(int)), this, SLOT(on_comboBox_activated(int)));

    // pojawianie się wrogów
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, player, &Player::spawn);
    timer->start(2000);
    show();
}

void Game::arrangeFormation(Formation formation) {
    int spacing = 20;

    switch (formation) {
    case Formation::Line:
        for (std::size_t i = 0; i < players.size(); ++i) {
            players[i]->setPos(i * (players[i]->boundingRect().width() + spacing), scene->height() / 2);
        }
        break;

    case Formation::Column:
        for (std::size_t i = 0; i < players.size(); ++i) {
            players[i]->setPos(scene->width() / 2, i * (players[i]->boundingRect().height() + spacing));
        }
        break;

    case Formation::Wave:
        for (std::size_t i = 0; i < players.size(); ++i) {
            int waveOffset = static_cast<int>(50 * sin(i * 0.5));
            players[i]->setPos(i * (players[i]->boundingRect().width() + spacing), (scene->height() / 2) + waveOffset);
        }
        break;

    case Formation::Square:
        int gridSize = static_cast<int>(sqrt(players.size()));
        for (std::size_t i = 0; i < players.size(); ++i) {
            int row = i / gridSize;
            int col = i % gridSize;
            players[i]->setPos(col * (players[i]->boundingRect().width() + spacing),
                               row * (players[i]->boundingRect().height() + spacing));
        }
        break;
    }
}

void Game::setFormation(Formation formation) {
    // Ustawienie wybranej formacji
    currentFormation = formation;

    // Przeorganizowanie graczy zgodnie z nową formacją
    arrangeFormation(currentFormation);
}

void Game::on_comboBox_activated(int index) {
    Formation formation;
    switch (index) {
    case 0: formation = Formation::Line; break;
    case 1: formation = Formation::Column; break;
    case 2: formation = Formation::Wave; break;
    case 3: formation = Formation::Square; break;
    default: return;
    }

    // Ustaw formację
    setFormation(formation);
}

void Game::addPlayerOfficer() {
    PlayerOfficer *newPlayerOfficer = new PlayerOfficer(this);

    int sceneWidth = static_cast<int>(scene->width());
    int sceneHeight = static_cast<int>(scene->height());
    int playerWidth = static_cast<int>(newPlayerOfficer->boundingRect().width());
    int playerHeight = static_cast<int>(newPlayerOfficer->boundingRect().height());

    int xPosition = rand() % (sceneWidth - playerWidth);
    int yPosition = rand() % (sceneHeight - playerHeight);
    newPlayerOfficer->setPos(xPosition, yPosition);

    int direction = players.size() % 4;
    newPlayerOfficer->setShootDirection(direction);

    scene->addItem(newPlayerOfficer);
    players.push_back(newPlayerOfficer);

    arrangeFormation(currentFormation);
}


void Game::addPlayer() {
    Player *newPlayer = new Player(":/images/PlayerMove.gif");

    // Ustawienie początkowej pozycji gracza
    int sceneWidth = static_cast<int>(scene->width());
    int sceneHeight = static_cast<int>(scene->height());
    int playerWidth = static_cast<int>(newPlayer->boundingRect().width());
    int playerHeight = static_cast<int>(newPlayer->boundingRect().height());

    int xPosition = rand() % (sceneWidth - playerWidth);
    int yPosition = rand() % (sceneHeight - playerHeight);
    newPlayer->setPos(xPosition, yPosition);

    // Ustawienie kierunku strzału na podstawie liczby graczy
    int direction = players.size() % 4; // 0 = góra, 1 = lewo, 2 = prawo, 3 = dół
    newPlayer->setShootDirection(direction);

    scene->addItem(newPlayer);
    players.push_back(newPlayer);

    // Przeorganizowanie graczy zgodnie z wybraną formacją
    arrangeFormation(currentFormation);
}

void Game::removeLastPlayer() {
    Player *lastPlayer = players.back(); // Pobierz ostatniego gracza
    scene->removeItem(lastPlayer);
    delete lastPlayer;
    players.pop_back(); // Usuń ostatni element
}

void Game::on_pushButton_clicked() {
    addPlayer();
}

void Game::keyPressEvent(QKeyEvent *event) {
    for (Player *player : players) {
        player->keyPressEvent(event);
    }
}

void Game::on_pushButton_2_clicked()
{
    removeLastPlayer();
}

void Game::on_pushButton_3_clicked()
{
    addPlayerOfficer();
}
