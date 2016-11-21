//
//  UpdateResource.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#include "UpdateResource.hpp"
#include "ResourceNew.h"

static const char* storedPath = "MyGame";

Scene* UpdateResourceScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = UpdateResourceScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool UpdateResourceScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_dialog);

    auto root = CSLoader::createNode("DownloaderScene.csb");
    listView = root->getChildByName<ListView*>("imageList");
    lblSpeed = root->getChildByName<Text*>("label_speed");
    lblVersion = root->getChildByName<Text*>("lblVersion");
    bar = root->getChildByName<LoadingBar*>("bar_speed");
    bar->setVisible(true);
    
    auto _but = root->getChildByName<Button*>("butReset");
    _but->loadTextureNormal(srcPNG_dialog_button_ok,Widget::TextureResType::PLIST);
    _but->loadTexturePressed(srcPNG_dialog_button_ok_tap,Widget::TextureResType::PLIST);
    _but->loadTexturePressed(srcPNG_dialog_button_ok_disable,Widget::TextureResType::PLIST);
    _but->addTouchEventListener(CC_CALLBACK_2(UpdateResourceScene::resetCallback, this));
    
    assMag = AssetsManagerEx::create("project.manifest", FileUtils::getInstance()->getWritablePath() + storedPath);
    assMag->retain();
    
    
    
    if (assMag->getLocalManifest()->isVersionLoaded()){
        CCLOG("Version loaded");
        lblVersion->setString(StringUtils::format("Version loaded: %s",assMag->getLocalManifest()->getVersion().c_str()));
    }else{
        CCLOG("Version load failed");
    }
    
    std::vector<std::string> path = assMag->getLocalManifest()->getSearchPaths();
    
    this->addChild(root);
    
    startDownload();
    return true;
}

void UpdateResourceScene::startDownload(){
    if (!assMag->getLocalManifest()->isLoaded())
    {
        CCLOG("Fail to update assets, step skipped.");
    }
    else
    {
        assMag_listener = EventListenerAssetsManagerEx::create(assMag, CC_CALLBACK_1(UpdateResourceScene::callBack, this));
        getEventDispatcher()->addEventListenerWithFixedPriority(assMag_listener, 1);
        assMag->update();

    }
}

void UpdateResourceScene::addString(std::string s){
    auto _layout = Layout::create();
    _layout->setContentSize(Size(listView->getContentSize().width,50));
    
    auto _text = Text::create(s, srcTFF_Roboto_Bold, 20);
    _text->setPosition(_layout->getContentSize()/2);
    _layout->addChild(_text);
    listView->pushBackCustomItem(_layout);
    listView->jumpToBottom();
    
}

void UpdateResourceScene::resetCallback(cocos2d::Ref *pSender, Widget::TouchEventType type){
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:{
            bar->setPercent(0);
            lblSpeed->setString("Speed");
            assMag->release();
            assMag = AssetsManagerEx::create("project.manifest", FileUtils::getInstance()->getWritablePath() + storedPath);
            assMag->retain();
            getEventDispatcher()->removeEventListener(assMag_listener);
            
            this->startDownload();
            listView->removeAllItems();
            break;
        }
            
        default:
            break;
    }
}


void UpdateResourceScene::callBack(cocos2d::extension::EventAssetsManagerEx *event){
    switch (event->getEventCode()) {
            
        case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
            addString("No local manifest");
            break;
            
        case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
            addString(StringUtils::format("Update progression: %s",event->getAssetId().c_str()));
            bar->setPercent(event->getPercent());
            lblSpeed->setString(StringUtils::format("Loading: %.2f",event->getPercent()) + "%");
            break;
            
        case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
            addString("Already up to date");
            break;
            
        case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
            addString(StringUtils::format("Error updating: %s",event->getMessage().c_str()));
            
            break;
            
        case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
            addString("Error decompress");
            break;
            
        case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
            addString("Asset updated");
            break;
        case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
            addString("Error download ! Check your network !");
            break;
            
        case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
            addString("Error parse manifest");
            break;
            
        case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:{
            addString("New version found");
            lblVersion->setString(StringUtils::format("Version loaded: %s",event->getAssetsManagerEx()->getRemoteManifest()->getVersion().c_str()));
            break;
        }
            
        case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
            addString("Update failed");
            break;
            
        case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:{
            addString("Update finished");
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(StringUtils::format("%s%s",FileUtils::getInstance()->getWritablePath().c_str(),"MyGame/Test4/pelatuk_default.plist"));
            
            
            Sprite* _sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pelatuk1.png"));
            
            this->addChild(_sprite);
            _sprite->setPosition(Vec2(250,350));
            
            break;
        }
            
        default:
            break;
    }
}


