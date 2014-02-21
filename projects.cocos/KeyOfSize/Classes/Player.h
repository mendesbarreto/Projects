#ifndef __PLAYER_H__
#define  __PLAYER_H__

#define PLAYER_INITIAL_SPEED 8#define PLAYER_JUMP 42#define GRAVITY 1.5#define FLOATNG_GRAVITY 0.4#define TERMINAL_VELOCITY 70#define FLOATING_FRICTION 0.98f#define AIR_FRICTION 0.99f
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

	CC_SYNTHESIZE(PlayerState, m_state, State);	CC_SYNTHESIZE(bool, m_inAir, InAir);	CC_SYNTHESIZE_READONLY( bool, m_floating, Floating );	CC_SYNTHESIZE(bool, m_jumping, Jumping);	CC_SYNTHESIZE(float, m_maxSpeed, MaxSpeed);

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

	inline int right() {		return this->getPositionX() + m_width * 0.5f;	}	inline int top() {		return this->getPositionY() ;	}	inline int bottom() {		return this->getPositionY() - m_height  ;	}

	inline int next_left() {		return m_nextPosition.x - m_width * 0.5f;	}	inline int next_right() {		return m_nextPosition.x + m_width * 0.5f;	}	inline int next_top() {		return m_nextPosition.y ;	}	inline int next_bottom() {		return m_nextPosition.y - m_height;	}

};

#endif //__PLAYER_H__