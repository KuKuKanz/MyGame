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
static const char* KAME_HEAD = "Kame/kame_Head2.plist";
static const char* KAME_OP_HEAD = "Kame/kame_OpHead.plist";


static const char* KAME_SOUND = "Kame/kame.mp3";

static float _SCALE = 0.4;

bool Kamehameha::init(){
    
    if (!Node::init()){
        return false;
    }
    
    _scale = 0.1;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(KAME_SOUND,false);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(KAME_SOUND,false);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(KAME_SOUND,false);

    _coverEnergy = ParticleSystemQuad::create(KAME_COVER);
    _coverEnergy->setPosition(0,0);
    _coverEnergy->setScale(_scale);
    
    
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
    
    if (timeElapse >= 0.2){
        _coverEnergy = ParticleSystemQuad::create(KAME_COVER);
        _coverEnergy->setPosition(0,0);
        _coverEnergy->setScale(_scale);
        this->addChild(_coverEnergy);

        vecPar.pushBack(_coverEnergy);
        
        _scale+= 0.04;
        timeElapse = 0;
    }
    
    totalDuration+= dt;
    log("%2.f",totalDuration);
}


void Kamehameha::callBackFinalCast(float dt){
    _head = ParticleSystemQuad::create(KAME_HEAD);
    _head->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _head->setPosition(0,0);
    _head->setScale(1.3);
    this->addChild(_head);
    
    auto _callBackHeadStop = CallFuncN::create(CC_CALLBACK_0(Kamehameha::callBackHeadStop, this));
    
    _head->runAction(Sequence::create(MoveBy::create(1., Vec2(0,1000)),_callBackHeadStop,NULL));
    
    {
        _OpHead = ParticleSystemQuad::create(KAME_OP_HEAD);
        _OpHead->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _OpHead->setPosition(0,0);
        this->addChild(_OpHead);

       // _OpHead->runAction(MoveBy::create(3, Vec2(0,)));
    }
    _finalCast = ParticleSystemQuad::create(KAME_CAST);
    _finalCast->setEmissionRate(1000);
    _finalCast->setPosition(0,0);
    _finalCast->setScale(_SCALE);
    //_finalCast->setRotation(90);
    this->addChild(_finalCast);
    
    this->scheduleOnce(schedule_selector(Kamehameha::callBackStop), 1.5);
    
    this->unscheduleUpdate();
}

void Kamehameha::callBackStop(float dt){
    _finalCast->stopSystem();
    
    
    _OpHead->runAction(Sequence::create(MoveBy::create(1.5, Vec2(0,1000)),RemoveSelf::create(),NULL));

    
    this->runAction(Sequence::create(DelayTime::create(5),RemoveSelf::create(), NULL));

    
}

void Kamehameha::callBackHeadStop(){
    _head->stopSystem();
    //_OpHead->stopSystem();

    for(auto _par : vecPar){
        _par->stopSystem();
    }
    
    this->unscheduleUpdate();

}
