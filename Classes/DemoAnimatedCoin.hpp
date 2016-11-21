//
//  DemoAnimatedCoin.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/5/16.
//
//

#ifndef DemoAnimatedCoin_hpp
#define DemoAnimatedCoin_hpp

#include "cocos2d.h"
#include "AnimatedCoin.hpp"
#include <SimpleAudioEngine.h>
#include "ui/CocosGUI.h"
#include "AnimatedCursor.hpp"
#include "DemoPhomBigWin.hpp"



using namespace cocos2d;
using namespace cocos2d::ui;

class CoinScene : public cocos2d::Layer
{
public:

    AnimatedCoinWave* wave1,*wave2,*wave3;
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    
    void createCustomDialog();
    void createBaseDialog();
    void DialogTouch(cocos2d::Ref *pSender, Widget::TouchEventType _type);
    
    void CoinCallBack();
    
    void cursorCallback();
    void onExit();
    
    CREATE_FUNC(CoinScene);
};



#endif /* DemoAnimatedCoin_hpp */
