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

	srand( time(NULL) );

    this->createScreen();
    this->createPools();
    this->createActions();
	this->createPlayer();


	EventListenerAcceleration* m_aceleration_listener = EventListenerAcceleration::create( CC_CALLBACK_2( GameLayer::onAcelerationHandler, this ) );
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority( m_aceleration_listener , 100 );

	this->schedule( schedule_selector( GameLayer::update ) );

	this->setAccelerometerInterval( 1/60.0f);
	this->setAccelerometerEnabled( true );

    return true;
}

void GameLayer::createPlayer()
{
	m_player = Character::create( "emilia_narizinho1.png" );
	m_player->addAnimation( "walk" , Character::createAnimationWithName("emilia_narizinho" , 20, 60 , true ) );
	m_player->setPosition( ccp( m_player->boundingBox().size.width + 20 , m_player->boundingBox().size.height + 100) );
	m_player->setPosition( ccp( 200 , 200) );
	
	this->addChild( m_player );
}


void GameLayer::update( float dt )
{
	m_goibaGoodTime += dt;

	if( m_goibaGoodTime > m_goibaGoodInterval )
	{
		m_goibaGoodTime = 0;
		
		this->createGoodGoiba();
	}
    
	float limitRight = m_screenSize.width - m_player->boundingBox().size.width * 0.5f;
	float limitLeft = m_player->boundingBox().size.width * 0.5f;

	float posX = m_player->getPositionX() + m_playerSpeed;

	if( posX < limitLeft )
	{
		posX = limitLeft;
		m_playerSpeed = 0;
	}
	else if( posX > limitRight )
	{
		posX = limitRight;
		m_playerSpeed = 0;
	}

	m_player->setPositionX( posX ); 
}


void GameLayer::onAcelerationHandler( Acceleration* ac , Event* event )
{
	float deceleration = 0.1f;
	float sensitivity = 8.0f;
	float maxVelocity = 50;

	//m_playerSpeed =  20 * ( powf ( ( - fabsf( ac->x) + 0.5), 2.0) - 1.25) * ac->y; //(I use sensitivity = 640.0);

	m_playerSpeed = m_playerSpeed * deceleration + ac->x * sensitivity ;
	m_playerSpeed = MAX( MIN( m_playerSpeed , maxVelocity ) , -maxVelocity );

	CCLOG("PlayerSpeed: %f , Accelerometer: %f ", m_playerSpeed , ac->x );
}


bool GameLayer::createPools()
{
    m_goibaGoodPoolIndex = 0;
	m_goibaBadPoolIndex = 0;

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
		
		character->setVisible(false);
		this->addChild(character);

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
		
		character->setVisible(false);
		this->addChild(character);

		m_goibaGoodPool->addObject(character);
	}

	m_goibaGoodPool->retain();

    return true;
}

bool GameLayer::createActions()
{
	m_goibaSpeed = 10.0f;

	m_goibaBadInterval = 5;
	m_goibaBadTime = 0;
 
	m_goibaGoodTime = 0;
	m_goibaGoodInterval = 5;
    
	m_goiba_actions.pushBack( RotateTo::create( 1 , -20 ) );
	m_goiba_actions.pushBack( RotateTo::create( 1 , 20 ) );
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

void GameLayer::createGoodGoiba()
{
	//if( m_goibaGoodPool->count() > 10 ) return;

	int initialPosX = rand() % (int) (m_screenSize.width * 0.8f ) + m_screenSize.width * 0.1f;
	
    if( m_goibaGoodPoolIndex > 19 )
		m_goibaGoodPoolIndex = 0;
    
	Character* c = (Character* ) m_goibaGoodPool->objectAtIndex( m_goibaGoodPoolIndex );
	m_goibaGoodPoolIndex++;
    
	c->stopAllActions();
	c->setPosition( ccp( initialPosX , m_screenSize.height + c->boundingBox().size.height * 0.5f ) );

	Vector<FiniteTimeAction *> actionsRotate;
	actionsRotate.pushBack( RotateTo::create( 1 , -20 ) );
	actionsRotate.pushBack( RotateTo::create( 1 , 20 ) );

	FiniteTimeAction* actionMove = MoveTo::create( (float) m_goibaSpeed , ccp( (float) initialPosX , 0 ) );
	FiniteTimeAction* actionMoveDone = CallFuncN::create( this , callfuncN_selector( GameLayer::goibaGoodFinishFalling ) );
	FiniteTimeAction* seq = Sequence::createWithTwoActions( actionMove , actionMoveDone );

	c->setVisible(true);
	c->gotoAndPlay( "goiba_good_falling" );
	c->play( actionsRotate );
	c->runAction( seq );

	//c->runAction( sequence );

}

void GameLayer::goibaGoodFinishFalling( Node* pSender )
{
	Character* c = (Character* ) pSender;
	
	if( pSender )
	{
		c->stopAllActions();
		c->setVisible(false);
	}

}


