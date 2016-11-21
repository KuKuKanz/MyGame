//
//  LayourEffect.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/19/16.
//
//

#ifndef LayourEffect_hpp
#define LayourEffect_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

enum EffectType{
    STATIC = 0,
    DYNAMIC = 1,
    COMBINE = 2
};

class LayourEffect : public Node{
public:
    static LayourEffect* createWithSize(cocos2d::Size _size,EffectType _type);
    bool initWithSprite(cocos2d::Size _size,EffectType _type);
    
    void stop();
    void start();
    void clear();
private:
    Vector<ParticleSystemQuad*> vecPar;
    
    ParticleSystemQuad* effectT;
    ParticleSystemQuad* effectB;
    ParticleSystemQuad* effectL;
    ParticleSystemQuad* effectR;
    
    RepeatForever* lAct,*rAct,*bAct,*tAct;
    
    LayourEffect* effectCombine;
    
    LayourEffect();
    ~LayourEffect();
    
    void createStaticEffect(cocos2d::Size _size);
    void createDynamicEffect(cocos2d::Size _size);
    void createCombine(cocos2d::Size _size);
    
public:
    void changeParticleColor(Color4F _color4f);
    void changeParticleCount(int _total);
    void changeParticleScale(float _scale);
    

};
#endif /* LayourEffect_hpp */
