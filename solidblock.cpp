#include "solidblock.h"
#include <QGraphicsScene>
#include "game.h"

extern Game *game;

SolidBlock::SolidBlock():
    BaseBlock(22, 0, 0, false)//int8_t id, int8_t HP_M, int8_t HP, bool DESTR
{

    setRect(0, 0, getSize(), getSize());
    //destructable = false;
    setBrush(QPixmap(":/images/SolidBlock.png"));
}

void SolidBlock::createBlock(QPointF pos)
{
    SolidBlock *block = new SolidBlock();
    block->setPos(pos);
    //scene()->addItem(block);
    game->scene->addItem(block);
}
