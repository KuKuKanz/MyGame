//
//  AnimatedCoin.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/4/16.
//
//

#include "AnimatedCoin.hpp"
#include "ResourceNew.h"


// ** How many coins do you want to store initially */
static const int COIN_PER_TYPE       = 50;

// ** .plist file of coin */
static const char* COIN_PLIST       = srcPLIST_LuckyWheel_small;

// ** How many types do we have here, we have 3 at present : GOLD SILVER AND BRONZE
static const int TOTAL_TYPE         = 3;

static const int FRAME_START_INDEX  = 1;
static const int FRAME_END_INDEX    = 8;

// ** Path for playing sound when coins reach destination */
static const char* SOUND_PATH        = "coinwave.wav";

// ** Path of Particle effect to border around the coins. */
static const char* PARTICEL_PATH     = "win_effect.plist";



static Vector<AnimatedCoin*> arrMoving;
static Vector<AnimatedCoin*> arrWaiting[TOTAL_TYPE];
static std::string COIN_PATH_TYPE[TOTAL_TYPE];
bool isload = false;


void AnimatedCoin::loadResource(){

    if (!isload){
  
        if (!SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded(COIN_PLIST)){
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(COIN_PLIST);
        }
        
        COIN_PATH_TYPE[(int)CoinType::GOLD]     =   "lw_iconCoin";
        COIN_PATH_TYPE[(int)CoinType::SILVER]   =   "lw_silverCoin";
        COIN_PATH_TYPE[(int)CoinType::BRONZE]   =   "lw_copperCoin";
        
        
        for(int i = 0;i < COIN_PER_TYPE; i++){
            int index = 0;
            arrWaiting[index++].pushBack(AnimatedCoin::createCoinType(CoinType::GOLD));
            arrWaiting[index++].pushBack(AnimatedCoin::createCoinType(CoinType::SILVER));
            arrWaiting[index++].pushBack(AnimatedCoin::createCoinType(CoinType::BRONZE));
            
            
            //** If you have a new type of coin, please create objects for that type here
            isload = true;
        }
    }
    
}


std::string AnimatedCoin::getCoinPath(CoinType _type){
    return COIN_PATH_TYPE[(int)_type];
}

Vector<AnimatedCoin*> AnimatedCoin::CreateCoinAtPos(int _count,
                                                    CoinType _type,
                                                    cocos2d::Vec2 _startPoint,
                                                    cocos2d::Vec2 _endPoint,
                                                    cocos2d::Layer *_layer,
                                                    cocos2d::CallFuncN *callback,
                                                    CallFuncN* callback2,
                                                    float _scale,
                                                    float duration){
    
    int index = (int)_type;
    
    Vector<AnimatedCoin*> vecCoin;
    
    for(int i = 0;i<_count;i++){
        if (arrWaiting[index].size() > 0){
            auto coin = arrWaiting[index].at(0);
            coin->scale = _scale;
            coin->duration = duration;
            vecCoin.pushBack(coin);
            arrMoving.pushBack(coin);
            arrWaiting[index].eraseObject(coin);
        }
    }
    
    if (vecCoin.size() > 0){
        vecCoin.at(vecCoin.size()-1)->FINAL_FLAG = true;
        for(auto _coin : vecCoin){
            _coin->start(_startPoint,
                         _endPoint,
                         _layer,
                         callback,
                         callback2);
        }
    }
    
    return vecCoin;
}

AnimatedCoin* AnimatedCoin::createCoinType(CoinType _type){
    auto coin = new (std::nothrow) AnimatedCoin();
    
    if (coin){
        if (!coin->initCoin(_type)){
            CC_SAFE_DELETE(coin);
        }
    }
    
    return coin;
}


bool AnimatedCoin::initCoin(CoinType _type){
    
    if (!Sprite::init()){
        return false;
    }
    
    this->FINAL_FLAG = false;
    this->type = _type;
    this->isStop = false;
    this->target = NULL;
    
    std::string coinPath = getCoinPath(_type);
    
    Vector<SpriteFrame*> vecFrame;
    
    for(int i = FRAME_START_INDEX; i < FRAME_END_INDEX+1; i++){
        vecFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s%zd%s",coinPath.c_str(),i,".png")));
    }
    
    auto animation = Animation::createWithSpriteFrames(vecFrame,0.04);
    auto animate = Animate::create(animation);
    
    this->coinAnimate = RepeatForever::create(animate);
    this->coinAnimate->retain();

    vecFrame.clear();
    
    
    this->effect = ParticleSystemQuad::create(PARTICEL_PATH);
    this->effect->setTotalParticles(3);
    this->effect->setSpeed(30);
    this->effect->setStartSize(0);
    this->effect->setEndSize(30);
    this->effect->retain();
    

    return true;
}


void AnimatedCoin::start(cocos2d::Vec2 _startPoint,
                         cocos2d::Vec2 _endPoint,
                         cocos2d::Layer *_layer,
                         CallFuncN* callback,
                         CallFuncN* callback2){
    
    this->parent = _layer;
    this->setPosition(_startPoint);
    
    this->parent->addChild(this->effect);
    this->effect->setPosition(this->getPosition());
    this->effect->setScale(0.05);
    this->effect->resetSystem();
    this->schedule(schedule_selector(AnimatedCoin::updateParticle),1/32);
    
    this->parent->addChild(this);
    
    this->runAction(coinAnimate);
    this->SetAnimatedAction(_startPoint, _endPoint,callback,callback2);
    isStop = false;
}

void AnimatedCoin::stop(){
    if (!isStop){
        auto lightEffect = ParticleSystemQuad::create("phomwin_effect.plist");
        lightEffect->setPosition(this->getPosition());
        lightEffect->setTotalParticles(20);
        lightEffect->setSpeed(100);
        lightEffect->setDuration(0.2);
        lightEffect->setLife(0.8);
        lightEffect->setEndColor(Color4F(1, 1, 0.4, 0));
        lightEffect->setAutoRemoveOnFinish(true);
        lightEffect->resetSystem();
        
        this->getParent()->addChild(lightEffect);
        
        if (random(0, 100) > 50){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_PATH);
        }
        
        this->stopAllActions();
        this->unscheduleAllCallbacks();

        this->effect->stopSystem();
        this->effect->removeFromParent();

        int index = (int)this->type;
        arrWaiting[index].pushBack(this);
        arrMoving.eraseObject(this);

        //experimental::AudioEngine::play2d(SOUND_PATH);
        
        this->parent = NULL;
        this->removeFromParent();
        isStop = true;
        
    }
    
    
}

void AnimatedCoin::setTarget(cocos2d::Sprite *_target){
    this->target = _target;
}


void AnimatedCoin::SetAnimatedAction(cocos2d::Vec2 _start,
                                     cocos2d::Vec2 _end,
                                     CallFuncN* callback,
                                     CallFuncN* callback2){
    
    float deg = random((float)0, (float)360);
    float randDist = random(100, 150);
    float randX = randDist * cos(CC_DEGREES_TO_RADIANS(deg));
    float randY = randDist * sin(CC_DEGREES_TO_RADIANS(deg));
    
    //Change random rotation for better graphic
    this->setRotation(random((float)0, (float)360));
    
    //Init for action move
    ccBezierConfig t;
    t.controlPoint_1 = _start;
    t.controlPoint_2 = Vec2(_start.x+randX, _start.y+randY);
    t.endPosition = _end;
    BezierTo* act = BezierTo::create(random((float)duration-0.2, (float)duration+0.2), t);
   
    
    //give to sequence with callback.
    Sequence* finalAct;
    finalAct = Sequence::create(act,callback,CallFuncN::create(CC_CALLBACK_0(AnimatedCoin::stop, this)), NULL);
    this->setScale(0.05);
    
    auto spawn = Spawn::create(RotateBy::create(5, 120),ScaleTo::create(1, this->scale),finalAct, NULL);
    
    this->effect->runAction(ScaleTo::create(duration, this->scale*1.5));
    this->runAction(spawn);
    
}

void AnimatedCoin::updateParticle(float dt){
    this->effect->setPosition(this->getPosition());
}

void AnimatedCoin::stopAll(){
    
    Vector<AnimatedCoin*> vecTemp;
    
    if (arrMoving.size() > 0){
        for(auto coin : arrMoving){
            vecTemp.pushBack(coin);
        }
        
        for(auto coin : vecTemp){
            coin->stop();
        }
    }
}

void AnimatedCoin::clearAll(){
    isload = false;
    
    stopAll();
    
    for(int i = 0;i < 3;i++){
        Vector<AnimatedCoin*> vecTemp;
        
        for(auto coin : arrWaiting[i]){
            vecTemp.pushBack(coin);
        }
        for(auto coin : vecTemp){
            coin->coinAnimate->release();
            coin->effect->release();
            coin->release();
        }
        
        arrWaiting[i].clear();
        vecTemp.clear();
    }
    
}


AnimatedCoinWave* AnimatedCoinWave::createAnimatedCoinWave(int _count,
                                                           cocos2d::Vec2 _startPoint,
                                                           cocos2d::Vec2 _endPoint){
    
    auto _layer = new (std::nothrow) AnimatedCoinWave();
    
    if (_layer){
        if (!_layer->initAnimatedCoinWave(_count, _startPoint, _endPoint)){
            CC_SAFE_DELETE(_layer);
        }
    }
    
    return _layer;
}


bool AnimatedCoinWave::initAnimatedCoinWave(int _count,
                                            cocos2d::Vec2 _startPoint,
                                            cocos2d::Vec2 _endPoint){
    
    if (!Layer::init()){
        return false;
    }
    

    this->isStart = false;
    this->countCoin = _count;
    this->startPoint = _startPoint;
    this->endPoint = _endPoint;
    this->scale = 0.5;
    this->duration = 2.5;
    this->callBack = NULL;

    
    return true;
}

void AnimatedCoinWave::SetCoinType(CoinType _type){
    this->typeCoin = _type;
}


void AnimatedCoinWave::addCoinCallBack(const std::function<void (Node *)> &func){
    this->callBack = CallFuncN::create(func);
    this->callBack->retain();
}

void AnimatedCoinWave::setScale(float _scale){
    this->scale = _scale;
}

void AnimatedCoinWave::setDuration(float _duration){
    this->duration = _duration;
}

void AnimatedCoinWave::start(){
    if (!isStart){
        auto callbackStop = CallFuncN::create(CC_CALLBACK_0(AnimatedCoinWave::stop, this));
        this->vecCoin = AnimatedCoin::CreateCoinAtPos(this->countCoin,
                                                      this->typeCoin,
                                                      this->startPoint,
                                                      this->endPoint,
                                                      this,
                                                      this->callBack,
                                                      callbackStop,
                                                      this->scale,
                                                      this->duration);
        this->scheduleUpdate();
        
        isStart = true;
    }
    
}

void AnimatedCoinWave::update(float dt){
    for(auto _coin : vecCoin){
        if (!_coin->isStop){
            return;
        }
    }
    
    if (callBack != NULL){
        this->runAction(callBack);
        this->clear();

    }
    
}

void AnimatedCoinWave::stop(){
    ///Play some sounds

    this->unscheduleUpdate();
    for(auto coin : this->vecCoin){
        coin->stop();
    }
    
    log("stop");
    this->vecCoin.clear();
    isStart = false;
}

void AnimatedCoinWave::clear(){
    this->stop();
    
    this->removeFromParent();
    callBack->release();
    this->release();
}







