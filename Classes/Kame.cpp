//
//  Kame.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/21/16.
//
//

#include "Kame.hpp"

static const char* KAME_COVER = "Kame/effect_kameCoverEnergy.plist";
static const char* KAME_CAST = "Kame/effect_kame2.plist";
static const char* KAME_SOUND = "Kame/kame.mp3";


bool Kamehameha::init(){
    
    if (!Node::init()){
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(KAME_SOUND,false);
    
    _coverEnergy = ParticleSystemQuad::create(KAME_COVER);
    _coverEnergy->setPosition(0,0);
    _coverEnergy->setScale(0.5);
    
    this->addChild(_coverEnergy);
    
    this->scheduleUpdate();
    this->scheduleOnce(schedule_selector(Kamehameha::callBackFinalCast), 6);
    
    vecPar.pushBack(_coverEnergy);

    return true;
}

static float totalDuration = 0;
static float timeElapse = 0;
void Kamehameha::update(float dt){
    timeElapse+= dt;
    
    if (timeElapse >= 0.5){
        _coverEnergy = ParticleSystemQuad::create(KAME_COVER);
        _coverEnergy->setPosition(0,0);
        _coverEnergy->setScale(0.5);
        this->addChild(_coverEnergy);

        vecPar.pushBack(_coverEnergy);

        timeElapse = 0;
    }
    
    totalDuration+= dt;
    log("%2.f",totalDuration);
}


void Kamehameha::callBackFinalCast(float dt){
   
    
    _finalCast = ParticleSystemQuad::create(KAME_CAST);
    _finalCast->setEmissionRate(1000);
    _finalCast->setPosition(0,0);
    _finalCast->setScale(0.7);
    _finalCast->setRotation(90);
    this->addChild(_finalCast);
    
    this->scheduleOnce(schedule_selector(Kamehameha::callBackStop), 2);
    
    //this->unscheduleUpdate();
}

void Kamehameha::callBackStop(float dt){
    _finalCast->stopSystem();
    for(auto _par : vecPar){
        _par->stopSystem();
    }
    
    this->runAction(Sequence::create(DelayTime::create(2),RemoveSelf::create(), NULL));
    this->unscheduleUpdate();

    
}
