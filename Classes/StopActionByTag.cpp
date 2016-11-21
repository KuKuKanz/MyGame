//
//  StopActionByTag.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/6/16.
//
//

#include "StopActionByTag.hpp"
#include "ResourceNew.h"

static float timeElapse = 0.0f;

Scene* Demo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Demo::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Demo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_Phom);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_Cards);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BaiCao.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Catte/catte.plist");

    auto touchListen = EventListenerTouchOneByOne::create();
    
    touchListen->onTouchBegan = CC_CALLBACK_2(Demo::onTouchBegan, this);
    touchListen->onTouchMoved = CC_CALLBACK_2(Demo::onTouchMoved, this);
    touchListen->onTouchEnded = CC_CALLBACK_2(Demo::onTouchEnded, this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListen, this);

    
    auto _btn = Button::create(srcPNG_button_square_green,srcPNG_button_square_green_tap,srcPNG_button_square_green,Widget::TextureResType::PLIST);
    _btn->setScale9Enabled(true);
    _btn->setContentSize(Size(179,57));
    _btn->setNormalizedPosition(Vec2(0.5,0.5));
    _btn->setTitleFontName(srcTFF_Roboto_Bold);
    _btn->setTitleFontSize(25);
    _btn->setTitleText("Thiệp bài");
    
    
    this->addChild(_btn);
    
    auto _effect = LayourEffect::createWithSize(_btn->getContentSize()*1.00,EffectType::DYNAMIC);
    _effect->setNormalizedPosition(Vec2(0.5,0.5));
    _effect->changeParticleScale(0.5);
    _btn->addChild(_effect);
    
    
    
    //createTimeLine();
    //createLabelVongChungBai();
    //createCard();
    this->addChild(AnimatedCursor::getInstance(),9999);

    return true;
}

void Demo::createHolylight(Vec2 _pos){
    ParticleSystemQuad* _obj = ParticleSystemQuad::create("Catte/holyLight.plist");
    
    _obj->setScale(0.5);
    _obj->setTotalParticles(15);
    
    _obj->resetSystem();
    
    auto _scaleUp = ScaleTo::create(0.4, 1.5);
    auto _fadeIn = FadeIn::create(0.01);
    auto _spawnOn = Spawn::create(_scaleUp,_fadeIn, NULL);
    
    auto _scaleDown = ScaleTo::create(0.5, 0);
    auto _fadeOut = FadeOut::create(0.5);
    auto _spawnOff = Spawn::create(EaseExponentialOut::create(_scaleDown),_fadeOut, NULL);
    
    auto _rotate = RotateBy::create(2,360);
    auto _remove = RemoveSelf::create();
    
    _obj->runAction(_rotate);
    _obj->runAction(Sequence::create(_spawnOn,DelayTime::create(0.2), _spawnOff,_remove, NULL));
    
    _obj->setPosition(_pos);
    this->addChild(_obj);
}

void Demo::createLabelVongChungBai(){
    
    
    
    imgVongChungBai = ImageView::create("phom_MidTable_NotifyBar_BD.png",Widget::TextureResType::PLIST);
    imgVongChungBai->setNormalizedPosition(Vec2(-0.2,0.5));
    this->addChild(imgVongChungBai,1);
    
    lblVongChungBai = Label::createWithTTF("VÒNG CHƯNG BÀI",srcTFF_UTM_NEO_SANS_INTELBOLD_0 , 25);
    lblVongChungBai->setNormalizedPosition(Vec2(1.2,0.5));
    this->addChild(lblVongChungBai,2);
    
    imgVongChungBai->setOpacity(0);
    lblVongChungBai->setOpacity(0);
    
    auto _fadeIn = FadeIn::create(0.5);
    auto _eraseIn = EaseInOut::create(MoveTo::create(0.5, (Vec2)this->getContentSize()/2 + Vec2(30,0)), 2.5f);
    auto __eraseIn = EaseInOut::create(MoveTo::create(0.5, (Vec2)this->getContentSize()/2- Vec2(30,0)), 2.5f);
    auto _moveToCenter = MoveTo::create(0.3, this->getContentSize()/2);
    
    auto _scaleX = SkewTo::create(0.6, 45,0);
    auto __scaleX = SkewTo::create(0.6, -45,0);
    auto ___scaleX = SkewTo::create(0.3, 0,0);
    
    
    auto _scaleXX = SkewTo::create(0.2, -45,0);
    auto __scaleXX = SkewTo::create(0.2, 45,0);
    auto _eraseOut = EaseInOut::create(MoveBy::create(1, this->getPosition() - Vec2(500,0)),2.5f);
    auto __eraseOut = EaseInOut::create(MoveBy::create(1, this->getPosition() + Vec2(500,0)),2.5f);
    auto _fadeOut = FadeOut::create(0.7);
    
    imgVongChungBai->runAction(Sequence::create(Spawn::create(_fadeIn->clone(),
                                                              _eraseIn,_scaleX->clone(), NULL),
                                                Spawn::create(___scaleX->clone(),_moveToCenter->clone(), NULL),
                                                DelayTime::create(1.5),Sequence::create(
                                                                                        Spawn::create(_eraseOut,
                                                                                                      _fadeOut->clone(),
                                                                                                      _scaleXX->clone(),
                                                                                                      NULL),
                                                                                        RemoveSelf::create(),NULL), nullptr));
    
    lblVongChungBai->runAction(Sequence::create(Spawn::create(_fadeIn->clone(),
                                                              __eraseIn,__scaleX->clone(), NULL),
                                                Spawn::create(___scaleX->clone(),_moveToCenter->clone(), NULL),
                                                DelayTime::create(1.5),Sequence::create(
                                                                                        Spawn::create(__eraseOut,
                                                                                                      _fadeOut->clone(),
                                                                                                      __scaleXX->clone(),
                                                                                                      NULL),
                                                                                        RemoveSelf::create(),NULL), nullptr));
}


void Demo::createTimeLine(){
    auto pTimeLine = ProgressTimer::create( Sprite::create("frame_circle.png"));
    pTimeLine->setVisible(true);
    pTimeLine->setType( ProgressTimer::Type::RADIAL );
    this->addChild(pTimeLine);
    pTimeLine->setPosition(this->getContentSize()/2);
    
    
    float percent = 80;
    pTimeLine->setPercentage(percent);
    pTimeLine->runAction( ProgressFromTo::create(5,100-percent,100));
    
    auto _node = Node::create();
    _node->setAnchorPoint(Vec2(0.5,0.5));
    _node->setPosition(this->getContentSize()/2);
    
    auto _par = ParticleSystemQuad::create("particle_texture.plist");
    _par->setScale(0.5);
    _par->setPosition(0,pTimeLine->getContentSize().height/2-4);
    _par->resetSystem();
    _node->addChild(_par,2);
    
    this->addChild(_node);
    
    _node->setRotation((360 - (pTimeLine->getPercentage()/100 * 360)));
    float deg = _par->getRotation();
    _node->runAction(Sequence::create(RotateBy::create(5, 360-_node->getRotation()),RemoveSelf::create(),NULL));
    
    
    {
        if (SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("BaiCao.plist")){
            
        
       
            auto pTimeLine = ProgressTimer::create( Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("time_banthan2.png")));
            pTimeLine->setVisible(true);
            pTimeLine->setType( ProgressTimer::Type::BAR);
            pTimeLine->setMidpoint(Vec2(0,0));
            pTimeLine->setBarChangeRate( Vec2(1, 0));
            this->addChild(pTimeLine);
            pTimeLine->setPosition(this->getContentSize().width/2,150);
            
            pTimeLine->setPercentage(100);
            pTimeLine->runAction( ProgressFromTo::create(5,100,0));
            
            effect= ParticleSystemQuad::create("particle_pPanelTimeLineEffect.plist");
            effect->setAnchorPoint(Vec2(0.5,0.5));
            effect->setScale(0.7);
            effect->setPosition(pTimeLine->getContentSize().width-5,150-1);
            effect->resetSystem();
            effect->runAction(Sequence::create(MoveBy::create(5, Vec2(-this->getContentSize().width,0)),
                                             RemoveSelf::create(),NULL));
            
            timeElapse = 0;
            this->schedule(schedule_selector(Demo::changeColor), 1/60);
         
            this->addChild(effect);
            
        }
    }
}



void Demo::changeColor(float dt){
    timeElapse+= dt;
    float percent = (timeElapse/5.0f)*255;
    CCLOG("%.2f",percent);
    
    this->effect->setStartColor(Color4F(Color3B(255,MAX(255-percent,50) ,MAX(255-percent,50))));

}

Sprite* Demo::getCard(){
    auto _card = Sprite::createWithSpriteFrameName(srcPNG_cardback_blue);
    auto _K = Sprite::createWithSpriteFrameName(srcPNG_K_co);
    _K->setPosition(_card->getContentSize().width/2,_card->getContentSize().height/2);
    _card->addChild(_K);
    
    return _card;
}

void Demo::createCard(){
    {
        auto _card = Sprite::createWithSpriteFrameName("BG_card.png");
        _card->setPosition(this->getContentSize().width*0.3,this->getContentSize().height/2);
        this->addChild(_card,1);
        auto _effect = LayourEffect::createWithSize(_card->getContentSize(),EffectType::STATIC);
        _card->addChild(_effect);
        
//        auto effect = ParticleSystemQuad::create("Catte/testParticle.plist");
//        effect->setPosition(_card->getPosition());
//        effect->setPosVar(Vec2(_card->getContentSize().width/2,_card->getContentSize().height/2));
//        this->addChild(effect,2);
//        effect->setBlendAdditive(false);
    }
    
    
    {
        auto _card = Sprite::createWithSpriteFrameName("BG_card.png");
        
        //auto _card = Sprite::createWithSpriteFrameName("cardback_blue.png");
        _card->setPosition(this->getContentSize().width*0.7,this->getContentSize().height/2);
        _card->setAnchorPoint(Vec2(0.5,0.5));
        _card->setScale(0.7);
        this->addChild(_card);
        auto _effect = LayourEffect::createWithSize(_card->getContentSize()*1.1,EffectType::DYNAMIC);
        _effect->setPosition(_card->getContentSize()/2);
        _card->addChild(_effect);

    }
    
    {
        auto _card = getCard();
        _card->setPosition(this->getContentSize().width*0.5,this->getContentSize().height*0.3);
        this->addChild(_card);
        _card->setAnchorPoint(Vec2(0,0));
        _card->setScale(0.7);
        
        CCLOG("Card: %.2f %.2f",_card->getAnchorPoint().x,_card->getAnchorPoint().y);
        
        _card->scheduleOnce(schedule_selector(Demo::addEffect), 1);

//        auto _effect = LayourEffect::createWithSize(_card->getContentSize(),EffectType::COMBINE);
//        _card->addChild(_effect);
    }

}

void Demo::addEffect(float dt){
    auto _effect = LayourEffect::createWithSize(this->getContentSize(),EffectType::COMBINE);
    this->addChild(_effect);
    
    CCLOG("Effect: %.2f %.2f",_effect->getAnchorPoint().x,_effect->getAnchorPoint().y);
}

void Demo::callBack(){
    
}

void Demo::processCallback(const cocos2d::network::DownloadTask &task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected){
    
    CCLOG("BytesRecieved: %zd",bytesReceived);
    CCLOG("BytesTotalRecieved: %zd",totalBytesReceived);
    CCLOG("TotalBytesExpected: %zd",totalBytesExpected);
}

void Demo::downloadCalback(const cocos2d::network::DownloadTask &task, std::vector<unsigned char> &data){
    Texture2D* texture = nullptr;
    
    do
    {
        Image img;
        if (!img.initWithImageData(data.data(), data.size()))
        {
            break;
        }
        
        texture = new Texture2D();
        if (!texture->initWithImage(&img))
        {
            break;
        }
        auto sprite = Sprite::createWithTexture(texture);
        this->addChild(sprite);
        sprite->setPosition(Vec2(480,320));
    } while (0);
    CC_SAFE_RELEASE(texture);
}


bool Demo::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    return true;
}

void Demo::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void Demo::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
//    auto _sprite = SpriteEffect::createWithPathAtPos("guc_tung.png", touch->getLocation());
//    
//    this->addChild(_sprite);
    
    auto _card = getCard();
    
//    _card->setScaleX(0);
//    auto _skewX = EaseElasticOut::create(ScaleTo::create(1, 1, 1),0.1);
    
    auto _move = MoveBy::create(1, Vec2(3,0));
    auto _seq = Sequence::create(_move->clone(),_move->reverse(), NULL);
    auto _skewX = EaseElasticOut::create(_seq, 0.1);
    _card->runAction(_skewX);
    
    this->addChild(_card);
    _card->setPosition(touch->getLocation());
    _card->runAction(Sequence::create(DelayTime::create(2),RemoveSelf::create(), NULL));
    
    this->createHolylight(touch->getLocation());
}




void Demo::onExit(){
    Node::onExit();
    
    this->unscheduleUpdate();
}
