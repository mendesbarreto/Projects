//
//  Character.cpp
//  PiqueNique
//
//  Created by Mundo do Sitio on 07/02/14.
//
//

#include <string>
#include "cocos2d.h"
#include "Character.h"


using namespace cocos2d;

Character::Character( void )
{
	m_animations = Dictionary::create();
    m_animation = "def";
}

//************************************
// Method:    create
// FullName:  Character::create
// Access:    public static 
// Returns:   Character*
// Qualifier:
// Parameter: const char * frameName
// 
// This method should be used to create a Character instance
//************************************
Character* Character::create( const char* frameName )
{
	Character* character = new Character();
	character->initWithSpriteFrameName( frameName );
	character->retain();
	return character;
}

Animation* Character::createAnimationWithName( const char* sequenceName, 
											  int framesNumber , 
											  float delay , 
											  bool restoreOriginalFrame = true
											  )
{
	Animation* anim = Animation::create();
	SpriteFrame* frame;
	
	char buffer[200];
	char name[200];
	int i;

	strcpy( name , sequenceName);
	strcat( name , "%i.png");

	for (i = 1; i < framesNumber+1; i ++ )
	{
		strcpy(buffer , "");
		sprintf(buffer , name , i , sizeof( buffer )-1 );
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( buffer );

		CC_ASSERT( frame != NULL );
		anim->addSpriteFrame( frame );
	}

	anim->setDelayPerUnit( 1 / delay );
	anim->setRestoreOriginalFrame( restoreOriginalFrame );
	anim->retain();

	return anim;
}

void Character::addAnimation( const char* name, Animation* anim )
{
	CC_ASSERT( anim != NULL );
	
	m_currentAnimation = anim;
	m_animations->setObject( anim, name );
	m_animations->retain();
	
}

void Character::gotoAndPlay( const char* state )
{
	if( m_isPlaying && strcmp(state , m_animation) != 0 )
	{
		CCLOG( "Animation already has been played" );	
	}
	else
	{
		Animation* anim = (Animation *) m_animations->objectForKey( state );
		CC_ASSERT( anim != NULL );
		m_currentAnimation = anim;	
		play();	
	}
	
}

void Character::stop()
{
    m_isPlaying = false;
	this->stopAllActions();
}

void Character::play()
{
    m_isPlaying = true;
	this->runAction( RepeatForever::create( Animate::create( m_currentAnimation ) ) );
}

void Character::play( Vector<FiniteTimeAction*> &actions )
{
	Sequence* sequence = Sequence::create(actions );
	this->stopAllActions();
	this->runAction( RepeatForever::create( sequence )	 );

	this->play();
}

void Character::gotoAndStop( const char* state )
{
    m_isPlaying = false;
	this->stopAllActions();
}

void Character::setCallbackOnAnimationComplete( const char* name , CallFuncN* callback )
{

}

