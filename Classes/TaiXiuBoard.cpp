//
//  TaiXiuBoard.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/2/16.
//
//

#include "TaiXiuBoard.hpp"
#include "ResourceNew.h"


static bool isResourceLoad = false;
static SpriteFrameCache* sprCache;

void TaiXiuBoard::loadResource(){
    if (!isResourceLoad){
        sprCache = SpriteFrameCache::getInstance();
        sprCache->addSpriteFramesWithFile(srcPLIST_tai_xiu);
        sprCache->addSpriteFramesWithFile(srcPLIST_Buttton);
        sprCache->addSpriteFramesWithFile(srcPLIST_LuckyWheel_small);

        isResourceLoad = true;
    }
}


bool TaiXiuBoard::init(){
    
    if (!Node::init()){
        return false;
    }
    
    drawBoard();
    
    return true;
}


void TaiXiuBoard::drawBoard(){
    
    auto _scaleX = Director::getInstance()->getVisibleSize().width/960;
    auto _scaleY = Director::getInstance()->getVisibleSize().height/640;
    
    _defaultScale = MIN(_scaleX,_scaleY);
    auto _dialog = ImageView::create(srcPNG_tx_dialog_nen,Widget::TextureResType::PLIST);
    _dialog->setScale9Enabled(true);
    _dialog->setContentSize(Size(700,460));
    _dialog->setScale(_defaultScale);
    _dialog->setPosition(this->getContentSize()/2);
    _dialog->setTag(kTagDialog);
    this->addChild(_dialog);
    
    auto _tenGame = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_tengame_01));
    _tenGame->setAnchorPoint(Vec2(0.5,0));
    _tenGame->setNormalizedPosition(Vec2(0.5,1));
    _tenGame->setTag(kTagTenGame);
    _dialog->addChild(_tenGame);
    createAnimationForTenGame();
    
    auto _btnHistory = Button::create(srcPNG_tx_history_button,
                                      srcPNG_tx_history_button,
                                      srcPNG_tx_history_button,
                                      Widget::TextureResType::PLIST);
    _btnHistory->setAnchorPoint(Vec2(0,0));
    _btnHistory->setScale9Enabled(true);
    _btnHistory->setNormalizedPosition(Vec2(0.0443,0.8809));
    _btnHistory->setTag(kTagBtnHistory);
    _dialog->addChild(_btnHistory);
    
    auto _btnThele = Button::create(srcPNG_tx_thele_button,
                                      srcPNG_tx_thele_button,
                                      srcPNG_tx_thele_button,
                                      Widget::TextureResType::PLIST);
    _btnThele->setAnchorPoint(Vec2(1,1));
    _btnThele->setScale9Enabled(true);
    _btnThele->setNormalizedPosition(Vec2(0.9557,0.9831));
    _btnThele->setTag(kTagBtnThele);
    _dialog->addChild(_btnThele);
    
    auto _btnClose = Button::create(srcPNG_button_circle_red,
                                      srcPNG_button_circle_redtap,
                                      srcPNG_button_circle_red,
                                      Widget::TextureResType::PLIST);
    _btnClose->setAnchorPoint(Vec2(0.5,0.5));
    _btnClose->setScale9Enabled(true);
    _btnClose->setNormalizedPosition(Vec2(0.9986,0.9957));
    _btnClose->setTag(kTagBtnClose);
    _dialog->addChild(_btnClose);
    
    auto _X = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_button_icon_cross));
    _X->setNormalizedPosition(Vec2(0.5,0.5));
    _btnClose->addChild(_X);

    auto _sprUserPlayingXiu = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_playinguser));
    _sprUserPlayingXiu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _sprUserPlayingXiu->setNormalizedPosition(Vec2(0.08,0.7761));
    _sprUserPlayingXiu->setTag(34);
    _dialog->addChild(_sprUserPlayingXiu);
    
    auto _txtUserPlayingXiu = Text::create("100.000", srcTFF_Roboto_Bold, 20);
    _txtUserPlayingXiu->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _txtUserPlayingXiu->setTextHorizontalAlignment(TextHAlignment::LEFT);
    _txtUserPlayingXiu->setTextVerticalAlignment(TextVAlignment::CENTER);
    _txtUserPlayingXiu->setContentSize(Size(120,23));
    _txtUserPlayingXiu->setOpacity(0.8*255);
    _txtUserPlayingXiu->setNormalizedPosition(Vec2(1.2941,0.5));
    _txtUserPlayingXiu->setTag(kTagTextXiuBettor);
    _sprUserPlayingXiu->addChild(_txtUserPlayingXiu);
    
    auto _sprUserPlayingTai = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_playinguser));
    _sprUserPlayingTai->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _sprUserPlayingTai->setNormalizedPosition(Vec2(0.7357,0.7761));
    _sprUserPlayingTai->setTag(52);
    _dialog->addChild(_sprUserPlayingTai);
    
    auto _txtUserPlayingTai = Text::create("100.000", srcTFF_Roboto_Bold, 20);
    _txtUserPlayingTai->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _txtUserPlayingTai->setTextHorizontalAlignment(TextHAlignment::LEFT);
    _txtUserPlayingTai->setTextVerticalAlignment(TextVAlignment::CENTER);
    _txtUserPlayingTai->setContentSize(Size(120,23));
    _txtUserPlayingTai->setOpacity(0.8*255);
    _txtUserPlayingTai->setNormalizedPosition(Vec2(1.2941,0.5));
    _txtUserPlayingTai->setTag(kTagTextTaiBettor);
    _sprUserPlayingTai->addChild(_txtUserPlayingTai);
    
    auto _sprXiNgauCenterBox = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_frame_xingau));
    _sprXiNgauCenterBox->setNormalizedPosition(Vec2(0.5,0.563));
    _sprXiNgauCenterBox->setTag(kTagTimeTable);
    _dialog->addChild(_sprXiNgauCenterBox);
    
    auto _sprXiu = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_Xiu));
    _sprXiu->setNormalizedPosition(Vec2(-0.4277,0.6324));
    _sprXiu->setTag(kTagSprXiu);
    _sprXiNgauCenterBox->addChild(_sprXiu);
    
    {
        auto _txtXiu = Text::create("4-10", srcTFF_Roboto_Bold, 25);
        _txtXiu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _txtXiu->setTextHorizontalAlignment(TextHAlignment::CENTER);
        _txtXiu->setTextVerticalAlignment(TextVAlignment::CENTER);
        _txtXiu->setNormalizedPosition(Vec2(-0.4244,0.3193));
        _txtXiu->setTag(41);
        _sprXiNgauCenterBox->addChild(_txtXiu);
        
        auto _txtXiuBet = Text::create("100.000", srcTFF_Roboto_Bold, 25);
        _txtXiuBet->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _txtXiuBet->setTextHorizontalAlignment(TextHAlignment::CENTER);
        _txtXiuBet->setTextVerticalAlignment(TextVAlignment::CENTER);
        _txtXiuBet->setPosition(Vec2(28,-26.1));
        _txtXiuBet->setColor(Color3B(255, 250, 142));
        _txtXiuBet->setTag(kTagTextXiuBet);
        _txtXiu->addChild(_txtXiuBet);
        
        auto _sprCoin = Sprite::createWithSpriteFrameName(srcPNG_lw_iconCoin1);
        _sprCoin->setScale(0.35);
        _sprCoin->setPosition(Vec2(-18,16.98));
        _txtXiuBet->addChild(_sprCoin);
        
        _txtXiuBet->setPositionX(_txtXiuBet->getPositionX() + _sprCoin->getContentSize().width*0.35/2);
        log("%f : %f", _sprCoin->getContentSize().width,_sprCoin->getContentSize().width/2);
    }
    
    
    auto _sprTai = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_Tai));
    _sprTai->setNormalizedPosition(Vec2(1.4216,0.6407));
    _sprTai->setTag(kTagSprTai);
    _sprXiNgauCenterBox->addChild(_sprTai);
    
    {
        auto _txtTai = Text::create("11-17", srcTFF_Roboto_Bold, 25);
        _txtTai->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _txtTai->setTextHorizontalAlignment(TextHAlignment::CENTER);
        _txtTai->setTextVerticalAlignment(TextVAlignment::CENTER);
        _txtTai->setNormalizedPosition(Vec2(1.4748,0.3193));
        _txtTai->setTag(38);
        _sprXiNgauCenterBox->addChild(_txtTai);
        
        auto _txtTaiBet = Text::create("500.000", srcTFF_Roboto_Bold, 25);
        _txtTaiBet->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _txtTaiBet->setTextHorizontalAlignment(TextHAlignment::CENTER);
        _txtTaiBet->setTextVerticalAlignment(TextVAlignment::CENTER);
        _txtTaiBet->setPosition(Vec2(28,-26.1));
        _txtTaiBet->setColor(Color3B(255, 250, 142));
        _txtTaiBet->setTag(kTagTextTaiBet);
        _txtTai->addChild(_txtTaiBet);
        
        auto _sprCoin = Sprite::createWithSpriteFrameName(srcPNG_lw_iconCoin1);
        _sprCoin->setScale(0.35);
        _sprCoin->setPosition(Vec2(-18,16.98));
        _txtTaiBet->addChild(_sprCoin);
        
        _txtTaiBet->setPositionX(_txtTaiBet->getPositionX() + _sprCoin->getContentSize().width*0.35/2);

    }
    
    
    auto _loadingBar = ProgressTimer::create(Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_frame_xingau_countdown)));
    _loadingBar->setType(ProgressTimer::Type::RADIAL);
    _loadingBar->setAnchorPoint(Vec2(0.5,0.5));
    _loadingBar->setContentSize(Size(234,234));
    _loadingBar->setNormalizedPosition(Vec2(0.50,0.53));
    _loadingBar->setPercentage(50);
    _loadingBar->setVisible(false);
    _loadingBar->setTag(kTagTimeline);
    _sprXiNgauCenterBox->addChild(_loadingBar);
    
    auto _sprTimeEffect = Sprite::createWithSpriteFrame(sprCache->getSpriteFrameByName(srcPNG_tx_frame_xingau_countdown_light));
    _sprTimeEffect->setNormalizedPosition(Vec2(0.5,0.5));
    _sprTimeEffect->setRotation(45);
    _sprTimeEffect->setTag(kTagTimeEffect);
    _loadingBar->addChild(_sprTimeEffect);
    
    auto _particleEffect = ParticleSystemQuad::create("TaiXiu/defaultParticle.plist");
    _sprTimeEffect->addChild(_particleEffect);
    _particleEffect->setNormalizedPosition(Vec2(0.2736,0.8590));
    _particleEffect->setTag(1);
    _particleEffect->stopSystem();
    
    
    auto _txtClock = Text::create("00:30", srcTFF_Roboto_Bold, 60);
    _txtClock->setAnchorPoint(Vec2(0.5,0.5));
    _txtClock->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _txtClock->setTextVerticalAlignment(TextVAlignment::CENTER);
    _txtClock->setNormalizedPosition(Vec2(0.50,0.50));
    _txtClock->setTag(kTagTextClock);
    _sprXiNgauCenterBox->addChild(_txtClock);
    
    //auto _txtSubMoney = Text::create("-10.000", srcTFF_Roboto_Bold, 35);
    auto _txtSubMoney = Label::createWithBMFont(srcFNT_Roboto_CoinLose,"-10.000");
    _txtSubMoney->setAnchorPoint(Vec2(0.5,0.5));
    _txtSubMoney->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    _txtSubMoney->setNormalizedPosition(Vec2(0.50,0.744));
    _txtSubMoney->setTag(kTagTextSubMoney);
    _sprXiNgauCenterBox->addChild(_txtSubMoney);
    
    auto _txtAddMoney = Label::createWithBMFont(srcFNT_Roboto_CoinWin,"+50.000");
    //auto _txtAddMoney = Text::create("+50.000", srcTFF_Roboto_Bold, 35);
    _txtAddMoney->setAnchorPoint(Vec2(0.5,0.5));
    _txtAddMoney->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    _txtAddMoney->setNormalizedPosition(Vec2(0.50,0.7458));
    _txtAddMoney->setTag(kTagTextAddMoney);
    _sprXiNgauCenterBox->addChild(_txtAddMoney);
    
    auto _txtTaiXiuResult = Text::create("17", srcTFF_Roboto_Bold, 25);
    _txtTaiXiuResult->setAnchorPoint(Vec2(0.5,0.5));
    _txtTaiXiuResult->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _txtTaiXiuResult->setTextVerticalAlignment(TextVAlignment::CENTER);
    _txtTaiXiuResult->setTextColor(Color4B::YELLOW);
    _txtTaiXiuResult->setNormalizedPosition(Vec2(0.50,0.1891));
    _txtTaiXiuResult->setTag(kTagTextTaiXiuResult);
    _sprXiNgauCenterBox->addChild(_txtTaiXiuResult);
    
    
    auto _txtTaiXiuSpecialResult = Text::create("Bộ ba đồng nhất", srcTFF_Roboto_Bold, 20);
    _txtTaiXiuSpecialResult->setAnchorPoint(Vec2(0.5,0.5));
    _txtTaiXiuSpecialResult->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _txtTaiXiuSpecialResult->setTextVerticalAlignment(TextVAlignment::CENTER);
    _txtTaiXiuSpecialResult->setTextColor(Color4B::YELLOW);
    _txtTaiXiuSpecialResult->setNormalizedPosition(Vec2(0.50,0.7605));
    _txtTaiXiuSpecialResult->setTag(kTagTextSpecialResult);
    _sprXiNgauCenterBox->addChild(_txtTaiXiuSpecialResult);
    
    {
        auto _txtMoneyBet = Text::create("Tiền Cược:", srcTFF_Roboto_Bold, 25);
        _txtMoneyBet->setAnchorPoint(Vec2(0.0,0.5));
        _txtMoneyBet->setTextHorizontalAlignment(TextHAlignment::LEFT);
        _txtMoneyBet->setTextVerticalAlignment(TextVAlignment::CENTER);
        _txtMoneyBet->setNormalizedPosition(Vec2(-0.7796,-0.1407));
        _txtMoneyBet->setTag(43);
        _sprXiNgauCenterBox->addChild(_txtMoneyBet);

        auto _txtUserBet = Button::create(srcPNG_button_square_red_disabled,
                                         srcPNG_button_square_red_disabled,
                                         srcPNG_button_square_red_disabled,
                                         Widget::TextureResType::PLIST);
        _txtUserBet->setAnchorPoint(Vec2(0.5,0.5));
        _txtMoneyBet->setTouchEnabled(false);
        _txtUserBet->setScale9Enabled(true);
        _txtUserBet->setContentSize(Size(200,55));
        _txtUserBet->setNormalizedPosition(Vec2(0.2198,-0.1407));
        _txtUserBet->setTitleFontName(srcTFF_Roboto_Bold);
        _txtUserBet->setTitleFontSize(30);
        _txtUserBet->setTitleText("0");
        _txtUserBet->setTag(kTabTextUserBet);
        _sprXiNgauCenterBox->addChild(_txtUserBet);
        
        auto _btnBet = Button::create(srcPNG_button_square_blue,
                                          srcPNG_button_square_blue_tap,
                                          srcPNG_button_square_blue_disabled,
                                          Widget::TextureResType::PLIST);
        _btnBet->setAnchorPoint(Vec2(0.5,0.5));
        _btnBet->setTouchEnabled(true);
        _btnBet->setScale9Enabled(true);
        _btnBet->setContentSize(Size(120,45));
        _btnBet->setNormalizedPosition(Vec2(3.3913,0.5));
        _btnBet->setTitleFontName(srcTFF_Roboto_Bold);
        _btnBet->setTitleFontSize(25);
        _btnBet->setTitleText("Cược");
        _btnBet->setTag(kTagBtnBet);
        _txtMoneyBet->addChild(_btnBet);
        
        auto _btnRemove= Button::create(srcPNG_tx_button_xoa,
                                      srcPNG_tx_button_xoa_tab,
                                      srcPNG_tx_button_xoa_disable,
                                      Widget::TextureResType::PLIST);
        _btnRemove->setAnchorPoint(Vec2(0.5,0.5));
        _btnRemove->setTouchEnabled(true);
        _btnRemove->setScale9Enabled(true);
        _btnRemove->setContentSize(Size(120,45));
        _btnRemove->setNormalizedPosition(Vec2(4.5124,0.5));
        _btnRemove->setTitleFontName(srcTFF_Roboto_Bold);
        _btnRemove->setTitleFontSize(25);
        _btnRemove->setTitleText("Xóa");
        _btnRemove->setTag(kTagBtnRemove);
        _txtMoneyBet->addChild(_btnRemove);
    }
    
    
    
    {
        auto _node = Node::create();
        _node->setNormalizedPosition(Vec2(0.0303,0.1015));
        _node->setScaleX(0.99);
        _node->setTag(54);
        
        auto _btn1k= Button::create(srcPNG_button_square_cyan,
                                        srcPNG_button_square_cyan_tap,
                                        srcPNG_button_square_cyan_disabled,
                                        Widget::TextureResType::PLIST);
        _btn1k->setAnchorPoint(Vec2(0.5,0.5));
        _btn1k->setTouchEnabled(true);
        _btn1k->setScale9Enabled(true);
        _btn1k->setContentSize(Size(140,40));
        _btn1k->setPosition(Vec2(92.86,0));
        _btn1k->setTitleFontName(srcTFF_Roboto_Bold);
        _btn1k->setTitleFontSize(25);
        _btn1k->setTitleText("1.000");
        _btn1k->setTag(kTagBtn1);
        _node->addChild(_btn1k);
        
        auto _btn5k= Button::create(srcPNG_button_square_cyan,
                                    srcPNG_button_square_cyan_tap,
                                    srcPNG_button_square_cyan_disabled,
                                    Widget::TextureResType::PLIST);
        _btn5k->setAnchorPoint(Vec2(0.5,0.5));
        _btn5k->setTouchEnabled(true);
        _btn5k->setScale9Enabled(true);
        _btn5k->setContentSize(Size(140,40));
        _btn5k->setPosition(Vec2(253.18,0));
        _btn5k->setTitleFontName(srcTFF_Roboto_Bold);
        _btn5k->setTitleFontSize(25);
        _btn5k->setTitleText("5.000");
        _btn5k->setTag(kTagBtn2);
        _node->addChild(_btn5k);
        
        auto _btn10k= Button::create(srcPNG_button_square_cyan,
                                    srcPNG_button_square_cyan_tap,
                                    srcPNG_button_square_cyan_disabled,
                                    Widget::TextureResType::PLIST);
        _btn10k->setAnchorPoint(Vec2(0.5,0.5));
        _btn10k->setTouchEnabled(true);
        _btn10k->setScale9Enabled(true);
        _btn10k->setContentSize(Size(140,40));
        _btn10k->setPosition(Vec2(412.51,0));
        _btn10k->setTitleFontName(srcTFF_Roboto_Bold);
        _btn10k->setTitleFontSize(25);
        _btn10k->setTitleText("10.000");
        _btn10k->setTag(kTagBtn3);
        _node->addChild(_btn10k);
        
        auto _btn50k= Button::create(srcPNG_button_square_cyan,
                                     srcPNG_button_square_cyan_tap,
                                     srcPNG_button_square_cyan_disabled,
                                     Widget::TextureResType::PLIST);
        _btn50k->setAnchorPoint(Vec2(0.5,0.5));
        _btn50k->setTouchEnabled(true);
        _btn50k->setScale9Enabled(true);
        _btn50k->setContentSize(Size(140,40));
        _btn50k->setPosition(Vec2(570.78,0));
        _btn50k->setTitleFontName(srcTFF_Roboto_Bold);
        _btn50k->setTitleFontSize(25);
        _btn50k->setTitleText("50.000");
        _btn50k->setTag(kTagBtn4);
        _node->addChild(_btn50k);
        
        _dialog->addChild(_node);
    }
    
    
    auto _listViewHistory = ListView::create();
    _listViewHistory->setAnchorPoint(Vec2(0.5,0.5));
    _listViewHistory->setDirection(ScrollView::Direction::HORIZONTAL);
    _listViewHistory->setBounceEnabled(false);
    _listViewHistory->setScrollBarEnabled(false);
    _listViewHistory->setItemsMargin(10);
    _listViewHistory->setContentSize(Size(370,50));
    _listViewHistory->setNormalizedPosition(Vec2(0.5,0.9250));
    _listViewHistory->setTag(KTagListView);

    _dialog->addChild(_listViewHistory);
    
    for(int i = 0;i < 10;i++){
        if (random(0, 100) < 50 ){
            auto _img = ImageView::create(srcPNG_tx_results_tai,Widget::TextureResType::PLIST);
            _listViewHistory->pushBackCustomItem(_img);

        }else{
            auto _img = ImageView::create(srcPNG_tx_results_xiu,Widget::TextureResType::PLIST);
            _listViewHistory->pushBackCustomItem(_img);

        }
    }
    _listViewHistory->forceDoLayout();
}


void TaiXiuBoard::createAnimationForTenGame(){
    Vector<SpriteFrame*> vecFrame;
    
    for(int i = 1; i < 5; i++){
        std::string _path = StringUtils::format("tx_tengame_0%zd.png",i);
        vecFrame.pushBack(sprCache->getSpriteFrameByName(_path));
    }
    
    _aniTenGame = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(vecFrame,0.25)));
    _aniTenGame->retain();
}













