//
//  SpriteEffect.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/20/16.
//
//

#ifndef SpriteEffect_hpp
#define SpriteEffect_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class SpriteEffect : public Sprite{
public:
    static SpriteEffect* createWithPathAtPos(string _path, Vec2 _pos);
    
    bool initWithPathAtPos(string _path, Vec2 _pos);
    
    void gucTungEffectCallBack();
    
};
#endif /* SpriteEffect_hpp */
