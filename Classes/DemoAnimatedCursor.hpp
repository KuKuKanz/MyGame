//
//  DemoAnimatedCursor.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/12/16.
//
//

#ifndef DemoAnimatedCursor_hpp
#define DemoAnimatedCursor_hpp
#include "CursorController.hpp"
#include "ui/CocosGUI.h"
#include <stdio.h>


using namespace cocos2d;
using namespace cocos2d::ui;

class DemoAnimatedCursor : public Layer{
public:
    static Scene* createScene();
    
    CheckBox* checkAuto;
    
    virtual bool init();
    
    void checkBoxCallback(Ref* pSender, CheckBox::EventType _type);
    
    CREATE_FUNC(DemoAnimatedCursor);
    
};
#endif /* DemoAnimatedCursor_hpp */
