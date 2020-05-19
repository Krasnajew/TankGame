#ifndef BASEBLOCK_H
#define BASEBLOCK_H

//#include<QGraphicsPixmapItem>
//#include "gameobject.h"
#include <QGraphicsRectItem>
#include<QObject>

class GameObject;

class BaseBlock: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    void fire();
    void remove(); //remove from scene, delete item
    virtual void takeDamage(int8_t damage);
    //virtual void posAdd(qreal x, qreal y);
    virtual void createBlock(QPointF pos)=0; //create new block, set position and add to scene
    static int8_t getSize(){return size;};
    bool ifDestructable() const {return destructable;};
protected:
    BaseBlock(int8_t id, int8_t HP_M, int8_t HP, bool DESTR);

    int8_t ID;
    static int8_t size;
    int8_t hp_max;
    int8_t hp;
    bool destructable;

};

#endif // BASEBLOCK_H
