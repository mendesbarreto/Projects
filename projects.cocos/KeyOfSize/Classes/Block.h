#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;


enum  {
	kBlockGap,
	kBlock1,
	kBlock2,
	kBlock3,
	kBlock4

};

class Block : public GameSprite{

	int m_tileWidth;
	int m_tileHeight;


	void initBlock(void);

public:

	CC_SYNTHESIZE(int, m_type, Type);

	Block();
	~Block();

	static Block * create();
	void setupBlock (int width, int height, int type);
};

#endif // __BLOCK_H__