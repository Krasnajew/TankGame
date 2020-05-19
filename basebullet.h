#ifndef BASEBULLET_H
#define BASEBULLET_H

//#include "gameobject.h"
#include <QGraphicsRectItem>
#include <QObject>
#include "basetank.h"

class GameObject;

class BaseBullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    virtual void shot(QPointF coord, qreal angle)=0; //create new bullet, make it move
    virtual void kaboom(QPointF pos){}; //make kaboom
    int8_t getDamage() const {return damage;};
    int8_t getSpeed() const {return speed;};
    int8_t getReloadTime() const {return reloadTime;};

    //BaseTank *owner;

    bool collisionTest();

    //virtual void posAdd(qreal x, qreal y);
public slots:
    void move(); //make bullet move and check collision

protected:
    BaseBullet(int8_t id, int8_t DAMAGE, int8_t SPEED, int8_t RANGE, int8_t RTime);

    //int8_t armCnt;
    int8_t ID;
    int8_t damage;
    int8_t speed;
    int8_t range;
    int8_t reloadTime;
    //BaseTank *owner;
};

#endif // BASEBULLET_H
