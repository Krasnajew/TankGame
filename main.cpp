#include "game.h"
#include <QApplication>
#include "enemytank.h"
//#include <QRandomGenerator>

//std::mt19937 EnemyTank::rng = std::mt19937(QRandomGenerator::global()->generate());
//std::mt19937 EnemyTank::rng = std::mt19937(65);
Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->start();
    return a.exec();
}
