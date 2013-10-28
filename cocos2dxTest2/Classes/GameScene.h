//
//  GameScene.h
//  cocos2dxTest2
//
//  Created by Ilseob lee on 28/10/13.
//
//

#ifndef __cocos2dxTest2__GameScene__
#define __cocos2dxTest2__GameScene__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayerColor
{
    public :
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
     CREATE_FUNC(GameScene);
    
    private :
    
    void setPlayerSprite();
    void addTaraget();
    void spriteMoveFinished(CCNode *node);
    void gameLogic(float dt);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void addProjectileWithTouchLocation(cocos2d::CCPoint location);
    void projectileMovedFinished(cocos2d::CCNode *node);
    
};

#endif /* defined(__cocos2dxTest2__GameScene__) */
