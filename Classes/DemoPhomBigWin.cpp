//
//  DemoPhomBigWin.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/5/16.
//
//

#include "DemoPhomBigWin.hpp"
#include "ResourceNew.h"
#include "cocostudio/CocoStudio.h"

Scene* PhomBigWinScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PhomBigWinScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    
    // return the scene
    return scene;
}


Node* PhomBigWinScene::CreatePhomBigWinEffect(){
    Node* _node = Node::create();
    
    auto effect = ParticleSystemQuad::create("phomwinbig.plist");
    
    effect->setSpeed(500);
    effect->setTotalParticles(300);
    effect->setDuration(0.5);
    effect->setPosition(_node->getContentSize()/2);
    effect->setAutoRemoveOnFinish(true);
    effect->resetSystem();
    
    auto lightEffect = ParticleSystemQuad::create("phomwin_effect.plist");
    lightEffect->setPosition(_node->getContentSize()/2);
    lightEffect->setAutoRemoveOnFinish(true);
    lightEffect->resetSystem();
    
    _node->addChild(effect,1);
    _node->addChild(lightEffect,0);
    
    return _node;
}

// on "init" you need to initialize your instance
bool PhomBigWinScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto root = CSLoader::createNode("TempResource/Scene/PhomBigWinScene.csb");
    auto _button = root->getChildByName<Button*>("butReset");
    
    _button->addTouchEventListener(CC_CALLBACK_2(PhomBigWinScene::DialogTouch, this));
    
    this->addChild(_button);
    
    
    testNode = CreatePhomBigWinEffect();
    testNode->setPosition(Vec2(480,320));
    this->addChild(testNode);
    this->addChild(root);
    this->addChild(AnimatedCursor::getInstance(),9999);

    return true;
}

void PhomBigWinScene::testCallBack(){
    testNode = CreatePhomBigWinEffect();
    testNode->setPosition(Vec2(480,320));
    this->addChild(testNode);
}

void PhomBigWinScene::DialogTouch(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    
    auto button = static_cast<Button*>(pSender);
    
    switch (_type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            if (button->getName() == "butReset"){
                testNode = CreatePhomBigWinEffect();
                testNode->setPosition(Vec2(480,320));
                this->addChild(testNode);
                break;
            }

        default:
            break;
    }
}


void PhomBigWinScene::onExit(){
    Node::onExit();
    testNode->removeAllChildren();
    testNode->removeFromParent();
    this->removeAllChildren();
    this->removeFromParent();
    
}
