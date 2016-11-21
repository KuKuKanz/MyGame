//
//  AnimatedCursor.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/7/16.
//
//

#include "AnimatedCursor.hpp"
#include "ResourceNew.h"

/**
 * Change parameter for personally used purpose
 *
 * @param FRAME_TYPE        where resource come from PLIST or LOCAL (default is LOCAL)
 * @param FRAME_NORMAL      normal state texture name.
 * @param FRAME_PRESS       selected state texture name.
 * @param FRAME_DISABLE     disabled state texture name.
 */

static const Widget::TextureResType FRAME_TYPE = Widget::TextureResType::LOCAL;
static const char* FRAME_NORMAL     = "TaiXiu/tx_miniicon.png";
static const char* FRAME_PRESS      = "TaiXiu/tx_miniicon_tap.png";
static const char* FRAME_DISABLE    = "TaiXiu/tx_miniicon.png";



static Vec2 winSize;

static AnimatedCursor* _animatedCursor = NULL;

AnimatedCursor* AnimatedCursor::getInstance(){
    if (_animatedCursor == NULL){
        _animatedCursor = AnimatedCursor::create();
        _animatedCursor->onCursorClickedCallBack = CC_CALLBACK_0(TaiXiuDialog::openTXDialog, TaiXiuDialog::getInstance());
        _animatedCursor->addChild(TaiXiuDialog::getInstance());
         
        _animatedCursor->retain();
    }
    
    return _animatedCursor;
}

void AnimatedCursor::onEnter(){
    Node::onEnter();
    AnimatedCursor::getInstance()->RUNNING_FLAG = false;
    AnimatedCursor::getInstance()->runUpdate();
    AnimatedCursor::getInstance()->isTouching = false;
    if (TaiXiuDialog::getInstance()->getisPause()){
        TaiXiuDialog::getInstance()->resetTimer();
    }
    
}

void AnimatedCursor::onExit(){
    Node::onExit();
    //AnimatedCursor::getInstance()->onCursorClickedCallBack = NULL;
}

bool AnimatedCursor::init(){
    
    if (!Node::init()){
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    
    this->defaultSpeed = 0.2;
    this->timeEslapse = 0;
    this->speed = defaultSpeed;
    this->isTouching = false;
    this->autoPush = true;
    this->RUNNING_FLAG = true;
    this->timeExpire = 10000;
    bDisableSleep= false;
    

    this->cursor = Button::create(FRAME_NORMAL,FRAME_PRESS,FRAME_DISABLE,FRAME_TYPE);
    this->cursor->setTag(1);
    //this->cursor->setPosition(winSize/2);
    this->cursor->setPosition(Vec2(winSize.x*0.2,winSize.y*0.9));
    this->cursor->setScale(0.8);
    this->wCur = cursor->getContentSize().width/2;
    this->hCur = cursor->getContentSize().height/2;
    this->destCursor = this->cursor->getPosition();
    this->set_Cursor(this->cursor);
    
    _backGroundTXResult = ImageView::create(srcPNG_tx_miniicon_result_bg,Widget::TextureResType::PLIST);
    _backGroundTXResult->setScale9Enabled(true);
    _backGroundTXResult->setContentSize(Size(cursor->getContentSize().width*1.25,cursor->getContentSize().height));
    _backGroundTXResult->setScaleY(_cursor->getScaleY());
    _backGroundTXResult->setAnchorPoint(Vec2(1,0.5));
    _backGroundTXResult->setVisible(false);
    this->set_BackGroundCursor(_backGroundTXResult);
    
    this->addChild(_backGroundTXResult);
    this->addChild(this->cursor);

    
    
    this->cursor->addTouchEventListener(CC_CALLBACK_2(AnimatedCursor::cursorCallBack, this));
    
    touchListen = EventListenerTouchOneByOne::create();
    
    touchListen->onTouchBegan = CC_CALLBACK_2(AnimatedCursor::onTouchBegan, this);
    touchListen->onTouchMoved = CC_CALLBACK_2(AnimatedCursor::onTouchMoved, this);
    touchListen->onTouchEnded = CC_CALLBACK_2(AnimatedCursor::onTouchEnded, this);
    
    this->createTimeText();
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListen, this);
    
    this->scheduleUpdate();
    
    
    return true;
}

bool AnimatedCursor::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    return true;
}

void AnimatedCursor::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    if (isTouching){
        this->destCursor = touch->getLocation();
        this->speed = defaultSpeed;
        this->runUpdate();
    }
}

void AnimatedCursor::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    if (isTouching){
        this->destCursor = touch->getLocation();
        this->speed = defaultSpeed;
    }

}

void AnimatedCursor::cursorCallBack(cocos2d::Ref *pSender, Widget::TouchEventType type){
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            if (this->onCursorClickedCallBack != NULL){
                this->onCursorClickedCallBack();
            }
            
            if (this->autoPush){this->pushToBorder();}
            
            this->cursor->setSwallowTouches(true);
            touchListen->setSwallowTouches(false);
            this->runUpdate();
            isTouching = false;
            break;
            
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            this->cursor->setSwallowTouches(false);
            touchListen->setSwallowTouches(true);
            this->runUpdate();
            isTouching = true;
            break;
            
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            if (this->autoPush){this->pushToBorder();}
            this->cursor->setSwallowTouches(true);
            touchListen->setSwallowTouches(false);
            this->runUpdate();
            isTouching = false;
            break;
            
        default:
            break;
    }
}

void AnimatedCursor::runUpdate(){
    this->timeEslapse = 0;
    this->cursor->stopAllActions();
    this->cursor->setOpacity(255);
    if (!this->RUNNING_FLAG){
        RUNNING_FLAG = true;
        this->scheduleUpdate();
    }
}

void AnimatedCursor::setScale(float _scale){
    this->cursor->setScale(_scale);
    this->_backGroundTXResult->setScaleY(_scale);
    
    
    this->wCur = cursor->getContentSize().width/2 * cursor->getScale();
    this->hCur = cursor->getContentSize().height/2 * cursor->getScale();
    
}

void AnimatedCursor::setSpeed(float _speed){
    this->defaultSpeed = _speed;
}

const float AnimatedCursor::getScale(){
    return cursor->getScale();
}

void AnimatedCursor::setPosition(const cocos2d::Vec2 &position){
    this->cursor->setPosition(position);
}

const Vec2 AnimatedCursor::getPosition(){
    return cursor->getPosition();
}

void AnimatedCursor::setAutoPushToBorder(bool enable){
    this->autoPush = enable;
}

void AnimatedCursor::setSleepingTime(const double duration){
    this->timeExpire = duration;
    this->runUpdate();
}

void AnimatedCursor::setCursorImage(const char *NORMAL, const char *PRESSED, const char *DISABLE, Widget::TextureResType TYPE){
    this->cursor->loadTextures(NORMAL,PRESSED,DISABLE,TYPE);
    this->wCur = cursor->getContentSize().width/2;
    this->hCur = cursor->getContentSize().height/2;
}

void AnimatedCursor::pushToBorder(){
    float xCur = this->cursor->getPosition().x;
    float yCur = this->cursor->getPosition().y;
    
    
    float rangeL = xCur;
    float rangeR = winSize.x - xCur;
    float rangeT = winSize.y - yCur;
    float rangeB = yCur;
    float minRange = rangeL;
    
    Vec2 delta = Vec2(-rangeL,0);

    if (minRange > rangeR){
        minRange = rangeR;
        delta = Vec2(rangeR,0);
    }
    
    if (minRange > rangeT){
        minRange = rangeT;
        delta = Vec2(0,rangeT);
    }
    
    if (minRange > rangeB){
        minRange = rangeB;
        delta = Vec2(0,-rangeB);
    }
    
    
    this->destCursor = this->cursor->getPosition() + delta;
    this->speed = defaultSpeed;
}

void AnimatedCursor::update(float dt){
    Vec2 delta = destCursor - this->cursor->getPosition();
    Vec2 _pos = delta.getNormalized() * (this->speed*(this->cursor->getPosition().distance(destCursor)));
    
    this->cursor->setPosition(this->cursor->getPosition() + _pos);
    
    float _txtH = txtTime->getContentSize().height/2;
    
    Vec2 movePos = this->cursor->getPosition() + _pos;
    
    if (movePos.x - wCur < 0){
        this->cursor->setPositionX(wCur);
    }
   
    if (movePos.x + wCur > winSize.x){
        this->cursor->setPositionX(winSize.x - wCur);
    }
    
    if (movePos.y - hCur < 0){
        this->cursor->setPositionY(hCur);
    }
    
    if (movePos.y + hCur + _txtH > winSize.y){
        this->cursor->setPositionY(winSize.y - (hCur+_txtH));
    }
    
    timeEslapse+=dt;
    if (timeEslapse > timeExpire && !bDisableSleep){
        this->unscheduleUpdate();
        this->RUNNING_FLAG = false;
        this->cursor->runAction(FadeTo::create(1, 255/2));
    }
    
    _backGroundTXResult->setPosition(_cursor->getPosition());
    
}



void AnimatedCursor::createTimeText(){
    txtTime = Text::create("00:00", srcTFF_Roboto_Bold, 20);
    txtTime->setAnchorPoint(Vec2(0.5,0.5));
    txtTime->setTextHorizontalAlignment(TextHAlignment::CENTER);
    txtTime->setTextVerticalAlignment(TextVAlignment::CENTER);
    txtTime->setTextColor(Color4B(Color3B(126,191,82)));
    txtTime->setNormalizedPosition(Vec2(0.5,1.1144));
    txtTime->setTag(1);
    this->cursor->addChild(txtTime);
}


static bool _run = false;
static float _timeElapse = 0;

void AnimatedCursor::showBoardResult(bool _enable){
    if (_enable){
        touchListen->setEnabled(false);
        
        if (_cursor->getPositionX() < winSize.x/2){
            _cursorSide = CURSOR_ON_SIDE_LEFT;
        }else{
            _cursorSide = CURSOR_ON_SIDE_RIGHT;
        }
        
        _backGroundTXResult->setVisible(true);
        _backGroundTXResult->setScaleX(0);
        _backGroundTXResult->setPosition(_cursor->getPosition());
        _timeElapse = 0;
        _showBackGroundTxResult = true;
        _run = true;
    }else{
        
        if (_cursor->getPositionX() < winSize.x/2){
            _cursorSide = CURSOR_ON_SIDE_LEFT;
        }else{
            _cursorSide = CURSOR_ON_SIDE_RIGHT;
        }
        _timeElapse = 0.5;
        _showBackGroundTxResult = false;
        touchListen->setEnabled(true);

        _run = true;
    }
}

void AnimatedCursor::clock(float dt){
    if (!_run)  return;
    
    if (_showBackGroundTxResult){
        _timeElapse+= dt;

        float _scale = MIN(1, _timeElapse/0.5* 1);
        
        _scale*= ((float)_cursorSide);
        _backGroundTXResult->setScaleX(_scale);
        
        if (_timeElapse>=1){
            _run = false;
        }
    }else{
        _timeElapse-= dt;
        float _scale = MAX(0, _timeElapse/0.5*1);
        
        _scale*= ((float)_cursorSide);
        _backGroundTXResult->setScaleX(_scale);
        
        if (_timeElapse<=0){
            _run = false;
            _backGroundTXResult->setVisible(false);
        }
    }
    
}


