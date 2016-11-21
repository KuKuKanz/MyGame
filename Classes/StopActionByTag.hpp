//
//  StopActionByTag.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/6/16.
//
//

#ifndef StopActionByTag_hpp
#define StopActionByTag_hpp
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <network/CCDownloader.h>
#include "LayourEffect.hpp"
#include "AnimatedCursor.hpp"
#include "SpriteEffect.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace network;

class Demo : public cocos2d::Layer
{
public:
    ParticleSystemQuad* effect;
    ImageView* imgVongChungBai;
    Label* lblVongChungBai;
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void downloadCalback(const cocos2d::network::DownloadTask& task,
                         std::vector<unsigned char>& data);
    void processCallback(const DownloadTask& task,
                         int64_t bytesReceived,
                         int64_t totalBytesReceived,
                         int64_t totalBytesExpected);
    
    void createTimeLine();
    void changeColor(float dt);
    void createLabelVongChungBai();
    
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void addEffect(float dt);
    void callBack();
    
    void createCard();
    void createHolylight(Vec2 _pos);

    
    Sprite* getCard();
    
    void callBackCreateCard();
    

    void onExit();
    CREATE_FUNC(Demo);
};



#endif /* StopActionByTag_hpp */
