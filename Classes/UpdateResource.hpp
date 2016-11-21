//
//  UpdateResource.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#ifndef UpdateResource_hpp
#define UpdateResource_hpp

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <network/CCDownloader.h>
#include <extensions/assets-manager/AssetsManagerEx.h>
#include <extensions/assets-manager/CCEventListenerAssetsManagerEx.h>

using namespace cocos2d;
using namespace network;
using namespace ui;
using namespace extension;

class UpdateResourceScene : public cocos2d::Layer
{
public:
    ListView* listView;
    LoadingBar* bar;
    Text* lblSpeed, *lblVersion;
    AssetsManagerEx* assMag;
    EventListenerAssetsManagerEx* assMag_listener;
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void downloadFileCallBack(const DownloadTask& task);
    
    void startDownload();
    void callBack(EventAssetsManagerEx* event);
    void addString(std::string s);
    void resetCallback(Ref* pSender, Widget::TouchEventType type);
    
    
    CREATE_FUNC(UpdateResourceScene);
};


#endif /* UpdateResource_hpp */
