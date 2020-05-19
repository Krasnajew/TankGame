#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "basetank.h"
#include <QKeyEvent>
#include <QTimer>
#include <random>
#include <QDebug>

class EnemyTank: public BaseTank
{
    Q_OBJECT
public:
    EnemyTank(QGraphicsItem * parent =0);
    //void goDest(); //send tank to reach destination point
    void choseDest(); //chose random dir and destpoint,
    //getters
    QPointF getDest() const {return destination;}
    Qt::Key getDir() const{return dir;}
    //setters
    void setDest(QPointF d){destination = d;}
    void setDir(Qt::Key d);
    bool playerDetect(); //detect player and respond (fire!). return true if detect player
public slots:
    void moveSlot();
private:
    void lookAround(); //tank look around to detect player.

    QPointF destination;
    QPointF lastPos;
    Qt::Key dir;
    Qt::Key backDir;
    QTimer *moveTim;
    QPointF temp;
    QGraphicsLineItem *nLine; //north

    bool stop; //stop movement if true;
    bool follow; //if true enemy follow player
    bool lookA; //if true, tank look around

    std::mt19937 rng;

};

#endif // ENEMYTANK_H
