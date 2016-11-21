//
//  CursorController.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/12/16.
//
//

#ifndef CursorController_hpp
#define CursorController_hpp

#include "AnimatedCursor.hpp"
#include "ui/CocosGUI.h"
#include <stdio.h>

class CursorController : public Layer{
public:
    
    static CursorController* getInstance();
    
    CheckBox* checkAuto;
    Slider* speedSlide,*sleepSlide;
    Text* lblSpeed,*lblSleep;
    
    float curSpeed,curSleep;
    
    virtual bool init();
    
    void checkBoxCallback(Ref* pSender, CheckBox::EventType _type);
    void slideCallback(Ref* pSender, Slider::EventType _type);
    
    void onExit();
    
    CREATE_FUNC(CursorController);
    
};
#endif /* CursorController_hpp */
