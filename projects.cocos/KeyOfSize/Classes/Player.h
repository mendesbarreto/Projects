#ifndef __PLAYER_H__
#define  __PLAYER_H__

#define PLAYER_INITIAL_SPEED 8
#include "cocos2d.h"
#include "GameSprite.h"

using namespace cocos2d;

enum PlayerState
{
	kPlayerMoving,
	kPlayerFalling,
	kPlayerDying
};

class Player : public GameSprite
{
	bool m_hasFloated;

	int m_floatingTimerMax;
	int m_floatingInterval;

	float m_speed;
	float m_floatingTimer;

	void initPlayer(void);

public:
	Player(void);

	CC_SYNTHESIZE(PlayerState, m_state, State);

	static Player* create();

	virtual void update(float dt);
	void setFloating(bool value);
	void reset(void);

	inline virtual void place() {
		this->setPositionY( m_nextPosition.y );

		if( m_vector.x > 0 && this->getPositionX < m_screenSize.width * 0.2f )
		{
			this->setPositionX( this->getPositionX() + m_vector.x );

			if( this->getPositionX() > m_screenSize.width * 0.2f )
			{
				this->setPositionX( m_screenSize.width * 0.2f );
			}

		}
	}

	inline int left()
	{
		return this->getPositionX() - m_width * 0.5f;
	}

	inline int right() {

	inline int next_left() {

};

#endif //__PLAYER_H__