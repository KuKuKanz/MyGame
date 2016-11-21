//
//  DemoDialogScene.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/13/16.
//
//

#ifndef DemoDialogScene_hpp
#define DemoDialogScene_hpp

#include "ui/CocosGUI.h"
#include <stdio.h>
#include "NCTBaseDialog.hpp"
#include "CustomDialog.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;


class DemoDialogScene : public Layer{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    void callBack(Ref* pSender, Widget::TouchEventType _type);
    void callBackBaseDialog(Ref* pSender,Widget::TouchEventType _type);
    
    BaseDialog* baseDig;
    
    BaseDialog* createBaseDialog();
    
    void onExit();
    CREATE_FUNC(DemoDialogScene);
};
#endif /* DemoDialogScene_hpp */
