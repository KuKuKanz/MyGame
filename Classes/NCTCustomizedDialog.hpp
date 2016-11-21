//
//  NCTCustomizedDialog.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/27/16.
//
//

#ifndef NCTCustomizedDialog_hpp
#define NCTCustomizedDialog_hpp

#include "NCTBaseDialog.hpp"
#include "ui/CocosGUI.h"
#include <stdio.h>

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;

class CustomizedDialog : public BaseDialog{
protected:
    bool initCustomizedDialog(std::string title, DialogFont _font,float width,float height);
    
    
};

#endif /* NCTCustomizedDialog_hpp */
