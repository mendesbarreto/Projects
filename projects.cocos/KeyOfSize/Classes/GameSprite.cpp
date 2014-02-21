#include "GameSprite.h"

GameSprite::GameSprite( void ) :
	m_vector( ccp( 0 , 0 ) ),
	m_screenSize( Director::getInstance()->getWinSize() )
{

}

