//
//  TaiXiuHistoryDialog.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/1/16.
//
//

#include "TaiXiuHistory.hpp"
#include "ResourceNew.h"

static SpriteFrameCache* sprCache = NULL;


bool TaiXiuHistory::init(){
    
    if (!Layer::init()){
        return false;
    }
    
    sprCache = SpriteFrameCache::getInstance();
    initBoard();
    
    _listener = EventListenerTouchOneByOne::create();
    
    _listener->onTouchBegan = CC_CALLBACK_2(TaiXiuHistory::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(TaiXiuHistory::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(TaiXiuHistory::onTouchEnded, this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
    
    for(int i = 0;i<10;i++){
        int _rand = random(0, 100);
        if (_rand < 30){
            addTXHistory(StringUtils::format("%zd",random(100500200, 100500500)), TXHistoryResult::historyTAI, StringUtils::format("%zd",random(1000, 1000)), true);
        }else if (_rand >= 30 && _rand < 60){
            addTXHistory(StringUtils::format("%zd",random(100500200, 100500500)), TXHistoryResult::historyXIU, StringUtils::format("%zd",random(1000, 100000)), false);
        }else{
            addTXHistory(StringUtils::format("%zd",random(100500200, 100500500)), TXHistoryResult::historyXCT, StringUtils::format("%zd",random(1000, 100000000)), true);
        }
    }

    return true;
}



void TaiXiuHistory::initBoard(){
    auto _scaleX = Director::getInstance()->getVisibleSize().width/960;
    auto _scaleY = Director::getInstance()->getVisibleSize().height/640;
    
    _defaultScale = MIN(_scaleY, _scaleX);
    
    _backGround = Layout::create();
    _backGround->setContentSize(this->getContentSize());
    _backGround->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    _backGround->setBackGroundColorOpacity(255/2);
    _backGround->setBackGroundColor(Color3B::BLACK);
    _backGround->setVisible(false);
    this->addChild(_backGround);
    
    _root = ImageView::create(srcPNG_tx_dialog_history,Widget::TextureResType::PLIST);
    _root->setScale9Enabled(true);
    _root->setContentSize(Size(820,470));
    _root->setScale(_defaultScale);
    _root->setPosition(this->getContentSize()/2);
    _root->setVisible(false);
    this->addChild(_root);
    
    auto _btnClose = Button::create(srcPNG_button_circle_red,
                                    srcPNG_button_circle_redtap,
                                    srcPNG_button_circle_red,
                                    Widget::TextureResType::PLIST);
    _btnClose->setAnchorPoint(Vec2(0.5,0.5));
    _btnClose->setScale9Enabled(true);
    _btnClose->setNormalizedPosition(Vec2(1.,1.));
    _btnClose->setTag(1);
    _root->addChild(_btnClose);
    
    _btnClose->addTouchEventListener(CC_CALLBACK_2(TaiXiuHistory::onButtonTouch,this));
    
    auto _X = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_button_icon_cross));
    _X->setNormalizedPosition(Vec2(0.5,0.5));
    _btnClose->addChild(_X);

    
    {
        _historicalData = Node::create();
        _historicalData->setNormalizedPosition(Vec2(0.5,0.5));
        _root->addChild(_historicalData);
        
        auto _sprHistoricalStar = Sprite::createWithSpriteFrameName(srcPNG_tx_dialog_history_empty);
        _sprHistoricalStar->setPosition(Vec2(-4,-55));
        _historicalData->addChild(_sprHistoricalStar);
        
        auto _txtEmptyHistory = Text::create("Không có dữ liệu lịch sử", srcTFF_Roboto_Bold, 25);
        _txtEmptyHistory->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _txtEmptyHistory->setTextHorizontalAlignment(TextHAlignment::CENTER);
        _txtEmptyHistory->setTextVerticalAlignment(TextVAlignment::CENTER);
        _historicalData->addChild(_txtEmptyHistory);
        
        auto _line = ImageView::create(srcPNG_tx_dialog_history_line,Widget::TextureResType::PLIST);
        _line->setPosition(Vec2(0,130));
        _historicalData->addChild(_line);

        
        _historicalData->setVisible(false);
    }
    
    
    _listHistory = ListView::create();
    _listHistory->setBackGroundImageScale9Enabled(true);
    _listHistory->setBackGroundImage(srcPNG_tx_dialog_history, Widget::TextureResType::PLIST);
    _listHistory->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _listHistory->setContentSize(Size(820,370));
    _listHistory->setNormalizedPosition(Vec2(0.5,0.3830));
    _listHistory->setItemsMargin(3);
    _listHistory->setBounceEnabled(true);
    _listHistory->setScrollBarEnabled(false);
    _listHistory->setClippingEnabled(true);
    _listHistory->setVisible(true);
    
    _root->addChild(_listHistory);
    
     wList = _listHistory->getContentSize().width;
     hList = _listHistory->getContentSize().height;
    
    auto _layout = Layout::create();
    _layout->setContentSize(Size(wList,80));
    _layout->setNormalizedPosition(Vec2(0.,0.7833));
    _root->addChild(_layout);
    
    auto _color = Color4B(Color3B::YELLOW);
    
    auto _phien = Text::create("Phiên", srcTFF_Roboto_Bold, 25);
    _phien->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _phien->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _phien->setTextVerticalAlignment(TextVAlignment::CENTER);
    _phien->setNormalizedPosition(Vec2(0.125,0.5));
    _phien->setTextColor(_color);
    _layout->addChild(_phien);
    
    auto _cuadat = Text::create("Cửa đặt", srcTFF_Roboto_Bold, 25);
    _cuadat->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _cuadat->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _cuadat->setTextVerticalAlignment(TextVAlignment::CENTER);
    _cuadat->setNormalizedPosition(Vec2(0.375,0.5));
    _cuadat->setTextColor(_color);
    _layout->addChild(_cuadat);
    
    auto _dat = Text::create("Đặt", srcTFF_Roboto_Bold, 25);
    _dat->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _dat->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _dat->setTextVerticalAlignment(TextVAlignment::CENTER);
    _dat->setNormalizedPosition(Vec2(0.625,0.5));
    _dat->setTextColor(_color);
    _layout->addChild(_dat);
    
    auto _ketqua = Text::create("Kết quả", srcTFF_Roboto_Bold, 25);
    _ketqua->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _ketqua->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _ketqua->setTextVerticalAlignment(TextVAlignment::CENTER);
    _ketqua->setNormalizedPosition(Vec2(0.875,0.5));
    _ketqua->setTextColor(_color);
    _layout->addChild(_ketqua);
    

    
    setEnableHistoricalData(true);
}

void TaiXiuHistory::addTXHistory(std::string _txtPhien, TXHistoryResult _result, std::string _totalMoney, bool _win){
    auto _layout = Layout::create();
    _layout->setContentSize(Size(wList,50));
    
    
    auto _phien = Text::create(_txtPhien, srcTFF_Roboto_Bold, 25);
    _phien->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _phien->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _phien->setTextVerticalAlignment(TextVAlignment::CENTER);
    _phien->setNormalizedPosition(Vec2(0.125,0.5));
    _layout->addChild(_phien);
    
    ImageView* _cuadat = NULL;
    switch (_result) {
        case historyTAI:
            _cuadat = ImageView::create(srcPNG_tx_results_tai,Widget::TextureResType::PLIST);
            break;
        case historyXIU:
            _cuadat = ImageView::create(srcPNG_tx_results_xiu,Widget::TextureResType::PLIST);
            break;
        case historyXCT:
            _cuadat = ImageView::create(srcPNG_tx_results_bo3,Widget::TextureResType::PLIST);
            break;
            
        default:
            break;
    }
    
    _cuadat->setNormalizedPosition(Vec2(0.375,0.5));
    _layout->addChild(_cuadat);
    
    
    auto _txtXiuBet = Text::create(_totalMoney, srcTFF_Roboto_Bold, 25);
    _txtXiuBet->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _txtXiuBet->setTextHorizontalAlignment(TextHAlignment::LEFT);
    _txtXiuBet->setTextVerticalAlignment(TextVAlignment::CENTER);
    _txtXiuBet->setNormalizedPosition(Vec2(0.58,0.5));
    _txtXiuBet->setColor(Color3B(255, 165, 0));

    auto _sprCoin = Sprite::createWithSpriteFrameName(srcPNG_lw_iconCoin1);
    _sprCoin->setScale(0.35);
    _sprCoin->setPosition(Vec2(-25,16.98));
    _txtXiuBet->addChild(_sprCoin);
   // _txtXiuBet->setPositionX(_txtXiuBet->getPositionX() + _sprCoin->getContentSize().width*0.35/2);
    _layout->addChild(_txtXiuBet);
    
    
    if (_win){
        auto _ketqua = ImageView::create(srcPNG_tx_history_win,Widget::TextureResType::PLIST);
        _ketqua->setNormalizedPosition(Vec2(0.875,0.5));
        _layout->addChild(_ketqua);

    }else{
        auto _ketqua = ImageView::create(srcPNG_tx_history_lose,Widget::TextureResType::PLIST);
        _ketqua->setNormalizedPosition(Vec2(0.875,0.5));
        _layout->addChild(_ketqua);
    }
    
    auto _line = ImageView::create(srcPNG_tx_dialog_history_line,Widget::TextureResType::PLIST);
    _line->setPositionX(_layout->getContentSize().width/2);
    _line->setPositionY(-2);
    _layout->addChild(_line);
    
    _listHistory->pushBackCustomItem(_layout);
    
    setEnableHistoricalData(false);
}

void TaiXiuHistory::openHistory(){
    _listener->setSwallowTouches(true);
    _backGround->setVisible(true);
    _root->setVisible(true);
    _root->setScale(0.2);

    auto _scale = EaseElasticOut::create(ScaleTo::create(1, _defaultScale),0.5);
    
    _root->runAction(_scale);
}

void TaiXiuHistory::closeHistory(){
    _backGround->setVisible(false);
    
    auto _callBackClose = CallFuncN::create(CC_CALLBACK_0(TaiXiuHistory::callBackClose, this));
    
    auto _scale = EaseElasticOut::create(ScaleTo::create(1, 0),0.5);
    _root->runAction(Sequence::create(_scale,_callBackClose, NULL));
}

void TaiXiuHistory::callBackClose(){
    _listener->setSwallowTouches(false);
    _root->setVisible(false);
}

void TaiXiuHistory::setEnableHistoricalData(bool _enable){
    if (_enable){
        _listHistory->setVisible(false);
        _historicalData->setVisible(true);
    }else{
        _listHistory->setVisible(true);
        _historicalData->setVisible(false);
    }
}

bool TaiXiuHistory::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    return true;
}

void TaiXiuHistory::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void TaiXiuHistory::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}


void TaiXiuHistory::onButtonTouch(cocos2d::Ref *pSender, Widget::TouchEventType type){
    auto _button = static_cast<Button*>(pSender);
    
    if (_button == NULL) return;
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            if (_button->getTag() == 1){
                closeHistory();
            }
            break;
        }
            
        default:
            break;
    }
}
