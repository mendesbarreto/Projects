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
    SpriteBatchNode* m_batch;
    
    Size m_screenSize;
    
    Array* m_goibaBadPool;
    
    int m_goibaBadFallingIndex;
    float m_goibaBadTime;
    float m_goibaBadInterval;

	Array* m_goibaGoodPool;

	int m_goibaGoodFallingIndex;
	float m_goibaGoodTime;
	float m_goibaGoodInterval;
    
    Action* m_swingFruit;
    Action* m_fruitFall;
    
    
    Sprite* m_player;
    Sprite* m_background;
    
    bool createActions();
    bool createScreen();
    bool createPools();
};

#endif // __HELLOWORLD_SCENE_H__
