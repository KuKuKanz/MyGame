//
//  DownloaderScene.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/6/16.
//
//

#include "DownloaderScene.hpp"


Scene* DownloaderScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DownloaderScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool DownloaderScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
  
    
    
    auto root = CSLoader::createNode("DownloaderScene.csb");
    listView = root->getChildByName<ListView*>("imageList");
    label = root->getChildByName<Text*>("label_speed");
    bar = root->getChildByName<LoadingBar*>("bar_speed");
    bar->setVisible(true);
    
    
    
    

    Downloader* _downloader = new Downloader();
    
    auto path = FileUtils::getInstance()->getWritablePath() + "monster.plist";
    _downloader->createDownloadFileTask("http://localhost/Tung/project_dev.manifest",path);
    
    _downloader->onDataTaskSuccess = CC_CALLBACK_2(DownloaderScene::downloadCalback, this);
    _downloader->onTaskProgress = CC_CALLBACK_4(DownloaderScene::processCallback, this);
    _downloader->onTaskError = CC_CALLBACK_4(DownloaderScene::downloadFail, this);
    _downloader->onFileTaskSuccess = CC_CALLBACK_1(DownloaderScene::downloadFileCallBack, this);
    this->addChild(root);

    return true;
}


void DownloaderScene::processCallback(const cocos2d::network::DownloadTask &task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected){
    
    label->setString(StringUtils::format("Speed: %zd kb/s",bytesReceived/1024));
    bar->setPercent((totalBytesReceived/totalBytesExpected)*100);
    CCLOG("BytesRecieved: %zd",bytesReceived);
    CCLOG("BytesTotalRecieved: %zd",totalBytesReceived);
    CCLOG("TotalBytesExpected: %zd",totalBytesExpected);
}

void DownloaderScene::downloadFileCallBack(const cocos2d::network::DownloadTask &task){
    label->setString(task.storagePath);
}

void DownloaderScene::downloadCalback(const cocos2d::network::DownloadTask &task, std::vector<unsigned char> &data){
    Texture2D* texture = nullptr;
    
    do
    {
        Image img;
        if (!img.initWithImageData(data.data(), data.size()))
        {
            break;
        }
        
        texture = new Texture2D();
        if (!texture->initWithImage(&img))
        {
            break;
        }
        
        auto _layout = Layout::create();
        auto sprite = Sprite::createWithTexture(texture);
        
        _layout->setContentSize(Size(listView->getContentSize().width,300));
        sprite->setPosition(_layout->getContentSize()/2);
        _layout->addChild(sprite);
        listView->addChild(_layout);
        
        label->setString(task.storagePath);
    
    } while (0);
    CC_SAFE_RELEASE(texture);
}

void DownloaderScene::downloadFail(const cocos2d::network::DownloadTask &task, int errorCode, int errorCodeInternal, const std::string &errorStr){
    
    label->setString(errorStr);
}
