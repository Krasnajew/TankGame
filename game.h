#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "playertank.h"
#include <QObject>
#include <QKeyEvent>
#include "gameobject.h"
#include "blockfactory.h"
#include "progresbar.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QGraphicsView *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void createMap(); //create game map base on *map
    int16_t getMapHeight() const {return mapHeight;};
    int16_t getMapWidth() const {return mapWidth;};
    QGraphicsScene* getScene(){return scene;}; //delete
    void reloadBarTim();
    void setReloadBar(int8_t fill);
    void setHpBar(int8_t fill);

    void start();

    QGraphicsScene *scene;
    PlayerTank *player;
private:
    BlockFactory *blockFactory;
    ProgresBar *reload; //show reload player gun
    ProgresBar *hpBar;

    QVector<QVector<int8_t>> *map; //store ID of game stuff
    const int16_t mapHeight = 900;
    const int16_t mapWidth = 1200;


    void addGameObject(int8_t ID, int8_t column, int8_t row);
    void createBlockFactory();
};
#endif // GAME_H