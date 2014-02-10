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

class Character : CCSprite
{
private:
    CCString* m_currentState;
    CCString* m_name;
    CCArray* m_states;
    Character(void);
    
public:
    
    static Character* createWithFrameName( const char* frameName );
    static Animation* createAnimationWithName( const char* name );
    
    void addAnimation( Animation* anim );
    void gotoAndPlay( const char* state );
    void gotoAndStop( const char* state );
    Character( const char* frameName );
    
    CCArray* getStates()
    {
        return m_states;
    }
    
    CCString* getCurrentState()
    {
        return m_currentState;
    }
    
    CCString* getName()
    {
        return m_name;
    }
    
};



#endif /* defined(__PiqueNique__Character__) */
