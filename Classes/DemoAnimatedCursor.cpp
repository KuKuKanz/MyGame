//
//  DemoAnimatedCursor.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/12/16.
//
//

#include "DemoAnimatedCursor.hpp"
#include "cocostudio/CocoStudio.h"
#include "ResourceNew.h"
Scene* DemoAnimatedCursor::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DemoAnimatedCursor::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    
    // return the scene
    return scene;
}



bool DemoAnimatedCursor::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_dialog);
    
    AnimatedCursor::getInstance()->setVisible(true);
    this->addChild(AnimatedCursor::getInstance());
    this->addChild(CursorController::getInstance());
    
    return true;
}
