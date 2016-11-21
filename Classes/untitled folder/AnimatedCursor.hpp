//
//  AnimatedCursor.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/7/16.
//
//

#ifndef AnimatedCursor_hpp
#define AnimatedCursor_hpp
#include "ui/CocosGUI.h"
#include "TaiXiuDialog.hpp"
#include <stdio.h>


using namespace cocos2d;
using namespace cocos2d::ui;


class AnimatedCursor : public Node{
    
public:
    
    /**
     * Get cursor.
     */
    static AnimatedCursor* getInstance();
    
    
    typedef std::function<void(void)> ccCursorCallBack;
    /**
     * This public variable used to set up CALLBACK function when user click on cursor.
     *
     */
    ccCursorCallBack onCursorClickedCallBack;
    
    /**
     * Change the image of cursor
     *
     * @param NORMAL normal state texture name.
     * @param PRESSED  selected state texture name.
     * @param DISABLE disabled state texture name.
     * @param TYPE    used from .plist or local file
     */
    void setCursorImage(const char* NORMAL,
                        const char* PRESSED,
                        const char* DISABLE,
                        Widget::TextureResType TYPE);
    
    /**
     * In normal state, cursor will automatically move to side of border
     * If you didn't want this, set to FALSE
     *
     * @param enable TRUE or FALSE
     */
    void setAutoPushToBorder(bool enable);
    
    /**
     * Cursor will automatically be faded out after a period.
     * Use this method to change the period.
     *
     * @param duration - how long cursor will be faded after.
     */
    void setSleepingTime(const double duration);
    
    /**
     * Change the size of cursor
     *
     * @param _scale - size of the cursor.

     */
    virtual void setScale(float _scale);
    
    /**
     * Change the position of cursor
     *
     * @param &position new position of the cursor.
     */
    virtual void setPosition(const Vec2 &position);
    
    /**
     * Change the speed of cursor
     *
     * @param &_speed new speed of the cursor.
     */
    virtual void setSpeed(float _speed);
    /**
     * Return current scale value of the cursor
     */
    virtual const float getScale();
    
    /**
     * Return current position of the cursor
     */
    virtual const Vec2 getPosition();
    
private:
    Button* cursor;
    
    EventListenerTouchOneByOne* touchListen;
    Vec2 detalCursor,destCursor;

    Text* txtTime;
    float speed,defaultSpeed,wCur,hCur;
    double timeEslapse,timeExpire;
    
    bool isTouching,autoPush,RUNNING_FLAG;
    
    bool init();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void pushToBorder();
    void createTimeText();
    
    void cursorCallBack(Ref* pSender,Widget::TouchEventType type);
    
    void onEnter();
    void onExit();
    
    void runUpdate();
    void update(float dt);
    CREATE_FUNC(AnimatedCursor);
};


#endif /* AnimatedCursor_hpp */
