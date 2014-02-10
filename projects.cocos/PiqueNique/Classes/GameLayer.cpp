#include "GameLayer.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->createScreen();
    this->createPools();
    this->createActions();

    return true;
}

bool GameLayer::createPools()
{
    m_fruitFallingIndex = 0;
    m_fruitPool = CCArray::createWithCapacity( 20 );
    
    for ( int i = 0 ; i < 20 ; i++) {
        
    }
    
    
    return true;
}

bool GameLayer::createActions()
{
    
    m_fruitInterval = 5;
    m_fruitTime = 0;
    
    
    
    
    return true;
}

bool GameLayer::createScreen()
{
    m_screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("piquenique.plist");
    m_batch = CCSpriteBatchNode::create( "piquenique.png" );
    this->addChild(m_batch);
    
    m_background = CCSprite::create("background.jpg");
    m_background->setPosition(
                              ccp( m_background->boundingBox().size.width * 0.5f
                                   , m_background->boundingBox().size.height * 0.5f));
    this->addChild(m_background);
    
    return true;
}

void GameLayer::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
