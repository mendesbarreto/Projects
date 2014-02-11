#include "GameLayer.h"
#include "Character.h"
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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile( "piquenique.plist" );

    this->createScreen();
    this->createPools();
    this->createActions();

    return true;
}

bool GameLayer::createPools()
{
    m_goibaBadFallingIndex = 0;
    m_goibaBadPool = Array::createWithCapacity( 20 );

	Character* character;

	char name[30] = "goiba_bad";
	char walk[30] = "goiba_bad_walk";
	char falling[30] = "goiba_bad_falling";
	char buffer[100];

	for ( int i = 1 ; i < 20 ; i++) 
	{
		strcpy(buffer , walk );
		sprintf( buffer , strcat(buffer , "%i.png") , 1 );
		character = Character::create( buffer );
		character->addAnimation( walk , Character::createAnimationWithName( walk , 40 , 60.0f , true ) );
		
		strcpy(buffer , falling );
		sprintf( buffer , strcat(buffer , "%i.png") , 1 );
		character->addAnimation( falling , Character::createAnimationWithName( falling , 1 , 60.0f , true ) );

		m_goibaBadPool->addObject(character);
    }

    m_goibaBadPool->retain();

	
	m_goibaGoodPool = Array::createWithCapacity(20);

	strcpy(walk , "goiba_good_waking" );
	strcpy(falling , "goiba_good_falling" );

	for ( int i = 1 ; i < 20 ; i++) 
	{
		strcpy(buffer , walk );
		sprintf( buffer , strcat(buffer , "%i.png") , 1 );
		character = Character::create( buffer );
		character->addAnimation( walk , Character::createAnimationWithName( walk , 19 , 60.0f , true ) );

		strcpy(buffer , falling );
		sprintf( buffer , strcat(buffer , "%i.png") , 1 );
		character->addAnimation( falling , Character::createAnimationWithName( falling , 1 , 60.0f , true ) );

		m_goibaGoodPool->addObject(character);
	}

	m_goibaGoodPool->retain();

	
	character->setPosition( ccp ( 200, 100 ) );
	character->gotoAndPlay( walk );
	
	Vector<FiniteTimeAction *> actions;
	actions.pushBack( RotateTo::create( 1 , -20 ) );
	actions.pushBack( RotateTo::create( 1 , 20 ) );
	character->play(actions);
	this->addChild( character );

    return true;
}

bool GameLayer::createActions()
{
    

	m_goibaBadInterval = 5;
	m_goibaBadTime = 0;
 
	m_goibaGoodTime = 0;
	m_goibaGoodInterval = 5;
    
    
    	/*
	character->setPosition( ccp ( 200, 100 ) );
	character->gotoAndPlay( walk );
	
	Vector<FiniteTimeAction *> actions;
	actions.pushBack( RotateTo::create( 1 , -20 ) );
	actions.pushBack( RotateTo::create( 1 , 20 ) );
	character->play(actions);
	this->addChild( character );*/
    
    return true;
}

bool GameLayer::createScreen()
{
    m_screenSize = Director::sharedDirector()->getWinSize();
    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("piquenique.plist");
    m_batch = SpriteBatchNode::create( "piquenique.png" );
    this->addChild(m_batch);
    
    m_background = Sprite::create("background.jpg");
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
