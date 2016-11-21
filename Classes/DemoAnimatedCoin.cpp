//
//  DemoAnimatedCoin.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/5/16.
//
//

#include "DemoAnimatedCoin.hpp"
#include "ResourceNew.h"
#include "cocostudio/CocoStudio.h"

Scene* CoinScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CoinScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CoinScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_dialog);
    
    
    
    wave1 = AnimatedCoinWave::createAnimatedCoinWave(10,Vec2(480,25),Vec2(480,600));
    wave1->SetCoinType(CoinType::BRONZE);
    wave1->addCoinCallBack(CC_CALLBACK_0(CoinScene::CoinCallBack, this));
    
    wave2 = AnimatedCoinWave::createAnimatedCoinWave(10,Vec2(25,320),Vec2(480,600));
    wave2->SetCoinType(CoinType::GOLD);
    wave2->addCoinCallBack(CC_CALLBACK_0(CoinScene::CoinCallBack, this));
    
    wave3 = AnimatedCoinWave::createAnimatedCoinWave(10,Vec2(935,320),Vec2(480,600));
    wave3->SetCoinType(CoinType::SILVER);
    wave3->addCoinCallBack(CC_CALLBACK_0(CoinScene::CoinCallBack, this));
    
    wave1->setScale(0.5);
    wave1->setDuration(1.5);
    wave1->start();
    
    wave2->setScale(0.2);
    wave2->setDuration(2);
    wave2->start();
    
    wave3->setScale(1);
    wave3->setDuration(0.2);
    wave3->start();
    
    auto root = CSLoader::createNode("TempResource/Scene/AnimatedCoin.csb");
    auto _button = root->getChildByName<Button*>("butReset");
    _button->addTouchEventListener(CC_CALLBACK_2(CoinScene::DialogTouch, this));
    
    this->addChild(root);
    
    
    this->addChild(wave1);
    this->addChild(wave2);
    this->addChild(wave3);
    
    this->addChild(AnimatedCursor::getInstance(),9999);

    
    return true;
}


static int i = 0;
void CoinScene::CoinCallBack(){
    
}

void CoinScene::cursorCallback(){
    wave1->start();
    wave2->start();
    wave3->start();
}

void CoinScene::DialogTouch(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    
    auto button = static_cast<Button*>(pSender);
    
    switch (_type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            if (button->getName() == "butReset"){
                wave1->start();
                wave2->start();
                wave3->start();
            }
            
        default:
            break;
    }
}

void CoinScene::onExit(){
    Node::onExit();
    wave1->clear();
    wave2->clear();
    wave3->clear();
    this->removeAllChildren();
    this->removeFromParent();
}
