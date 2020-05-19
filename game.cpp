#include "game.h"
#include <QDebug>
#include "dirtblock.h"
#include "solidblock.h"
#include "normalbullet.h"
#include <QTimer>
#include "gameobject.h"
#include "baseblock.h"
#include "blockfactory.h"
#include "concreteblock.h"
#include "enemytank.h"


int8_t BaseBlock::size = 60;

Game::Game(QGraphicsView *parent)
    : QGraphicsView(parent)
{
    //set scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, getMapWidth(), getMapHeight()+30);
    setFixedSize(getMapWidth(), getMapHeight()+30);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}
void Game::keyPressEvent(QKeyEvent *event)
{
    static int t = 100;
    switch (event->key() )
    {
    case Qt::Key_T: //test key
        reload->setFill(t);
          t -=10;
    break;
    case Qt::Key_1:
        player->reload(Qt::Key_1 );
    break;
    case Qt::Key_2:
        player->reload(Qt::Key_2);
    break;
    case Qt::Key_W:
        player->setRotation(0);
        player->move(Qt::Key_W);
    break;
    case Qt::Key_S:
        player->setRotation(180);
        player->move(Qt::Key_S);
    break;
    case Qt::Key_A:
        player->setRotation(-90);
        player->move(Qt::Key_A);
    break;
    case Qt::Key_D:
        player->setRotation(90);
        player->move(Qt::Key_D);
    break;
    case Qt::Key_Space:
        player->fire();
    break;
    case Qt::Key_Q: //change bullet
        static int i = 0;
        QGraphicsScene *scene2 = new QGraphicsScene(this);
        scene2->setSceneRect(0, 0, 200, 200);
        setFixedSize(200, 200);
        setScene(scene2);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        setScene(scene2);

        i++;

        if(i>1){
            //scene = new QGraphicsScene(this);
            scene->setSceneRect(0, 0, getMapWidth(), getMapHeight());
            setFixedSize(getMapWidth(), getMapHeight());
            setScene(scene);
            i=0;

        }
    break;


}
}

void Game::createMap()
{
   //map of ID
   /*QVector<QVector<int8_t>> d = {
       {22, 22 ,22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 23, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
      {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
      {22, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
      {22, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
      {22, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 22 ,22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,},

   };*/
   QVector<QVector<int8_t>> d = {
       {22, 22 ,22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 21, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 21, 0,0, 0, 0, 0,0, 0, 23, 22,},
       {22, 0, 0, 0, 21, 21, 0, 0,0, 21, 0, 23,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 21, 21, 0, 0,0, 21, 0, 23,23, 23, 23, 23,23, 0, 0, 22,},
       {22, 0, 0, 0, 21, 21, 0, 0,0, 0, 21, 23,21, 21, 21, 21,21, 23, 23, 22,},
       {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,23, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 0, 0, 0, 0, 0, 22,0, 0, 0, 0,23, 0, 0, 0,0, 0, 0, 22,},
      {22, 0, 0, 0, 0, 0, 0, 0,0, 0, 23, 23,23, 0, 0, 0,0, 0, 0, 22,},
      {22, 0, 23, 0, 0, 22, 22, 22,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 21,21, 21, 21, 21,23, 23, 0, 22,},
      {22, 0, 23, 0, 0, 22, 22, 22,22, 0, 23, 23,23, 23, 23, 23,23, 23, 23, 22,},
      {22, 0, 23, 0, 0, 0, 0, 22,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 22,},
       {22, 22 ,22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,22, 22, 22, 22,},

   };

    /*QVector<QVector<int8_t>> d = {
        {21, 21 ,21, 21,21, 21, 21, 21,21, 21, 21, 21,21, 21, 21, 21,21, 21, 21, 21,},
        {21, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 23, 21,},
        {21, 0, 0, 0, 0, 0, 23, 0,0, 0, 0, 0,23, 0, 23, 0,0, 0, 23, 21,},
        {21, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 23, 21,},
        {21, 0, 23, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 23, 21,},
        {21, 0, 23, 0, 0, 0, 0, 21,21, 21, 0, 0,21, 21, 21, 0,23, 0, 0, 21,},
        {21, 0, 0, 0, 23, 0, 0, 21,21, 21, 0, 0,21, 21, 21, 0,0, 23, 0, 21,},
        {21, 0, 0, 0, 0, 0, 0, 21,21, 21, 0, 0,21, 21, 21, 23,0, 23, 0, 21,}, //this line too
        {21, 0, 0, 0, 0, 0, 0, 0,0, 23, 0, 0,23, 0, 0, 0,23, 0, 0, 21,}, //to
      {21, 0, 0, 0, 0, 23, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 23, 0, 21,}, //to
        {21, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 21, 0,23, 0, 0, 21,}, //to
       {21, 0, 23, 0, 0, 0, 0, 0,0, 23, 0, 0,0, 0, 21, 0,23, 0, 0, 21,}, //game crash when destroy 23 block in this line
       {21, 0, 0, 0, 0, 23, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 23, 0, 21,}, //to
        {21, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 23,0, 23, 0, 21,}, //to
        {21, 21 ,21, 21,21, 21, 21, 21,21, 21, 21, 21,21, 21, 21, 21,21, 21, 21, 21,}, //to

    };*/
   map = new QVector<QVector<int8_t>>(d);
   //qDebug()<<map[0][0];

   int8_t column = 0;
   int8_t row = 0;
   //create and add to scene acording to 2d vector of ID
   std::for_each(map[0].begin(), map[0].end(), [this, &column, &row](auto i){
       std::for_each(i.begin(), i.end(), [this, &row, &column](auto x){
           if(x>=21 && x<=50){ //block ID range is: 21-50
               blockFactory->createBlock(x, QPointF(row*60, column*60)); //60 is block size
           }
           row++;
       });
       column++;
       row=0;
   });


}

void Game::reloadBarTim()
{
    setReloadBar(0);
}

void Game::setReloadBar(int8_t fill)
{
    reload->setFill(fill);
}

void Game::setHpBar(int8_t fill)
{
    hpBar->setFill(fill);
}

void Game::start()
{
    //set Player
    player = new PlayerTank();
    player->setPos(100, 100);
    scene->addItem(player);
    player->reload(Qt::Key_1); //gear up normal bullet

    //set reload bar
    reload = new ProgresBar(100, 15, 100, QPointF(90, 910));
    QGraphicsTextItem* reloadText = new QGraphicsTextItem(QString("Reload: "));
    QFont font("Tokyo", 15);
    reloadText->setFont(font);
    reloadText->setPos(10, 900);
    scene->addItem(reloadText);

    //set hp bar
    hpBar = new ProgresBar(100, 15, 100, QPointF(350 ,910));
    QGraphicsTextItem* hpText = new QGraphicsTextItem(QString("HP: "));
    QFont font1("Tokyo", 15);
    hpText->setFont(font1);
    hpText->setPos(300, 900);
    scene->addItem(hpText);

    createBlockFactory();
    createMap();

    //set Enemy
    EnemyTank* enemy = new EnemyTank();
    enemy->setPos(QPointF(200, 200));
    scene->addItem(enemy);

    /*EnemyTank* enemy2 = new EnemyTank();
    enemy2->setPos(QPointF(500, 100));
    scene->addItem(enemy2);

    EnemyTank* enemy3 = new EnemyTank();
    enemy3->setPos(QPointF(200, 300));
    scene->addItem(enemy3);*/
}


void Game::createBlockFactory()
{
    std::vector<BaseBlock*> temp;

    DirtBlock *dr = new DirtBlock();
    SolidBlock *sd = new SolidBlock();
    ConcreteBlock *cr = new ConcreteBlock();

    temp.push_back(dr);
    temp.push_back(sd);
    temp.push_back(cr);

    blockFactory = new BlockFactory(temp);
}
