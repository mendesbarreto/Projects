//
//  Character.h
//  PiqueNique
//
//  Created by Mundo do Sitio on 07/02/14.
//
//

#ifndef __PiqueNique__Character__
#define __PiqueNique__Character__

#include "cocos2d.h"

using namespace cocos2d;

class Character : public CCSprite
{
private:
	char* m_name;
    char* m_animation;
	Animation* m_currentAnimation;
    Dictionary* m_animations;
    Character(void);
    
public:
    
    static Character* create( const char* frameName );
	static Animation* createAnimationWithName( 
		const char* sequenceName, 
		int frames , 
		float delay , 
		bool restoreOriginalFrame);
    
    void addAnimation( const char* name, Animation* anim );
    void gotoAndPlay( const char* state );
    void gotoAndStop( const char* state );
	void setCallbackOnAnimationComplete( const char* name , CallFuncN* callback );

	void stop();
	void play();
	void play( Vector<FiniteTimeAction*> &actions );

    Dictionary* getStates()
    {
        return m_animations;
    }
    
    const char* getCurrentState()
    {
        return m_animation;
    }
    
    const char* getName()
    {
        return m_name;
    }
    
};



#endif /* defined(__PiqueNique__Character__) */
