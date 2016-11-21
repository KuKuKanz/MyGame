//
//  Clock.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/8/16.
//
//

#include "Clock.hpp"

static Clock* _clock = NULL;

Clock* Clock::getInstance(){
    if (_clock == NULL){
        _clock = Clock::create();
        _clock->retain();
    }
    
    return _clock;
}

bool Clock::init(){
    Director::getInstance()->getScheduler()->schedule(schedule_selector(Clock::update),this,0,false);
    
    return true;
}

static float _timeElapse = 0;

void Clock::update(float dt){
    _timeElapse+= dt;
    if (TaiXiuDialog::getInstance()!= NULL && _timeElapse>=1){
        TaiXiuDialog::getInstance()->clock(1);
        _timeElapse = 0;
    }
    
    if (TaiXiuDialog::getInstance()!= NULL){
        TaiXiuDialog::getInstance()->miliClock(dt);
    }
    
    if (AnimatedCursor::getInstance() != NULL){
        AnimatedCursor::getInstance()->clock(dt);
    }
}
