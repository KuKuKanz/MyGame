//
//  DemoPhomBigWin.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/5/16.
//
//

#ifndef DemoPhomBigWin_hpp
#define DemoPhomBigWin_hpp

#include "cocos2d.h"
#include "DemoAnimatedCoin.hpp"
#include "ui/CocosGUI.h"
#include "AnimatedCursor.hpp"
#include <SimpleAudioEngine.h>
#include <stdio.h>


using namespace cocos2d;
using namespace cocos2d::ui;

class PhomBigWinScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
    
    Node* testNode;
    
    void DialogTouch(cocos2d::Ref *pSender, Widget::TouchEventType _type);
    
    Node* CreatePhomBigWinEffect();
    
    void testCallBack();
    void onExit();
    
    CREATE_FUNC(PhomBigWinScene);
};

#endif /* DemoPhomBigWin_hpp */
