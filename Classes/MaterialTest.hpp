//
//  MaterialTest.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#ifndef MaterialTest_hpp
#define MaterialTest_hpp

#include "ui/CocosGUI.h"
#include <stdio.h>

using namespace cocos2d;
using namespace cocos2d::ui;

class MaterialTest : public Layer{
public:
    
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MaterialTest);
};

#endif /* MaterialTest_hpp */
