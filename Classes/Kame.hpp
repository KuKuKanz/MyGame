//
//  Kame.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/21/16.
//
//

#ifndef Kame_hpp
#define Kame_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <SimpleAudioEngine.h>
#include <stdio.h>

using namespace cocos2d;
using namespace cocos2d::ui;

class Kamehameha : public Node{
public:
    virtual bool init();
    
    CREATE_FUNC(Kamehameha);
    
private:
    ParticleSystemQuad* _coverEnergy;
    ParticleSystemQuad* _finalCast;
    ParticleSystemQuad* _head;
    ParticleSystemQuad* _OpHead;

    Vector<ParticleSystemQuad*> vecPar;
    
    void update(float dt);
    void callBackFinalCast(float dt);
    void callBackStop(float dt);
    
    void callBackHeadStop();

};

#endif /* Kame_hpp */
