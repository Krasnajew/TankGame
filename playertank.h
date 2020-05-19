#ifndef PLAYERTANK_H
#define PLAYERTANK_H
#include "basetank.h"
#include <QKeyEvent>

class PlayerTank: public BaseTank
{
    Q_OBJECT
public:
    PlayerTank(QGraphicsItem * parent =0);

    void hpBarMod();
public slots:
    virtual void loadGun() override;
    //virtual void load
};

#endif // PLAYERTANK_H
