//
//  SpriteEffect.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/20/16.
//
//

#include "SpriteEffect.hpp"


SpriteEffect* SpriteEffect::createWithPathAtPos(string _path, cocos2d::Vec2 _pos){
    
    auto _obj = new (std::nothrow) SpriteEffect();
    
    if (_obj){
        if (!_obj->initWithPathAtPos(_path, _pos)){
            CC_SAFE_DELETE(_obj);
        }
    }
    return _obj;
}


bool SpriteEffect::initWithPathAtPos(string _path, cocos2d::Vec2 _pos){
    
    if (!Sprite::init()){
        return false;
    }
    
    this->setSpriteFrame(_path);
    
    this->setPosition(_pos);
    
    
    
    this->setScale(2);
    this->setOpacity(0);
    auto _scaleDown = ScaleTo::create(0.7, 1);
    auto _fadIn = FadeIn::create(0.5);
    
    auto _ease = EaseExponentialIn::create(_scaleDown);
    auto __ease = EaseExponentialIn::create(_fadIn);
    
    auto _effectCallBack = CallFuncN::create(CC_CALLBACK_0(SpriteEffect::gucTungEffectCallBack, this));
    
    this->runAction(Sequence::create(Spawn::create(_ease,__ease, NULL),_effectCallBack, NULL));
    
    
    this->runAction(Sequence::create(DelayTime::create(1.5),RemoveSelf::create(), NULL));
    return true;
}

void SpriteEffect::gucTungEffectCallBack(){
    ParticleSystemQuad* effect = ParticleSystemQuad::create("Catte/gucTungEffect.plist");
    effect->resetSystem();
    effect->setScale(0.5);
    effect->setSpeed(250);
    effect->setLife(0.5);
    
    effect->setPosVar(Vec2(this->getContentSize().width,10));
    effect->setAutoRemoveOnFinish(true);
    effect->setPosition(this->getPosition());
    
    if (this->getParent() != NULL){
        this->getParent()->addChild(effect,this->getGlobalZOrder()-1);
    }else{
        CCLOG("SpriteEffect: void gucTungEffectCallBack() : -- can't find parent of this instance");
        CCLOG("SpriteEffect: void gucTungEffectCallBack() : -- can't find parent of this instance");
        CCLOG("SpriteEffect: void gucTungEffectCallBack() : -- can't find parent of this instance");
    }
}
