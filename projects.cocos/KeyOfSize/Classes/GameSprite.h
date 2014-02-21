#ifndef __GAME_SPRITE_H__
#define  __GAME_SPRITE_H__

#include "cocos2d.h"

using namespace cocos2d;

enum
{
	kBackground,
	kMiddleground,
	kForeground
};

class GameSprite : public Sprite
{
public:
	GameSprite(void);

protected:
	Size m_screenSize;

public:
	CC_SYNTHESIZE( Point, m_nextPosition, NextPosition );
	CC_SYNTHESIZE( float , m_width, Width );
	CC_SYNTHESIZE( float , m_height , Height );
	CC_SYNTHESIZE( Point , m_vector , Vector );

	inline virtual void place () { this->setPosition( m_nextPosition ); }

	inline void setSize() {
		m_width = this->boundingBox().size.width;
		m_height = this->boundingBox().size.height;
	}

};

#endif //__GAME_SPRITE_H__