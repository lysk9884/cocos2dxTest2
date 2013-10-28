//
//  GameScene.cpp
//  cocos2dxTest2
//
//  Created by Ilseob lee on 28/10/13.
//
//

#include "GameScene.h"





//using namespace cocos2d
USING_NS_CC;

CCScene *GameScene::scene()
{
    CCScene *scene = CCScene::create();
    
    GameScene *layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool GameScene::init()
{
    if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)) )
    {
        // if it fails to init returns false
        return false;
    }
    //set touch input enabled
    this->setTouchEnabled(true);

    // add player sprite on screen
    this->setPlayerSprite();
    
    
    
    // create game logic
    this->schedule(schedule_selector(GameScene::gameLogic) , 1.0);
    
    return true;
}

void GameScene::setPlayerSprite()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //create player sprite
    CCSprite *player = CCSprite::create("player.png", CCRectMake(0,0, 27, 40));
    
    //set player position
    player->setPosition( ccp(player->getContentSize().width/2, winSize.height/2));
    
    this->addChild(player);
}
void GameScene::addTaraget()
{
    //create target sprite
    CCSprite *target = CCSprite::create("monster.png", CCRectMake(0,0, 27, 40));
    
    
    //place target sprite on random coordination of y axis
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minY = target->getContentSize().height/2;
    int maxY = winSize.height - target->getContentSize().height/2;
    int rangeY = maxY - minY;
    int actualY = ( rand() % rangeY ) + minY;
    target->setPosition(ccp(winSize.width + (target->getContentSize().width / 2),actualY));
    
    this->addChild(target);
    
    // set random movement speed
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand() % rangeDuration) + minDuration;
    
    //make move action
    CCFiniteTimeAction *actionMove = CCMoveTo::create((float)actualDuration, ccp(0-target->getContentSize().width/2 , actualY));
    CCFiniteTimeAction *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameScene::spriteMoveFinished));
    target->runAction(CCSequence::create(actionMove , actionMoveDone , NULL));
}
void GameScene::spriteMoveFinished(CCNode *node)
{
    this->removeChild(node, true);
}
// handles game logic
void GameScene::gameLogic(float dt)
{
    // add targets to the scene
    this->addTaraget();
}
// handles touch event

void GameScene::ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent)
{
    CCTouch *pTouch = (CCTouch*)(pTouches->anyObject());
    CCPoint location = pTouch->getLocationInView();
    
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    this->addProjectileWithTouchLocation(location);
}

//add projectile

void GameScene::addProjectileWithTouchLocation(cocos2d::CCPoint location)
{
    //set projectile init position
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *projectile = CCSprite::create("projectile.png", CCRectMake(0,0, 20,20));
    
    projectile->setPosition(ccp(20, winSize.height/2));
    
    // calculate distance between touch position and projectile position
    int offX = location.x - projectile->getPosition().x;
    int offY = location.y - projectile->getPosition().y;
    
    //ignore projectile behind player
    if(offX <=0)
    {
        return;
    }
    //add projectile to scene
    this->addChild(projectile);
    
    
    
    int realX = winSize.width + (projectile->getContentSize().width/2);
    float ratio = (float)offY / (float)offX;
    int realY = (realX * ratio) + projectile->getPosition().y;
    CCPoint realDest = CCPoint(realX, realY);
    
    
    int offRealX = realX - projectile->getPosition().x;
    int offRealY = realY - projectile->getPosition().y;
    float length = sqrtf((offRealX*offRealX)+(offRealY*offRealY));
    float velocity = 480/1.0f;
    float realMoveDuration = length/velocity;
    
    CCFiniteTimeAction *actionMove = CCMoveTo::create(realMoveDuration, realDest);
    CCFiniteTimeAction *actionFinished = CCCallFuncN::create(this , callfuncN_selector(GameScene::projectileMovedFinished));
    
    CCFiniteTimeAction *actions = CCSequence::create(actionMove,actionFinished,NULL);
    
    projectile->runAction(actions);
    
}

void GameScene::projectileMovedFinished(CCNode *node)
{
    node->removeFromParent();
}