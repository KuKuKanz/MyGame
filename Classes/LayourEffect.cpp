//
//  LayourEffect.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/19/16.
//
//

#include "LayourEffect.hpp"

LayourEffect::LayourEffect(){
    effectT = NULL;
    effectB = NULL;
    effectR = NULL;
    effectL = NULL;
    effectCombine = NULL;
}

LayourEffect::~LayourEffect(){
}

LayourEffect* LayourEffect::createWithSize(Size _size,EffectType _type){
    
    auto obj = new (std::nothrow) LayourEffect();
    
    if (obj){
        if (!obj->initWithSprite(_size,_type)){
            CC_SAFE_DELETE(obj);
        }
    }
    
    return obj;
}


bool LayourEffect::initWithSprite(Size _size,EffectType _type){
    
    if (!Node::init()){
        return false;
    }
    this->setAnchorPoint(Vec2(0.5,0.5));
    
    auto _layout = Layout::create();
    _layout->setAnchorPoint(Vec2(0.5,0.5));
    _layout->setContentSize(_size);
   // _layout->setPosition(this->getContentSize()/2);
    _layout->setBackGroundColor(Color3B::BLUE);
    _layout->setOpacity(125);
    _layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    //this->addChild(_layout);
    
    switch (_type) {
        case STATIC:
        {
            createStaticEffect(_size);
        }
            break;
        
            case DYNAMIC:
        {
            createDynamicEffect(_size);
        }
            break;
            
        default:
        {
            createCombine(_size);
        }
            break;
    }
    
    
    return true;
}

void LayourEffect::createStaticEffect(cocos2d::Size _size){
    float _w = _size.width;
    float _h = _size.height;
    
    effectT = ParticleSystemQuad::create("layoutEffect.plist");
    effectT->setPosVar(Vec2(_w/2+2,1));
    effectT->setPosition(Vec2(_w/2,_h-2));
    effectT->setStartSize(10);
    effectT->setStartSizeVar(2);
    effectT->setGravity(Vec2(0,300));
    this->addChild(effectT);
    
    effectB = ParticleSystemQuad::create("layoutEffect.plist");
    effectB->setPosVar(Vec2(_w/2+2,1));
    effectB->setPosition(Vec2(_w/2,2));
    effectB->setStartSize(10);
    effectB->setStartSizeVar(2);
    effectB->setGravity(Vec2(0,-300));
    this->addChild(effectB);
    
    effectL = ParticleSystemQuad::create("layoutEffect.plist");
    effectL->setPosVar(Vec2(_h/2+2,1));
    effectL->setPosition(Vec2(-2,_h/2));
    effectL->setStartSize(10);
    effectL->setStartSizeVar(2);
    effectL->setGravity(Vec2(0,300));
    effectL->cocos2d::Node::setRotation(-90);
    this->addChild(effectL);
    
    effectR = ParticleSystemQuad::create("layoutEffect.plist");
    effectR->setPosVar(Vec2(_h/2+2,1));
    effectR->setPosition(Vec2(_w-2,_h/2));
    effectR->setStartSize(10);
    effectR->setStartSizeVar(2);
    effectR->setGravity(Vec2(0,-300));
    effectR->cocos2d::Node::setRotation(-90);
    this->addChild(effectR);
    
    vecPar.pushBack(effectT);
    vecPar.pushBack(effectB);
    vecPar.pushBack(effectL);
    vecPar.pushBack(effectR);
}



void LayourEffect::createDynamicEffect(cocos2d::Size _size){
    float _w = _size.width;
    float _h = _size.height;
    
    Color4F _color = Color4F(1.0, 1, 1, 1);

    
    
    effectL = ParticleSystemQuad::create("layoutEffect2.plist");
    effectR = ParticleSystemQuad::create("layoutEffect2.plist");
    effectT = ParticleSystemQuad::create("layoutEffect2.plist");
    effectB = ParticleSystemQuad::create("layoutEffect2.plist");
    
    effectL->setScale(0.5);
    effectR->setScale(0.5);
    effectT->setScale(0.5);
    effectB->setScale(0.5);
    
    effectL->setAnchorPoint(Vec2(0.5,0.5));
    effectR->setAnchorPoint(Vec2(0.5,0.5));
    effectT->setAnchorPoint(Vec2(0.5,0.5));
    effectB->setAnchorPoint(Vec2(0.5,0.5));
    
    effectL->setStartColor(_color);
    effectR->setStartColor(_color);
    effectT->setStartColor(_color);
    effectB->setStartColor(_color);
    
    effectB->setTotalParticles(30);
    effectL->setTotalParticles(30);
    effectR->setTotalParticles(30);
    effectT->setTotalParticles(30);
    
    Vec2 _posLB = Vec2(-_w/2,-_h/2+4);
    Vec2 _posLT = Vec2(-_w/2,_h/2);
    Vec2 _posRT = Vec2(_w/2,_h/2);
    Vec2 _posRB = Vec2(_w/2,-_h/2+4);

    effectL->setPosition(_posLB);
    effectR->setPosition(_posRT);
    effectT->setPosition(_posLT);
    effectB->setPosition(_posRB);
    
    float _time = 1;
    
    
    auto _moveLB_to_LT = MoveTo::create(_time, _posLT);
    auto _moveLT_to_RT = MoveTo::create(_time, _posRT);
    auto _moveRT_to_RB = MoveTo::create(_time, _posRB);
    auto _moveRB_to_LB = MoveTo::create(_time, _posLB);

    
    lAct = RepeatForever::create(Sequence::create( _moveLB_to_LT->clone(),
                                                   _moveLT_to_RT->clone(),
                                                  _moveRT_to_RB->clone(),
                                                  _moveRB_to_LB->clone(), NULL));
    
    tAct = RepeatForever::create(Sequence::create( _moveLT_to_RT->clone(),
                                                  _moveRT_to_RB->clone(),
                                                  _moveRB_to_LB->clone(),
                                                  _moveLB_to_LT->clone(), NULL));
    
    rAct = RepeatForever::create(Sequence::create(_moveRT_to_RB->clone(),
                                                                   _moveRB_to_LB->clone(),
                                                                   _moveLB_to_LT->clone(),
                                                                   _moveLT_to_RT->clone(), NULL));
                                 
    bAct = RepeatForever::create(Sequence::create(_moveRB_to_LB->clone(),
                                                  _moveLB_to_LT->clone(),
                                                  _moveLT_to_RT->clone(),
                                                  _moveRT_to_RB->clone(), NULL));
    
    effectL->runAction(lAct);
    effectT->runAction(tAct);
    effectR->runAction(rAct);
    effectB->runAction(bAct);
    
    
    this->addChild(effectL);
    this->addChild(effectR);
    this->addChild(effectT);
    this->addChild(effectB);
    
    vecPar.pushBack(effectT);
    vecPar.pushBack(effectB);
    vecPar.pushBack(effectL);
    vecPar.pushBack(effectR);

}

void LayourEffect::createCombine(cocos2d::Size _size){
    this->createStaticEffect(_size);
    
    effectCombine = createWithSize(_size, EffectType::DYNAMIC);
    
    this->addChild(effectCombine);
}

void LayourEffect::changeParticleColor(cocos2d::Color4F _color4f){
    for(auto _par : vecPar){
        _par->setStartColor(_color4f);
    }
}

void LayourEffect::changeParticleCount(int _total){
    for(auto _par : vecPar){
        _par->setTotalParticles(_total);
    }
}

void LayourEffect::changeParticleScale(float _scale){
    for(auto _par : vecPar){
        _par->setScale(_scale);
    }
}


void LayourEffect::stop(){
    for(auto _par : vecPar){
        _par->stopSystem();
    }
    
    if (effectCombine != NULL){
        effectCombine->stop();
    }
}

void LayourEffect::start(){
    for(auto _par : vecPar){
        _par->resetSystem();
    }
    
    if (effectCombine != NULL){
        effectCombine->start();
    }
}

void LayourEffect::clear(){
    this->stop();
    
    for(auto _par : vecPar){
        this->removeChild(_par);
    }
    
    if (effectCombine != NULL){
        effectCombine->clear();
        this->removeChild(effectCombine);
    }
}
