//
//  ResourceUpdateManagerScene.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#ifndef ResourceUpdateManagerScene_hpp
#define ResourceUpdateManagerScene_hpp

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ResourceUpdateManager.hpp"


using namespace cocos2d;
using namespace network;
using namespace ui;
using namespace extension;

class ResourceUpdateManagerScene : public cocos2d::Layer
{
public:
    ListView* listView;
    LoadingBar* bar;
    Text* lblSpeed, *lblVersion;
    
    ResourceUpdateManager* assMag;
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void addString(std::string s);
    void resetCallback(Ref* pSender, Widget::TouchEventType type);
    
    
    void onFinish();
    void onProgressing(std::string meg,float percent);
    void onFailed(std::string message);
    
    CREATE_FUNC(ResourceUpdateManagerScene);
};


#endif /* ResourceUpdateManagerScene_hpp */
