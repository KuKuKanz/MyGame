//
//  XiNgau.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/3/16.
//
//

#ifndef XiNgau_hpp
#define XiNgau_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <stdio.h>

using namespace cocos2d;
using namespace cocos2d::ui;


class XiNgau : public Sprite{
public:
    typedef std::function<void()> ccResultCallBack;

    static XiNgau* createXiNgauAtPos(Vec2 _pos,int _indexResult,ccResultCallBack _callBackResult);
    static void loadResource();
    
    float maxTime;
    
    
    ccResultCallBack onResultCallBack;
    
private:
    int _count,indexFrame;
    
    bool _show;
    
    float _speed,_moveSpeed;
    virtual bool init(Vec2 _pos,int _indexResult,ccResultCallBack _callBackResult);
    Vec2 _orginalPos;
    
    float _time,_duration,_v;
    Vector<SpriteFrame*> showFrame;
    Vector<SpriteFrame*> vecFrame;
    
    void callBackAnimate(float dt);
    void callBackShowResult(float dt);
    
};


class XiNgauController : public Node{
public:
    typedef std::function<void()> ccResultCallBack;
    
    static XiNgauController* create3XiNgau(int _result1, int _result2, int _result3,ccResultCallBack _resultCallBack);
    
private:
    bool init(int _result1, int _result2, int _result3,ccResultCallBack _resultCallBack);
    
};

#endif /* XiNgau_hpp */
