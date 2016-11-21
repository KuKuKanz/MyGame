//
//  AnimatedCoin.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/4/16.
//
//

#ifndef AnimatedCoin_hpp
#define AnimatedCoin_hpp
#include <SimpleAudioEngine.h>
#include "audio/include/AudioEngine.h"


using namespace cocos2d;


enum CoinType{
    GOLD = 0,
    SILVER = 1,
    BRONZE = 2,

};


class AnimatedCoin : public Sprite{
    
private:
    bool FINAL_FLAG;
    
    RepeatForever* coinAnimate;
    Layer* parent;
    CoinType type;
    
    float scale,duration;
    
    ParticleSystemQuad* effect;
    
    static AnimatedCoin* createCoinType (CoinType _type);
    
    static std::string getCoinPath      (CoinType _type);
    
    //** This method call stopAll first, it then clear all coins from memory
    static void stopAll();
    
    //** If you want to create coins again, MUST re-call loadResource()
    static void clearAll();
    
    void start(Vec2 _startPoint,
               Vec2 _endPoint,
               Layer* _layer,
               CallFuncN* callback,
               CallFuncN* callback2);
    
    bool initCoin           (CoinType _type);
    
    void updateParticle     (float dt);
    
    void SetAnimatedAction  (Vec2 _start,Vec2 _end,CallFuncN* callback,CallFuncN* callback2);
    
    
public:
    bool isStop;

    
    //** You MUST implement this method at begining of the game */
    //** This is to load resource and prepare for using lately */
    static void loadResource();

    //** This is main method to create Coin  */
    //@Param _Count         number of coins you want to create  */
    //@Param _type          type of Coin: Gold/Silver or Bronze */
    //@Param _startPoint    started point of coins when created */
    //@Param _endPoint      destination of coins                */
    //@Param _layer         use to add coins as child, after finishing coins automatically removed from this layer */
    //@Param &func          throw a callback when coin reach destination or removed from their parent */
    static Vector<AnimatedCoin*> CreateCoinAtPos(int _count,
                                CoinType _type,
                                Vec2 _startPoint,
                                Vec2 _endPoint,
                                Layer* _layer,
                                CallFuncN* callback,
                                CallFuncN* callback2,
                                float _scale,
                                float duration);


    void stop();
};




//** AnimatedCoinWave: used to manage animated coin easily
//**
//**
class AnimatedCoinWave : public Layer{
//**    ///////////////////////////////////////////////////////
//  - createAnimatedCoinWave: used to create instance.
//  - SetCoinType           : used to set up coin type : GOLD, SILVER OR BRONZE
//  - setScale              : used to set up scale value for coin
//
//  - start()               : coin start moving
//  - stop()                : stop coin
//  - clear()               : remove this instance and it's parent as well.
//**
//**
//**    ///////////////////////////////////////////////////////
public:
    static AnimatedCoinWave* createAnimatedCoinWave(int _count,
                                                    Vec2 _startPoint,
                                                    Vec2 _endPoint);
    
    void SetCoinType        (CoinType _type);
    
    void addCoinCallBack    (const std::function<void(Node*)>& func);
    
    void setScale           (float _scale) override;
    
    void setDuration        (float _duration);
    
    void start();
    
    void stop();
    
    void clear();
    
private:
    CoinType typeCoin;
    
    Vector<AnimatedCoin*> vecCoin;
    
    int countCoin;
    float scale,duration;
    
    Vec2 startPoint;
    Vec2 endPoint;
    
    bool isStart;
    
    CallFuncN* callBack;
    
    
    bool initAnimatedCoinWave(int _count,Vec2 _startPoint, Vec2 _endPoint);
    
    void update(float dt);
    
};

#endif /* AnimatedCoin_hpp */
