//
//  XiNgau.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/3/16.
//
//

#include "XiNgau.hpp"
#include "ResourceNew.h"
static bool _loadResource = false;
static float TIME_SHOW_RESULT = 1.75;


static SpriteFrameCache* sprCache = NULL;

void XiNgau::loadResource(){
    if (!_loadResource){
        sprCache = SpriteFrameCache::getInstance();
        if (!sprCache->isSpriteFramesWithFileLoaded(srcPLIST_tai_xiu)){
            sprCache->addSpriteFramesWithFile(srcPLIST_tai_xiu);
        }
    }
}

XiNgau* XiNgau::createXiNgauAtPos(Vec2 _pos,int _indexResult,ccResultCallBack _callBackResult){
    auto _xingau = new (std::nothrow) XiNgau();
    
    if (_xingau){
        if (!_xingau->init(_pos,_indexResult,_callBackResult)){
            CC_SAFE_DELETE(_xingau);
        }else{
            _xingau->autorelease();
        }
    }
    return _xingau;
}

static int TIME = -1;
bool XiNgau::init(Vec2 _pos,int _indexResult,ccResultCallBack _callBackResult){
    
    if (!Sprite::init()){
        return false;
    }
    _show = false;
    _speed = 0.01;
    _orginalPos = _pos;
    _duration = 50;
    _time = 0;
    _v = 0;
    
    onResultCallBack = _callBackResult;
    
    switch (TIME) {
        case -1:
            _duration = 15;
            break;
        case 0:
            _duration = 30;
            break;
        case 1:
            _duration = 60;
            break;
            
        default:
            break;
    }
    
    for(int i = 1; i < 7; i++){
        std::string _path = StringUtils::format("tx_xingau_lac%zd.png",i);
        vecFrame.pushBack(sprCache->getSpriteFrameByName(_path));
        
        {
            std::string _path = StringUtils::format("tx_xingau_0%zd.png",i);
            showFrame.pushBack(sprCache->getSpriteFrameByName(_path));
        }
    }
    _count = random(0,(int)vecFrame.size()-1);

    this->setSpriteFrame(vecFrame.at(_count));
    
    maxTime = TIME_SHOW_RESULT + (float)TIME/2;
    TIME++;
    if (TIME == 2){
        TIME = -1;
    }
    
    indexFrame = _indexResult-1;

    this->scheduleOnce(schedule_selector(XiNgau::callBackShowResult), maxTime);
    this->schedule(schedule_selector(XiNgau::callBackAnimate), 0.01);
    

    this->setPosition(_pos);
    return true;
}

void XiNgau::callBackAnimate(float dt){
    _time+=dt;
    if (_time >= _v){
        if (_count>= 0 && _count < vecFrame.size()){
            this->setSpriteFrame(vecFrame.at(_count));
            if (_show && _count == indexFrame){
                this->setSpriteFrame(showFrame.at(indexFrame));
                this->unscheduleAllCallbacks();
                this->runAction(EaseOut::create(RotateBy::create(maxTime/3, random(0, 90)), 10));
                if (this->onResultCallBack != NULL){
                    this->onResultCallBack();
                }
            }
            _count++;
        }else{
            _count= 0;
        }
        
        if (_duration > 1){
            _duration-= 1;
        }
        _time=0;
        _v+= (dt/_duration);
    }
}

void XiNgau::callBackShowResult(float dt){
    _show = true;
}



XiNgauController* XiNgauController::create3XiNgau(int _result1, int _result2, int _result3,ccResultCallBack _resultCallBack){
    auto _xingau = new (std::nothrow) XiNgauController();
    
    if (_xingau){
        if (!_xingau->init(_result1,_result2,_result3,_resultCallBack)){
            CC_SAFE_DELETE(_xingau);
        }else{
            _xingau->autorelease();
        }
    }
    return _xingau;
}

bool XiNgauController::init(int _result1, int _result2, int _result3,ccResultCallBack _resultCallBack){
    
    
    if (!Node::init()){
        return false;
    }
    
    auto _spr1 = XiNgau::createXiNgauAtPos(Vec2(50,50),_result1,NULL);
    auto _spr2 = XiNgau::createXiNgauAtPos(Vec2(-50,50),_result2,NULL);
    auto _spr3 = XiNgau::createXiNgauAtPos(Vec2(0,-50),_result3,_resultCallBack);
    
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    _spr1->setScale(random(1.2, 1.6));
    _spr2->setScale(random(1.2, 1.6));
    _spr3->setScale(random(1.2, 1.6));
    
    auto _move1 = MoveTo::create(_spr1->maxTime, (Vec2(0,0) - _spr1->getPosition()).getNormalized()*(random(40, 50)));
    auto _move2 = MoveTo::create(_spr2->maxTime, (Vec2(0,0) - _spr2->getPosition()).getNormalized()*(random(40, 50)));
    auto _move3 = MoveTo::create(_spr3->maxTime, (Vec2(0,0) - _spr3->getPosition()).getNormalized()*(random(40, 50)));
    
    _spr1->runAction(EaseElasticOut::create(_move1, (random(5, 14))));
    _spr2->runAction(EaseElasticOut::create(_move2, (random(5, 14))));
    _spr3->runAction(EaseElasticOut::create(_move3, (random(5, 14))));
    
    auto _scale1 = ScaleTo::create(_spr1->maxTime, 1);
    auto _scale2 = ScaleTo::create(_spr2->maxTime, 1);
    auto _scale3 = ScaleTo::create(_spr3->maxTime, 1);
    
    _spr1->runAction(EaseElasticOut::create(_scale1->clone(), (random(0.1, 0.5))));
    _spr2->runAction(EaseElasticOut::create(_scale2->clone(), (random(0.1, 0.5))));
    _spr3->runAction(EaseElasticOut::create(_scale3->clone(), (random(0.1, 0.5))));
    
    _spr3->onResultCallBack = _resultCallBack;
    
    this->addChild(_spr1);
    this->addChild(_spr2);
    this->addChild(_spr3);
    
    this->setRotation(random(0,360));
    
    auto _rotate = RotateBy::create(3, 720);
    
    this->runAction(EaseOut::create(_rotate, 10));
    
    return true;
}



























