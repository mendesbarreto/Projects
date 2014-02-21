#define PLAYER_ACCELERATION 0.5;

#include "Player.h"

void Player::setFloating (bool value) {}void Player::initPlayer () {}

Player * Player::create () {	Player * player = new Player();	if (player && player->initWithFile("blank.png")) {		player->autorelease();		player->setSize();		player->initPlayer();		return player;	}		CC_SAFE_DELETE(player);	return NULL;}void Player::update (float dt) {}void Player::reset () {	m_speed = PLAYER_INITIAL_SPEED;	m_maxSpeed = PLAYER_INITIAL_SPEED;	m_vector = ccp(0,0);	this->setFloating(false);	this->setRotation(0);	m_nextPosition.y = m_screenSize.height * 0.6f;	this->setPosition(ccp( m_screenSize.width * 0.2f, m_nextPosition.y ));	m_state = kPlayerMoving;	m_jumping = false;	m_hasFloated = false;}