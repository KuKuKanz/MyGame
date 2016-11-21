//
//  ResourceUpdateManagerScene.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#include "ResourceUpdateManagerScene.hpp"
#include "ResourceNew.h"

Scene* ResourceUpdateManagerScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResourceUpdateManagerScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool ResourceUpdateManagerScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_dialog);
    
    auto root = CSLoader::createNode("TempResource/Scene/DownloadMagScene.csb");
    listView = root->getChildByName<ListView*>("imageList");
    lblSpeed = root->getChildByName<Text*>("label_speed");
    lblVersion = root->getChildByName<Text*>("lblVersion");
    bar = root->getChildByName<LoadingBar*>("bar_speed");
    bar->setVisible(true);
    
    auto _but = root->getChildByName<Button*>("butReset");
    _but->addTouchEventListener(CC_CALLBACK_2(ResourceUpdateManagerScene::resetCallback, this));
    this->addChild(root);
    
    
    

    
    assMag = ResourceUpdateManager::createResourceUpdateManager("project.manifest", "MyGame");
    assMag->retain();
    assMag->onFinish = CC_CALLBACK_0(ResourceUpdateManagerScene::onFinish, this);
    assMag->onProgressing = CC_CALLBACK_2(ResourceUpdateManagerScene::onProgressing, this);
    assMag->onFailed = CC_CALLBACK_1(ResourceUpdateManagerScene::onFailed, this);
    
    lblVersion->setString(assMag->getCurrentVersion());
    assMag->startUpdateResource();
    return true;
}

void ResourceUpdateManagerScene::addString(std::string s){
    auto _layout = Layout::create();
    _layout->setContentSize(Size(listView->getContentSize().width,50));
    
    auto _text = Label::createWithTTF(s, srcTFF_Roboto_Bold, 20);
    _text->setMaxLineWidth(500);
    _text->setPosition(_layout->getContentSize()/2);
    _layout->addChild(_text);
    listView->pushBackCustomItem(_layout);
    listView->jumpToBottom();
    
}

void ResourceUpdateManagerScene::resetCallback(cocos2d::Ref *pSender, Widget::TouchEventType type){
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:{
            bar->setPercent(0);
            lblSpeed->setString("Loading: ");
            listView->removeAllItems();
            assMag->resetUpdateReousrce();
            break;
        }
            
        default:
            break;
    }
}



void ResourceUpdateManagerScene::onFinish(){
    addString("Update Finish: " + assMag->getCurrentVersion());
    lblVersion->setString(assMag->getCurrentVersion());
}

void ResourceUpdateManagerScene::onProgressing(std::string meg,float percent){
    bar->setPercent(percent);
    lblSpeed->setString(StringUtils::format("Loading: %.2f",percent) + "%");
    addString(meg);
}

void ResourceUpdateManagerScene::onFailed(std::string message){
    addString(message);
}
