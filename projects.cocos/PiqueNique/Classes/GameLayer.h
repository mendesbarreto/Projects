#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    
private:
    CCSpriteBatchNode* m_batch;
    
    CCSize m_screenSize;
    
    CCArray* m_fruitPool;
    
    int m_fruitFallingIndex;
    float m_fruitTime;
    float m_fruitInterval;
    
    CCAction* m_swingFruit;
    CCAction* m_fruitFall;
    
    
    CCSprite* m_player;
    CCSprite* m_background;
    
    
    bool createActions();
    bool createScreen();
    bool createPools();
};

#endif // __HELLOWORLD_SCENE_H__
