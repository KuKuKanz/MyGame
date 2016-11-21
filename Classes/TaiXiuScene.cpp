//
//  TaiXiuScene.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/31/16.
//
//

#include "TaiXiuScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ResourceNew.h"

Scene* TaiXiuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = TaiXiuScene::create();
    
    // add layer as a child to scene
    
    scene->addChild(layer);
    // return the scene
    return scene;
}

static bool _first = false;

bool TaiXiuScene::init(){
    
    if (!Layer::init()){
        return false;
    }
    
    //auto board = TaiXiuBoard::create();
    
    //this->addChild(board);
    
//    _spr = Sprite::createWithSpriteFrameName(srcPNG_tx_Tai);
//    _spr->setPosition(0,0);
//    _spr->runAction(MoveTo::create(15, Vec2(960,640)));
//    this->addChild(_spr);
    auto _listener = EventListenerTouchOneByOne::create();
    
    _listener->onTouchBegan = CC_CALLBACK_2(TaiXiuScene::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(TaiXiuScene::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(TaiXiuScene::onTouchEnded, this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
    
    this->addChild(AnimatedCursor::getInstance(),9999);
    
    return true;
}

//
void TaiXiuScene::onEnterTransitionDidFinish(){
    Node::onEnterTransitionDidFinish();
    
//    if (Director::getInstance()->getRunningScene()->getChildByTag<TaiXiuDialog*>(1) == NULL){
//        Director::getInstance()->getRunningScene()->addChild(TaiXiuDialog::getInstance());
//        TaiXiuDialog::getInstance()->resetTimer();
//    }
//    //TaiXiuDialog::getInstance()->resume();
//    if (!_first){
//        //TaiXiuDialog::getInstance()->startTimer(0);
//               _first = true;
//    }
}
//
//void TaiXiuScene::onExitTransitionDidStart(){
//    Node::onExitTransitionDidStart();
//    
//    TaiXiuDialog::getInstance()->pause();
//}

bool TaiXiuScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    //_spr->pause();
    return true;
}

void TaiXiuScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void TaiXiuScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
//    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/baucua/diceroll.mp3");
//    
//    auto _res1 = random(1, 6);
//    auto _res2 = random(1, 6);
//    auto _res3 = random(1, 6);
//    
//    //    _res1 = random(1, 1);
//    //    _res2 = random(1, 1);
//    //    _res3 = random(1, 1);
//    
//    //_containerXiNgau = XiNgauController::create3XiNgau(_res1,_res2,_res3,CC_CALLBACK_0(TaiXiuDialog::testCallBackResult, this));
//    auto _containerXiNgau = XiNgauController::create3XiNgau(2,_res1,_res2,_res3,NULL);
//    
//    _containerXiNgau->setScale(0.75);
//    this->addChild(_containerXiNgau);
//    _containerXiNgau->setPosition(touch->getLocation());
//    
//    
//    _containerXiNgau->runAction(Sequence::create(DelayTime::create(6),RemoveSelf::create(), NULL));
    
    
    auto _spell = Kamehameha::create();
    _spell->setPosition(touch->getLocation());
    this->addChild(_spell);
    
    

}
