//
//  SceneCenter.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/12/16.
//
//

#ifndef SceneCenter_hpp
#define SceneCenter_hpp

#include "DemoPhomBigWin.hpp"
#include "DemoAnimatedCoin.hpp"
#include "DemoAnimatedCursor.hpp"
#include "ResourceUpdateManagerScene.hpp"
#include "DemoDialogScene.hpp"
#include "StopActionByTag.hpp"
#include "MaterialTest.hpp"
#include "TaiXiuScene.hpp"
#include "ui/CocosGUI.h"

#include <stdio.h>

using namespace cocos2d;
using namespace cocos2d::ui;

class SceneCenter : public Layer{
public:
    static Scene* createScene();
    ListView* listItem;
    
    Node* root;
    Node* layerBack;
    
    Button* _backButton;
    Vector<Scene*> vecScene;
    
    CheckBox* _checkCursor;
    virtual bool init();
    
    void addLabelItem(std::string _s);
    
    void callBackItemClicked(Ref* pSender, ui::ListView::EventType _type);
    void callBackButton(Ref* pSender,Widget::TouchEventType _type);
    void checkCallBack(Ref* pSender, CheckBox::EventType _type);

    CREATE_FUNC(SceneCenter);
};

#endif /* SceneCenter_hpp */
