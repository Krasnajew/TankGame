#include "basebullet.h"
#include "superbullet.h"
#include "enemytank.h"
#include "playertank.h"
#include "game.h"
#include "dirtblock.h"
#include "solidblock.h"
#include "concreteblock.h"
#include "QDebug"

extern Game * game;

BaseBullet::BaseBullet(int8_t id, int8_t DAMAGE, int8_t SPEED, int8_t RANGE, int8_t RTime):
    ID(id), damage(DAMAGE), speed(SPEED), range(RANGE), reloadTime(RTime)
{

}

bool BaseBullet::collisionTest()
{
    //armCnt++;
    bool flag = false;
    //get all coliding_item, compare bullet Damage to target hp, delete bullet


        QList<QGraphicsItem*> colliding_item = this->collidingItems();
    // qDebug()<<colliding_item.size();


        std::for_each(colliding_item.begin(), colliding_item.end(), [&flag, this](auto i){

            if(dynamic_cast<BaseBlock*>(i) != nullptr){
                dynamic_cast<BaseBlock*>(i)->takeDamage(this->getDamage());
                auto p = i->pos() + QPointF(-45, -45);
                this->kaboom(p);
                flag = true;
            }
            else if(dynamic_cast<BaseBullet*>(i) != nullptr){

                flag = true;
            }
            else if(dynamic_cast<EnemyTank*>(i) != nullptr)
            {
                dynamic_cast<EnemyTank*>(i)->takeDamage(this->getDamage());
                auto p = i->pos() + QPointF(-45, -45);
                this->kaboom(p);
                flag = true;
            }
            else if(dynamic_cast<PlayerTank*>(i) != nullptr)
            {
                dynamic_cast<PlayerTank*>(i)->takeDamage(this->getDamage());
                auto p = i->pos() + QPointF(-45, -45);
                this->kaboom(p);
                dynamic_cast<PlayerTank*>(i)->hpBarMod();
                flag = true;
            }
            //else if

        });
        if(flag)
        {

            return true;
        }
        else return false;


}

void BaseBullet::move()
{
   qreal angle = this->rotation();
   QPointF temp = pos();

   //static int i = 0;

   if(angle==0) //move bullet acording to angle
   {
        setPos(x(), y()-speed);
   }
   else if(angle==180)
   {
        setPos(x(), y()+speed);
   }
   else if(angle==90)
   {
       setPos(x()+speed, y());
   }
   else if(angle==-90)
   {
       setPos(x()-speed, y());
   }

   //i++;

       if(collisionTest()) //check range
       {

           //qDebug()<<"dzieje sie";
           game->getScene()->removeItem(this);
           delete this;

       }


}
