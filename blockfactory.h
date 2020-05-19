#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include "baseblock.h"
#include "dirtblock.h"
#include "solidblock.h"
#include "normalbullet.h"
#include "playertank.h"

class BlockFactory
{
public:
    BlockFactory(std::vector<BaseBlock*> BL);

    void createBlock(int8_t ID, QPointF pos);
private:
    std::vector<BaseBlock*> blockList;


};

#endif // BLOCKFACTORY_H
