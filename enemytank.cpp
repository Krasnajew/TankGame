#include "enemytank.h"
#include "playertank.h"
#include <QRandomGenerator>

EnemyTank::EnemyTank(QGraphicsItem *parent):
     BaseTank(2, 30, 30, 10, QPointF(20,25)), //int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF gunPoint
        rng(std::mt19937(QRandomGenerator::global()->generate())),
        stop(false), follow(false), lookA(false)
{

    std::uniform_int_distribution<int> u(0,100);
    //qDebug()<<"random: "<< u(rng);

    setPixmap(QPixmap(":/images/enemytank.png"));
    setTransformOriginPoint(getWidth()/2, getHeight()/2);

    temp = QPointF(getWidth()/2+300, getHeight()/2);
    //set move Timer
    moveTim = new QTimer();
    moveTim->setInterval(100);
    connect(moveTim, &QTimer::timeout, this, &EnemyTank::moveSlot);
    backDir = Qt::Key_N; //N like null

    //set detection line
    QLineF nL(this->transformOriginPoint(), QPointF(transformOriginPoint().rx(), transformOriginPoint().ry()-500));
    nLine = new QGraphicsLineItem(nL, this);
    //set bullet
    reload(Qt::Key_1);

    //get tank move
    choseDest();


}

/*void EnemyTank::goDest()
{
    moveTim->start();
}*/

void EnemyTank::choseDest()
{

    std::uniform_int_distribution<int> u(0,3);
    Qt::Key temp;
    bool flag = true;

    //draw by lot direction
    while(flag)
    {
        int d = u(rng); //draw lots dir
        switch(d)
        {
        case 0:
            temp = Qt::Key_W;

        break;
        case 1:
            temp = Qt::Key_S;

        break;
        case 2:
            temp = Qt::Key_A;

        break;
        case 3:
            temp = Qt::Key_D;

        break;
        }

        if(backDir != temp) flag = false; //backtrack check
    }

    setDir(temp); //set direction

    //set bacDir to prevent backtrack in next move
    switch(dir)
    {
    case Qt::Key_W:
        backDir = Qt::Key_S;

    break;
    case Qt::Key_S:
         backDir = Qt::Key_W;

    break;
    case Qt::Key_A:
         backDir = Qt::Key_D;

    break;
    case Qt::Key_D:
         backDir = Qt::Key_A;

    break;
    default:
    break;
    }

   //draw by lot destination point
   std::uniform_int_distribution<int> p(100, 500);
   int mod = p(rng);

   //dest point depend on dir
   if(dir == Qt::Key_W || dir == Qt::Key_S)
   {
       destination.setX(pos().rx());

       if(dir == Qt::Key_W)
       {
           destination.setY(pos().ry()-mod);
       }
       else if(dir == Qt::Key_S)
       {
           destination.setY(pos().ry()+mod);
       }

   }
   else if(dir == Qt::Key_A || dir == Qt::Key_D)
   {
       destination.setY(pos().ry());

       if(dir == Qt::Key_A)
       {
           destination.setX(pos().rx()-mod);
       }
       else if(dir == Qt::Key_D)
       {
           destination.setX(pos().rx()+mod);
       }
   }

   //goDest();
   moveTim->start();
}

void EnemyTank::setDir(Qt::Key d)
{
    dir = d;

    switch(d)
    {
    case Qt::Key_W:
        this->setRotation(0);

    break;
    case Qt::Key_S:
        this->setRotation(180);

    break;
    case Qt::Key_D:
        this->setRotation(90);
    break;
    case Qt::Key_A:
        this->setRotation(-90);

    break;
    default:
    break;
    }

}

bool EnemyTank::playerDetect()
{
   stop = false; // if enemy tank not detect player again, enemytank start moving
   QList<QGraphicsItem*> colliding_item = nLine->collidingItems();

    std::for_each(colliding_item.begin(), colliding_item.end(), [this](auto i){
        if(typeid(*i) == typeid(PlayerTank))
        {
            //stop moving and fire if detect palyer
            this->fire();
            stop = true;
            follow = true;
            destination = i->pos();
            lookA = true;
            return true;
        }

    });
    return false;
}

void EnemyTank::moveSlot()
{

    if(!stop){
        lastPos = pos();
        move(dir);
    }
    playerDetect(); //sets destination to last player position

    QLineF ln(pos(), destination);
    //qDebug()<<ln.length();
    //qDebug()<<lookA;
    if(follow)
    {
        follow = false;
        moveTim->start();
    }
    //if tank reach dest point or hit the wall, chose new dest
    else if(ln.length()<30 || (lastPos == pos() && !lookA)) //chose new dest and dir if tank raech dest or tank stack on obsticle
    {
        //qDebug()<<"blip";
        lookA = false;
        destination = pos();
        moveTim->stop();
        choseDest();//chose new dest point

    }
}

void EnemyTank::lookAround()
{
    //qDebug()<<"blip";
    if(this->rotation() == 180 || this->rotation()== 0)
    {
        //qDebug()<<"180||0";
        this->setRotation(-90);
        dir = Qt::Key_A;
        if(playerDetect()) return;
        this->setRotation(90);
        dir = Qt::Key_D;
        if(playerDetect()) return;

    }
    else if(this->rotation() == 90 || this->rotation()== -90)
    {
        //qDebug()<<"-90||90";
        this->setRotation(0);
        dir = Qt::Key_W;
        if(playerDetect()) return;
        this->setRotation(180);
        dir = Qt::Key_S;
        if(playerDetect()) return;

    }
}
