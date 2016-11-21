//
//  DownloaderScene.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/6/16.
//
//

#ifndef DownloaderScene_hpp
#define DownloaderScene_hpp

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <network/CCDownloader.h>
#include <extensions/assets-manager/AssetsManagerEx.h>
#include <extensions/assets-manager/CCEventListenerAssetsManagerEx.h>

using namespace cocos2d;
using namespace network;
using namespace ui;
using namespace extension;

class DownloaderScene : public cocos2d::Layer
{
public:
    ListView* listView;
    LoadingBar* bar;
    Text* label;
    AssetsManagerEx* assMag;
    EventListenerAssetsManagerEx* assMag_listener;
    
    static cocos2d::Scene* createScene();
    virtual bool init();

    void downloadCalback(const cocos2d::network::DownloadTask& task,
                         std::vector<unsigned char>& data);
    
    void processCallback(const DownloadTask& task,
                         int64_t bytesReceived,
                         int64_t totalBytesReceived,
                         int64_t totalBytesExpected);
    
    void downloadFail(const DownloadTask& task,
                      int errorCode,
                      int errorCodeInternal,
                      const std::string& errorStr);
    
    void downloadFileCallBack(const DownloadTask& task);
    
    CREATE_FUNC(DownloaderScene);
};

#endif /* DownloaderScene_hpp */
