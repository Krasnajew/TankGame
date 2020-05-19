#ifndef BASETANK_H
#define BASETANK_H

//#include "gameobject.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include "basebullet.h"
//#include "game.h"

//extern Game * game;

class BaseBullet;

class BaseTank: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    void fire();
    void reload(Qt::Key key); //change type of bullet
    void move(Qt::Key dir); //move tank on the screen. Argument: up, down, right, left
    virtual void takeDamage(int8_t damage);

    //getter
    int8_t getHeight() const {return height;};
    int8_t getWidth() const {return width;};
    int8_t getHp() const {return hp;};
    int8_t getHp_max() const {return hpMax;};
    int8_t getSpeed() const {return speed;};

    //virtual void posAdd(qreal x, qreal y);
public slots:
    virtual void loadGun(); //set loaded true

protected:
    BaseTank(int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF gunPoint);

    int8_t ID;
    int8_t hpMax;
    int8_t hp;
    int8_t speed;
    QPointF gunPoint;
    BaseBullet *bullet;
    bool loaded;

    //
private:
    const int8_t height = 50;
    const int8_t width = 40;


    bool collisionTest(); //return true if tank collide with something

};

#endif // BASETANK_H
