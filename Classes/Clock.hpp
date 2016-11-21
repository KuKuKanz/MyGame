//
//  Clock.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/8/16.
//
//

#ifndef Clock_hpp
#define Clock_hpp
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "TaiXiuDialog.hpp"
#include <stdio.h>

using namespace cocos2d;
using namespace cocos2d::ui;



class Clock : public Ref{
public:
    void update(float dt);
    
    static Clock* getInstance();
    virtual bool init();
    
    CREATE_FUNC(Clock);
    
};

#endif /* Clock_hpp */
