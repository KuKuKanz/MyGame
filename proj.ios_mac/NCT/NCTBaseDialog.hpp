//
//  NCTBaseDialog.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/23/16.
//
//

#ifndef NCTBaseDialog_hpp
#define NCTBaseDialog_hpp

#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ResourceNew.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;
using namespace cocos2d::ui;


class BaseDialog : public Layer{

public:
    
    Layout* backGround;
    
    static void loadResource();
    
    static BaseDialog* createBaseDialogWithTitle(std::string _title);
    
    bool initBaseDialog(std::string _title);

};

#endif /* NCTBaseDialog_hpp */
