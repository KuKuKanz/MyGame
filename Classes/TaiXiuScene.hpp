//
//  TaiXiuScene.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/31/16.
//
//

#ifndef TaiXiuScene_hpp
#define TaiXiuScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "TaiXiuDialog.hpp"
#include "TaiXiuBoard.hpp"
#include "XiNgau.hpp"
#include "Kame.hpp"
#include <stdio.h>


using namespace cocos2d;
using namespace cocos2d::ui;

class TaiXiuScene: public cocos2d::Layer
{
public:
    
    Sprite* _spr;
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void onEnterTransitionDidFinish();
//    void onExitTransitionDidStart();
    CREATE_FUNC(TaiXiuScene);
};

#endif /* TaiXiuScene_hpp */
