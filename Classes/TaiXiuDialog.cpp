//
//  TaiXiuDialog.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/31/16.
//
//

#include "TaiXiuDialog.hpp"
#include "ResourceNew.h"

#define MAX_TIME 25

static TaiXiuDialog* TAI_XIU = NULL;

static const char* srcPNG_tx_result_bo3 = "TaiXiu/tx_results_bo3.png";



TaiXiuDialog* TaiXiuDialog::getInstance(){
    if (TAI_XIU == NULL){
        TAI_XIU = TaiXiuDialog::create();
        TAI_XIU->retain();
        TAI_XIU->setTag(1);
    }
    return TAI_XIU;
}

bool TaiXiuDialog::init(){
    
    if (!Layer::init()){
        return false;
    }
    setisPause(false);
    _boardState = TXBoardState::NEXT_TIME;
    
    _containerXiNgau = NULL;
    _containerXiNgauCursor = NULL;
    _resultOnCursor = NULL;
    
    _taiBetCash = 0;
    _xiuBetCash = 0;
    _betCash = 0;
    _taiBetCashShow = 0;
    _xiuBetCashShow = 0;
    _betCashShow = 0;
    _curBetCash = 0;
    _curTaiBetCash = 0;
    _curXiuBetCash = 0;
    _time = 9999;
    _nextTime = -1;
    _isAttractSuccessfully = false;
    _effectFocusLastResult = NULL;


    
    _root = TaiXiuBoard::create();
    _root->setAnchorPoint(Vec2(0.5,0.5));
    
    _backGround = Layout::create();
    _backGround->setContentSize(this->getContentSize());
    _backGround->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    _backGround->setBackGroundColorOpacity(255/2);
    _backGround->setBackGroundColor(Color3B::BLACK);
    _backGround->setVisible(false);
    this->addChild(_backGround);
    
    
    this->addChild(_root);
    _root->setVisible(false);
    
    _historyDialog = TaiXiuHistory::create();
    _historyDialog->retain();
    this->addChild(_historyDialog);
    
    
    curTaiXiuStatus = TaiXiuStatus::select_NONE;
    
    createTouchListener();
    storeChild(_root);
    reSettingVar();
    buttonSetting();
    setEnabledButton(TaiXiuButton::btnAll,false);

    startNextTime(5);
    
    addHistoryResult(TaiXiuResultType::TAI);

    return true;
}

void TaiXiuDialog::drawDialog(){
    
}

void TaiXiuDialog::onEnter(){
    Node::onEnter();    
    
    if (_boardState == TXBoardState::XINGAU_ACTION){
        float _per = -_time / 6;
        testCallXiNgau(0);
        callBackXiNgau(_per*(float)2);
    }
}

void TaiXiuDialog::onExit(){
    Node::onExit();
    setisPause(true);
    callBackInvisible();
}

void TaiXiuDialog::resetTimer(){
    if (_nextTime > 0 && _boardState == TXBoardState::NEXT_TIME){
        resetTimeLine();
    }
}

void TaiXiuDialog::resetTimeLine(){
    float per = (float)_nextTime/(float)this->_defaultNextTime*100;
    
    ptTimeLine->setPercentage(per);
    
    sprTimeEffect->setRotation(getExactRotation(100-per));
    
    auto _callXiNgau = CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackTimeLine, this));
    auto _sed = Sequence::create(ProgressFromTo::create(_nextTime,100-per, 100),
                                 _callXiNgau, NULL);
    
    ptTimeLine->runAction(_sed);
    sprTimeEffect->runAction( RotateBy::create(_nextTime, 405-(sprTimeEffect->getRotation())));
}

void TaiXiuDialog::testAddHistory(float dt){
    int i = random(0,100);
    if (i < 30){
        addHistoryResult(TaiXiuResultType::TAI);
    }else if (i >=30 && i < 60){
        addHistoryResult(TaiXiuResultType::XIU);
    }else{
        addHistoryResult(TaiXiuResultType::XCT);
    }
}

void TaiXiuDialog::createTouchListener(){
    _listener = EventListenerTouchOneByOne::create();
    
    _listener->onTouchBegan = CC_CALLBACK_2(TaiXiuDialog::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(TaiXiuDialog::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(TaiXiuDialog::onTouchEnded, this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}

void TaiXiuDialog::openTXDialog(){
    this->setVisible(true);
    _backGround->setVisible(true);

    _listener->setSwallowTouches(true);
    
    _root->setVisible(true);
    
    _root->setScale(0.1);
    _root->setPosition(AnimatedCursor::getInstance()->getPosition());

    auto _scale = ScaleTo::create(1, 1);
    auto _move = EaseElasticOut::create(MoveTo::create(1, this->getContentSize()/2),0.5);
    auto _ani = Spawn::create(_move, EaseElasticOut::create(_scale, 0.5),
                              NULL);
    
   
    _root->runAction(Sequence::create(_ani,
                                      CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackDialogAppear, this)), NULL));
    
    _close = false;
    sprTenGame->runAction(_root->_aniTenGame);
    this->enableAttractUserForSelecting(true);

}

void TaiXiuDialog::closeTXDialog(){
     _backGround->setVisible(false);
    auto _scale = ScaleTo::create(1, 0.0);
    auto _move = EaseElasticOut::create(MoveTo::create(1, AnimatedCursor::getInstance()->getPosition()),1);
    auto _ani = Spawn::create(_move, EaseElasticOut::create(_scale, 0.5),
                              NULL);
    auto _callBackInvisible = CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackInvisible, this));
    
    _root->runAction(Sequence::create(_ani, _callBackInvisible, NULL));
    sprTenGame->stopAllActions();
    
    auto _effect_win_coin = (Node*)sprTimeTable->getChildByTag(9999); //Tag of effect win coin if it exits
    
    if (_effect_win_coin != NULL){
        sprTimeTable->removeChild(_effect_win_coin, true);
    }
    
    _effectFocusLastResult->stopSystem();
}


void TaiXiuDialog::storeChild(cocos2d::Node *_node){
    dialog = _node->getChildByTag<ImageView*>(kTagDialog);
    
    listViewResult = dialog->getChildByTag<ListView*>(KTagListView);
    
    sprTenGame = dialog->getChildByTag<Sprite*>(kTagTenGame);
    
    btnHistory = dialog->getChildByTag<Button*>(kTagBtnHistory);
    btnClose = dialog->getChildByTag<Button*>(kTagBtnClose);
    btnRule = dialog->getChildByTag<Button*>(kTagBtnThele);
    
    sprTimeTable = dialog->getChildByTag<Sprite*>(kTagTimeTable);
    ptTimeLine = sprTimeTable->getChildByTag<ProgressTimer*>(kTagTimeline);
    sprTimeEffect = ptTimeLine->getChildByTag<Sprite*>(kTagTimeEffect);
    parTimeEffect = sprTimeEffect->getChildByTag<ParticleSystemQuad*>(1);
    
    sprTai = sprTimeTable
    ->getChildByTag<Sprite*>(kTagSprTai);
    
    sprXiu = sprTimeTable
    ->getChildByTag<Sprite*>(kTagSprXiu);
    
    txtuserBet = sprTimeTable
    ->getChildByTag<Button*>(kTabTextUserBet);
    
    txtXiuBet = sprTimeTable
    ->getChildByTag<Text*>(41)
    ->getChildByTag<Text*>(kTagTextXiuBet);
    
    txtTaiBet = sprTimeTable
    ->getChildByTag<Text*>(38)
    ->getChildByTag<Text*>(kTagTextTaiBet);
    
    txtXiuBettor = dialog->getChildByTag<Sprite*>(34)
    ->getChildByTag<Button*>(kTagTextXiuBettor);
    
    txtTaiBettor = dialog->getChildByTag<Sprite*>(52)
    ->getChildByTag<Button*>(kTagTextTaiBettor);
    
    txtClock = sprTimeTable
    ->getChildByTag<Text*>(kTagTextClock);
    
    txtSubMoney = sprTimeTable
    ->getChildByTag<Label*>(kTagTextSubMoney);
    
    txtAddMoney = sprTimeTable
    ->getChildByTag<Label*>(kTagTextAddMoney);
    
    txtSpecialResult = sprTimeTable
    ->getChildByTag<Text*>(kTagTextSpecialResult);
    
    txtTXResult = sprTimeTable
    ->getChildByTag<Text*>(kTagTextTaiXiuResult);
    
    btn1 = dialog
    ->getChildByTag<Node*>(54)
    ->getChildByTag<Button*>(kTagBtn1);
    btn1->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    
    btn2 = dialog
    ->getChildByTag<Node*>(54)
    ->getChildByTag<Button*>(kTagBtn2);
    btn2->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    
    btn3 = dialog
    ->getChildByTag<Node*>(54)
    ->getChildByTag<Button*>(kTagBtn3);
    btn3->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    
    btn4 = dialog
    ->getChildByTag<Node*>(54)
    ->getChildByTag<Button*>(kTagBtn4);
    btn4->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    
    btnBet = sprTimeTable
    ->getChildByTag<Text*>(43)
    ->getChildByTag<Button*>(kTagBtnBet);
    btnBet->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    
    btnRemove = sprTimeTable
    ->getChildByTag<Text*>(43)
    ->getChildByTag<Button*>(kTagBtnRemove);
    btnRemove->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    
    txtCursorTime = AnimatedCursor::getInstance()
    ->getChildByTag<Button*>(1)
    ->getChildByTag<Text*>(1);
}

void TaiXiuDialog::reSettingVar(){
    txtTXResult->setVisible(false);
    txtAddMoney->setVisible(false);
    txtSubMoney->setVisible(false);
    txtSpecialResult->setVisible(false);
    txtClock->setVisible(false);
    
    listViewResult->removeAllItems();
    listViewResult->setScrollBarEnabled(false);
    
    txtTaiBet->setString("0");
    txtXiuBet->setString("0");
}

void TaiXiuDialog::startTimer(float dt){
    _boardState = TXBoardState::COUNT_DOWN;
    _time = MAX_TIME;
    //ptTimeLine->setVisible(true);
    this->showTxtResult(false);
    testCallXiNgau(0);
    showTxtClock(true);
    //setEnabledButton(TaiXiuButton::btnAll, true);
    resetStatus();
    
    //ptTimeLine->setPercentage(0);
    
    //sprTimeEffect->setRotation(getExactRotation(0));
    
    //auto _callXiNgau = CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackTimeLine, this));
//    auto _sed = Sequence::create(ProgressFromTo::create(MAX_TIME,0, 100),
//                                _callXiNgau, NULL);
    
    //ptTimeLine->runAction(_sed);
    //sprTimeEffect->runAction( RotateBy::create(MAX_TIME, 405-(sprTimeEffect->getRotation())));
}

void TaiXiuDialog::startNextTime(float dt){
    _boardState = TXBoardState::NEXT_TIME;
    _nextTime = dt;
    _defaultNextTime = dt;
    
    ptTimeLine->setVisible(true);
    this->showTxtResult(false);
    testCallXiNgau(0);
    showTxtClockNextTime(true);
    resetStatus();
    
    ptTimeLine->setPercentage(0);
    
    sprTimeEffect->setRotation(getExactRotation(0));
    
    auto _callXiNgau = CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackTimeLine, this));
    auto _sed = Sequence::create(ProgressFromTo::create(_nextTime,0, 100),
                                 _callXiNgau, NULL);
    
    ptTimeLine->runAction(_sed);
    sprTimeEffect->runAction( RotateBy::create(_nextTime, 405-(sprTimeEffect->getRotation())));
}

float TaiXiuDialog::getExactRotation(float _per){
    float deg = _per/100 *360;
    
    while (deg>=360) {
        deg-= 360;
    }
    
    return deg + 45;
}

void TaiXiuDialog::buttonSetting(){
    btnClose->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    btnHistory->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    btn1->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    btn2->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    btn3->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    btn4->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    btnBet->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    btnRemove->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
}

void TaiXiuDialog::addHistoryResultToListView(ImageView* _img){
    listViewResult->addChild(_img);
    listViewResult->forceDoLayout();
    if (listViewResult->getItems().size() > 10){
        listViewResult->removeItem(0);
    }
    
    ssize_t _size = listViewResult->getItems().size();
    
    if (_size == 1){
        float _factor = listViewResult->getContentSize().width/_img->getContentSize().width;
        listViewResult->setAnchorPoint(Vec2(0.5/_factor,0.5));
    }else if (_size > 1){
        float _w = _img->getContentSize().width*_size + 10*(_size-1);
        float _factor = listViewResult->getContentSize().width/_w;
        listViewResult->setAnchorPoint(Vec2(0.5/_factor,0.5));
    }
    
    listViewResult->setNormalizedPosition(Vec2(0.5,listViewResult->getNormalizedPosition().y));
}

void TaiXiuDialog::setFocus(){
    auto _lastResult = listViewResult->getItems().back();
    
    if (_lastResult != NULL){
        
        if (_effectFocusLastResult == NULL){
            _effectFocusLastResult = ParticleSystemQuad::create("TaiXiu/focusLastResult.plist");
            _effectFocusLastResult->retain();
        }
        
        if (_effectFocusLastResult->getParent() != NULL){
            _effectFocusLastResult->removeFromParent();
        }
        _lastResult->addChild(_effectFocusLastResult);
        _effectFocusLastResult->setPosition(_lastResult->getContentSize()/2);
        _effectFocusLastResult->setPositionY(_effectFocusLastResult->getPositionY()+1.5);
        _effectFocusLastResult->resetSystem();

        
    }
}

void TaiXiuDialog::addHistoryResult(TaiXiuResultType _type){
    switch (_type) {
        case TAI:
            addHistoryResultToListView(ImageView::create(srcPNG_tx_results_tai,Widget::TextureResType::PLIST));
//            _historyDialog->addTXHiàstory(StringUtils::format("%zd",random(100000, 200000)), TXHistoryResult::historyTAI, std::string _totalMoney, bool _win)
            break;
            
        case XIU:
            addHistoryResultToListView(ImageView::create(srcPNG_tx_results_xiu,Widget::TextureResType::PLIST));
            break;
        case XCT:
            addHistoryResultToListView(ImageView::create(srcPNG_tx_result_bo3));
            break;

        default:
            break;
    }
}

void TaiXiuDialog::setEnabledButton(TaiXiuButton _typeBtn, bool _enable){
    switch (_typeBtn) {
        case TaiXiuButton::btn1:
        {
            btn1->setEnabled(_enable);
            if (!_enable){
                btn1->setTitleColor(Color3B::GRAY);
            }else{
                btn1->setTitleColor(Color3B::WHITE);
            }
            break;
        }
        case TaiXiuButton::btn2 :
        {
            btn2->setEnabled(_enable);
            if (!_enable){
                btn2->setTitleColor(Color3B::GRAY);
            }else{
                btn2->setTitleColor(Color3B::WHITE);
            }
            break;
        }
        case TaiXiuButton::btn3 :
        {
            btn3->setEnabled(_enable);
            if (!_enable){
                btn3->setTitleColor(Color3B::GRAY);
            }else{
                btn3->setTitleColor(Color3B::WHITE);
            }
            break;
        }
        case TaiXiuButton::btn4 :
        {
            btn4->setEnabled(_enable);
            if (!_enable){
                btn4->setTitleColor(Color3B::GRAY);
            }else{
                btn4->setTitleColor(Color3B::WHITE);
            }
            break;
        }
        case TaiXiuButton::btnAll :{
            setEnabledButton(TaiXiuButton::btn1, _enable);
            setEnabledButton(TaiXiuButton::btn2, _enable);
            setEnabledButton(TaiXiuButton::btn3, _enable);
            setEnabledButton(TaiXiuButton::btn4, _enable);

            btnBet->setEnabled(_enable);
            btnRemove->setEnabled(_enable);
            
            if (!_enable){
                btnBet->setTitleColor(Color3B::GRAY);
                btnRemove->setTitleColor(Color3B::GRAY);
            }else{
                btnBet->setTitleColor(Color3B::WHITE);
                btnRemove->setTitleColor(Color3B::WHITE);
            }
            break;
        }

        default:
            break;
    }
}

void TaiXiuDialog::resetStatus(){
    txtXiuBet->setString("0");
    txtTaiBet->setString("0");
    txtuserBet->setTitleText("0");
    _curBetCash = _betCash;
    _curTaiBetCash = _curTaiBetCash;
    _curXiuBetCash = _curXiuBetCash;
    _betCash = 0;
    _taiBetCash = 0;
    _xiuBetCash = 0;
}

void TaiXiuDialog::callBackTouchBtn(cocos2d::Ref *pSender, ui::Widget::TouchEventType type){
    auto _button = static_cast<Button*>(pSender);
    
    if (_button == NULL || _close){
        return;
    }
    
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            switch (_button->getTag()) {
                case kTagBtnClose:
                    closeTXDialog();
                    _close = true;
                    break;
                    
                case kTagBtn1:
                    setBet(1000);
                    log("BTN 1 OK");
                    break;
                    
                    
                case kTagBtn2:
                    setBet(5000);
                    log("BTN 2 OK");
                    break;
                    
                    
                case kTagBtn3:
                    setBet(10000);
                    log("BTN 3 OK");
                    break;
                    
                    
                case kTagBtn4:
                    setBet(50000);
                    log("BTN 4 OK");
                    break;
                    
                case kTagBtnBet:
                    confirmBet();
                    log("BTN BET OK");
                    break;

                case kTagBtnRemove:
                    _curBetCash = _betCash;
                    _betCash = 0;
                    break;
                    
                case kTagBtnHistory:{
                    this->_historyDialog->openHistory();
                    break;}

                    
                default:
                    break;
            }
            break;
        }
            
        default:
            break;
    }
}

void TaiXiuDialog::setBet(float _value){
    _betCash+= _value;
    _curBetCash = _value;
    txtuserBet->setTitleText(StringUtils::format("%zd",_betCashShow));
}

void TaiXiuDialog::confirmBet(){
    if (_betCash <= 0){
        return;
    }
    
    switch (curTaiXiuStatus) {
        case select_TAI:
        {
            _taiBetCash+= _betCash;
            _curTaiBetCash = _betCash;
            txtTaiBet->setString(StringUtils::format("%zd",_taiBetCashShow));
            auto wave = AnimatedCoinWave::createAnimatedCoinWave(getCountCoinToShow(_betCash),txtuserBet->getPosition(),sprTai->getPosition());
            wave->SetCoinType(CoinType::GOLD);
            wave->addCoinCallBack(CC_CALLBACK_0(TaiXiuDialog::callBackCoinWaveTai, this));
            wave->setDuration(1);
            wave->setScale(0.5);
            wave->start();
            sprTimeTable->addChild(wave,1);
            
        }
            break;
        
        case select_XIU:
        {
            _xiuBetCash+= _betCash;
            _curXiuBetCash = _betCash;
            txtXiuBet->setString(StringUtils::format("%zd",_xiuBetCashShow));
            
            auto wave = AnimatedCoinWave::createAnimatedCoinWave(getCountCoinToShow(_betCash),txtuserBet->getPosition(),sprXiu->getPosition());
            wave->SetCoinType(CoinType::GOLD);
            wave->addCoinCallBack(CC_CALLBACK_0(TaiXiuDialog::callBackCoinWaveXiu, this));
            wave->setDuration(1);
            wave->setScale(0.5);
            wave->start();
            sprTimeTable->addChild(wave,1);
        }
            break;
            
        default:
            break;
    }
    
    _curBetCash = _betCash;
    _betCash = 0;
}

void TaiXiuDialog::callBackCoinWaveTai(){
    switch (curTaiXiuStatus) {
        case select_TAI:
        {
            sprTai->stopAllActions();
            sprTai->setScale(MAX((float)sprTai->getScale()-0.03,(float)0.6));
            sprTai->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1.1),1));
        }
            break;
          default:
            break;
    }
}

void TaiXiuDialog::callBackCoinWaveXiu(){
    switch (curTaiXiuStatus) {
        case select_XIU:
        {
            sprXiu->stopAllActions();
            sprXiu->setScale(MAX((float)sprXiu->getScale()-0.03,(float)0.6));
            sprXiu->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1.1),1));
        }
            break;
            
        default:
            break;
    }
}


int TaiXiuDialog::getCountCoinToShow(int _cash){
    return MAX(_cash/20000, 1);
}

void TaiXiuDialog::showCashResult(bool _enable){
    int _resultCash = 0;
    
    if (!_enable){
        auto _cloneAnimationText = (Label*)sprTimeTable->getChildByTag(989);
        if (_cloneAnimationText != NULL){
            _cloneAnimationText->stopAllActions();
            _cloneAnimationText->removeFromParent();
        }
        return;
    }
    
    txtSpecialResult->setVisible(false);
    
    switch (curTaiXiuResult) {
        case TAI:
            _resultCash = _taiBetCash-_xiuBetCash;
            break;
        
        case XIU:
            _resultCash = _xiuBetCash - _taiBetCash;
            break;
        
        case XCT:
            _resultCash = -_xiuBetCash - _taiBetCash;
            break;
        default:
            break;
    }
    
    if (_resultCash > 0){
        txtAddMoney->setString(StringUtils::format("+%zd",_resultCash));
        this->castAnimationForLabel(txtAddMoney);
        
        //Them hieu ung particle tiền nếu thắng.
        auto _effect_win_coin = CreatePhomBigWinEffect(_resultCash);
        _effect_win_coin->setNormalizedPosition(Vec2(0.5,0.5));
        sprTimeTable->addChild(_effect_win_coin, 9999, 9999);
    }else if (_resultCash < 0){
        txtSubMoney->setString(StringUtils::format("-%zd",-_resultCash));
        this->castAnimationForLabel(txtSubMoney);
    }
}

void TaiXiuDialog::castAnimationForLabel(cocos2d::Label *_lable){
    
    auto _clone = Label::createWithBMFont(_lable->getBMFontFilePath(),_lable->getString());
    _clone->setAnchorPoint(Vec2(0.5,0.5));
    _clone->setAlignment(TextHAlignment::CENTER,TextVAlignment::CENTER);
    _clone->setNormalizedPosition(Vec2(0.50,0.7458));
    sprTimeTable->addChild(_clone,9999,989);
    
    _clone->setScale(0.2);
    
    auto _scale = ScaleTo::create(0.5, 1);
    auto _move = MoveBy::create(3, Vec2(0, 50));
    
    auto _spawn = Spawn::create(EaseElasticOut::create(_scale, 0.5),_move, NULL);
    _clone->runAction(_spawn);
}

void TaiXiuDialog::callBackInvisible(){
    _listener->setSwallowTouches(false);
    
//    if (_containerXiNgau != NULL){
//        _containerXiNgau->removeFromParent();
//        _containerXiNgau = NULL;
//    }
    
    this->setVisible(false);
   
//    Director::getInstance()->getRunningScene()->removeChild(this);
}

void TaiXiuDialog::callBackDialogAppear(){
    parTimeEffect->resetSystem();
    setFocus();
}

void TaiXiuDialog::callBackTimeLine(){
    ptTimeLine->setVisible(false);
}

void TaiXiuDialog::callBackXiNgau(float _timeShowResult){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/baucua/diceroll.mp3");
    
    _res1 = random(1, 1);
    _res2 = random(1, 2);
    _res3 = random(1, 1);
    
//    _res1 = random(1, 1);
//    _res2 = random(1, 1);
//    _res3 = random(1, 1);
    
    //_containerXiNgau = XiNgauController::create3XiNgau(_res1,_res2,_res3,CC_CALLBACK_0(TaiXiuDialog::testCallBackResult, this));
    _containerXiNgau = XiNgauController::create3XiNgau(_timeShowResult,_res1,_res2,_res3,NULL);

    _containerXiNgau->setScale(0.75);
    sprTimeTable->addChild(_containerXiNgau);
    _containerXiNgau->setNormalizedPosition(Vec2(0.5,0.5));
    
    _containerXiNgauCursor = XiNgauController::create3XiNgau(_timeShowResult,_res1,_res2,_res3,NULL);
    AnimatedCursor::getInstance()->get_BackGroundCursor()->addChild(_containerXiNgauCursor);
    _containerXiNgauCursor->setScale(0.45);
//    _containerXiNgauCursor->setPosition(AnimatedCursor::getInstance()->get_Cursor()->getContentSize()/2 + Size(0,AnimatedCursor::getInstance()->get_Cursor()->getContentSize().height));
    
    _containerXiNgauCursor->setPosition(AnimatedCursor::getInstance()->get_Cursor()->getContentSize()/2);
    
}

void TaiXiuDialog::testCallXiNgau(float dt){
    if (_containerXiNgau != NULL){
        _containerXiNgau->removeFromParent();
        _containerXiNgau = NULL;
    }
    
    
    if (_containerXiNgauCursor != NULL){
        _containerXiNgauCursor->removeFromParent();
        _containerXiNgauCursor = NULL;
    }
    
    if (_resultOnCursor != NULL){
        _resultOnCursor->removeFromParent();
        _resultOnCursor = NULL;
    }
}


void TaiXiuDialog::showTxtResult(bool _enable){
    if (_enable){
        int _result = _res1+_res2+_res3;
        
        txtTXResult->setVisible(true);
        txtTXResult->setString(StringUtils::format("%zd",_result));
        
        txtTXResult->setScale(0.2);
        auto _scale = ScaleTo::create(1, 1);
        auto _ease = EaseElasticOut::create(_scale, 0.5);
        txtTXResult->runAction(_ease);
        
        {//If has special result : bo 3 dong nhat - show result
            if ((_res1 == _res2) && (_res2 == _res3)){
                txtSpecialResult->setVisible(true);
                txtSpecialResult->setScale(0.2);
                auto _scale = ScaleTo::create(1, 1);
                auto _ease = EaseElasticOut::create(_scale, 0.1);
                txtSpecialResult->runAction(_ease);
            }

        }
        
        if ((_res1 == _res2) && (_res1 == _res3)){
            curTaiXiuResult = TaiXiuResultType::XCT;
            createResultOnCursor(TaiXiuResultType::XCT);
            addHistoryResult(TaiXiuResultType::XCT);
        }else if (_result >= 4 && _result <= 10){
            curTaiXiuResult = TaiXiuResultType::XIU;
            addHistoryResult(TaiXiuResultType::XIU);
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_XIU,true);
            createResultOnCursor(TaiXiuResultType::XIU);
        }else if (_result >= 11 && _result <= 17){
            curTaiXiuResult = TaiXiuResultType::TAI;
            addHistoryResult(TaiXiuResultType::TAI);
            createResultOnCursor(TaiXiuResultType::TAI);
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_TAI,true);
        }

    }else{
        txtTXResult->setVisible(false);

        if ((_res1 == _res2) && (_res2 == _res3)){
            txtSpecialResult->setVisible(false);
        }
    }
    
}

void TaiXiuDialog::createResultOnCursor(TaiXiuResultType _status){
    
    switch (_status) {
        case TAI:{
            _resultOnCursor = ImageView::create(srcPNG_tx_Tai_tap,Widget::TextureResType::PLIST);
            _resultOnCursor->setScale(0.35);
            break;}
            
        case XIU:{
            _resultOnCursor = ImageView::create(srcPNG_tx_Xiu_tap,Widget::TextureResType::PLIST);
            _resultOnCursor->setScale(0.35);
            break;}
        
        case XCT:
            _resultOnCursor = ImageView::create(srcPNG_tx_results_bo3,Widget::TextureResType::PLIST);
            break;
            
        default:
            break;
    }
    
    _containerXiNgauCursor->removeAllChildren();
    AnimatedCursor::getInstance()->get_BackGroundCursor()->addChild(_resultOnCursor);
    _resultOnCursor->setPosition(_containerXiNgauCursor->getPosition());
    _resultOnCursor->setScaleX(_resultOnCursor->getScaleX()* (float)AnimatedCursor::getInstance()->_cursorSide);
}

void TaiXiuDialog::showTxtClock(bool _enable){
    if (_enable){
        txtClock->setVisible(true);
        
        if (_time>= 10){
            txtClock->setString(getTimeClock(_time));
            txtCursorTime->setString(getTimeClock(_time));
            txtCursorTime->setColor(Color3B::GREEN);
            txtClock->setColor(Color3B::WHITE);
        }else if (_time >=0 && _time<10){
            txtClock->setColor(Color3B::RED);
            txtCursorTime->setColor(Color3B(255,150,55) );
            txtClock->setString(getTimeClock(_time));
            txtCursorTime->setString(getTimeClock(_time));
            if (_time == 0){
                
            }
        }else{
            txtClock->setString("00:00");
        }
    }else{
        txtClock->setVisible(false);
        //txtCursorTime->setString("Kết Quả");
        txtCursorTime->setString("");
    }
}

void TaiXiuDialog::showTxtClockNextTime(bool _enable){
    if (_enable){
        txtClock->setVisible(true);
        
        if (_nextTime>= 10){
            txtClock->setString(StringUtils::format("00:%zd",_nextTime));
            txtCursorTime->setString(StringUtils::format("00:%zd",_nextTime));
            txtCursorTime->setColor(Color3B::GREEN);
        }else if (_nextTime >=0 && _nextTime<10){
            txtClock->setColor(Color3B::RED);
            txtCursorTime->setColor(Color3B(255,150,55) );
            txtClock->setString(StringUtils::format("00:0%zd",_nextTime));
            txtCursorTime->setString(StringUtils::format("00:0%zd",_nextTime));
        }else{
            txtClock->setString("00:00");
        }
    }else{
        txtClock->setVisible(false);
        //txtCursorTime->setString("Kết Quả");
        txtCursorTime->setString("");
    }
}

std::string TaiXiuDialog::getTimeClock(int _timeClock){
    
    std::string tempMin = "";
    std::string tempSec = "";
    
    int min = 0;
    int sec = _timeClock;
    
    while (sec > 59) {
        min++;
        sec-= 60;
    }
    
    if (min >= 0){
        tempMin = StringUtils::format("%zd",min);
        tempSec = StringUtils::format("%zd",sec);
        
        if (tempMin.length() == 1){
            tempMin = "0" + tempMin;
        }
        
        if (tempSec.length() == 1){
            tempSec = "0" + tempSec;
        }
    }
    

    return tempMin + ":" + tempSec;
}


void TaiXiuDialog::clock(float dt){
    //if (!txtClock->isVisible()) return;
    
    _time--;
    
    if (_boardState == TXBoardState::NEXT_TIME){
        _nextTime--;
    }
    if (_time == 1){
        AnimatedCursor::getInstance()->showBoardResult(true);
        AnimatedCursor::getInstance()->setSleepingTime(1000);
    }
    
    if (_time == 0){
        curTaiXiuStatus = TaiXiuStatus::select_NONE;
        this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_TAI, false);
        this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_XIU, false);
        
        setEnabledButton(TaiXiuButton::btnAll,false);
        this->enableAttractUserForSelecting(false);
    }
    
    if (_time < 0 && _time >= -1){
         _boardState = TXBoardState::XINGAU_ACTION;
        showTxtClock(false);
        callBackXiNgau(2);
    }else if (_time >= 0){
        showTxtClock(true);
    }
    if (_time == -6){
        _boardState = TXBoardState::RESULT;
        this->showTxtResult(true);
        setFocus();
    }
    
    if (_time == -8){
        showCashResult(true);
    }
    
    if (_time == -10){
        showCashResult(false);
        this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_TAI, false);
        this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_XIU, false);
        this->enableAttractUserForSelecting(true);
        
        AnimatedCursor::getInstance()->showBoardResult(false);
        AnimatedCursor::getInstance()->setSleepingTime(1);
        
        startNextTime(5);
        //startTimer(0);
    }
    
    
    if (_nextTime>=0){
        showTxtClockNextTime(true);
    }
    
    if (_nextTime == -1){
        startTimer(0);
        _nextTime--;
    }
}

void TaiXiuDialog::showTxt(std::string _s){
    auto _lbl = Label::createWithTTF(_s, srcTFF_Roboto_Bold, 20);
    
    _lbl->setNormalizedPosition(Vec2(0.5,0.2));
    
    this->addChild(_lbl,99999);
    
    _lbl->runAction(Sequence::create(MoveBy::create(3, Vec2(0,100)),RemoveSelf::create(), NULL));
}

static float _speedReduction = 0.1; ///Giảm 5% tiền per frame

void TaiXiuDialog::miliClock(float dt){
    if (_betCashShow < _betCash){
        _betCashShow= MIN(_betCash, _betCashShow + (_speedReduction*_curBetCash));
        txtuserBet->setTitleText(StringUtils::format("%zd",_betCashShow));
    }else if (_betCashShow > _betCash){
        _betCashShow= MAX(_betCash, _betCashShow - (_speedReduction*_curBetCash));
        txtuserBet->setTitleText(StringUtils::format("%zd",_betCashShow));
    }
    
    if (_taiBetCashShow < _taiBetCash) {
        _taiBetCashShow = MIN(_taiBetCash, _taiBetCashShow + (_speedReduction*_curTaiBetCash));
        txtTaiBet->setString(StringUtils::format("%zd",_taiBetCashShow));
    }else if (_taiBetCashShow > _taiBetCash){
        _taiBetCashShow = MAX(_taiBetCash, _taiBetCashShow - (_speedReduction*_curTaiBetCash));
        txtTaiBet->setString(StringUtils::format("%zd",_taiBetCashShow));
    }
    
    if (_xiuBetCashShow < _xiuBetCash) {
        _xiuBetCashShow = MIN(_xiuBetCash, _xiuBetCashShow + (_speedReduction*_curXiuBetCash));
        txtXiuBet->setString(StringUtils::format("%zd",_xiuBetCashShow));
    }else if (_xiuBetCashShow > _xiuBetCash){
        _xiuBetCashShow = MAX(_xiuBetCash, _xiuBetCashShow - (_speedReduction*_curXiuBetCash));
        txtXiuBet->setString(StringUtils::format("%zd",_xiuBetCashShow));

    }
    
}

bool TaiXiuDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    return true;
}

void TaiXiuDialog::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void TaiXiuDialog::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    if (_time <= 0) return;
    
    if ( utils::getCascadeBoundingBox(sprTai).containsPoint(touch->getLocation())){
        if (curTaiXiuStatus == TaiXiuStatus::select_TAI) return;
        curTaiXiuStatus = TaiXiuStatus::select_TAI;
        createEffectOnClickTX(curTaiXiuStatus);
    }else if (utils::getCascadeBoundingBox(sprXiu).containsPoint(touch->getLocation())){
        if (curTaiXiuStatus == TaiXiuStatus::select_XIU) return;
        curTaiXiuStatus = TaiXiuStatus::select_XIU;
        createEffectOnClickTX(curTaiXiuStatus);
    }
    
}

void TaiXiuDialog::createEffectOnClickTX(TaiXiuStatus _status){
    if (_time <=0) return;
    
    setEnabledButton(TaiXiuButton::btnAll, true);

    
    switch (curTaiXiuStatus) {
        case select_TAI:{
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_TAI,true);
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_XIU,false);

            break;
        }
            
        case select_XIU:{
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_XIU,true);
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_TAI,false);
            break;
        }
        default:
            break;
    }
}

void TaiXiuDialog::ShowBtnTaiXiuEffect(TaiXiuStatus _status, bool _enable){
    enableAttractUserForSelecting(false);
    
    switch (_status) {
        case select_TAI:{
            if (_enable){
                auto _scale = ScaleTo::create(1, 1.1);
                sprTai->runAction(EaseElasticOut::create(_scale, 0.5));
                sprTai->setSpriteFrame(srcPNG_tx_Tai_tap);
            }else{
                auto _scale = ScaleTo::create(1, 1);
                sprTai->runAction(EaseElasticOut::create(_scale, 0.5));
                sprTai->setSpriteFrame(srcPNG_tx_Tai);
            }
            
            break;
        }
            
        case select_XIU:{
            if (_enable){
                auto _scale = ScaleTo::create(1, 1.1);
                sprXiu->runAction(EaseElasticOut::create(_scale, 0.5));
                sprXiu->setSpriteFrame(srcPNG_tx_Xiu_tap);
            }else{
                auto _scale = ScaleTo::create(1, 1);
                sprXiu->runAction(EaseElasticOut::create(_scale, 0.5));
                sprXiu->setSpriteFrame(srcPNG_tx_Xiu);
            }
            
            break;
        }
        default:
            break;
    }
}

Node* TaiXiuDialog::CreatePhomBigWinEffect(int cash){
    Node* _node = Node::create();
    
    auto effect = ParticleSystemQuad::create("phomwinbig.plist");
    
    int _max = MIN(500, cash/500);
    effect->setSpeed(500);
    effect->setTotalParticles(_max);
    effect->setDuration(0.5);
    effect->setPosition(_node->getContentSize()/2);
    effect->setAutoRemoveOnFinish(true);
    effect->resetSystem();
    
    auto lightEffect = ParticleSystemQuad::create("phomwin_effect.plist");
    lightEffect->setPosition(_node->getContentSize()/2);
    lightEffect->setAutoRemoveOnFinish(true);
    lightEffect->resetSystem();
    
    _node->addChild(effect,1);
    _node->addChild(lightEffect,0);
    
    return _node;
}

void TaiXiuDialog::enableAttractUserForSelecting(bool _enable){
    return;
    if (_enable){
        if (curTaiXiuStatus == TaiXiuStatus::select_NONE && !_isAttractSuccessfully){
            _isAttractSuccessfully = true;
            
            sprTai->setScale(1);
            sprXiu->setScale(1);
            
            auto _scaleDown = ScaleTo::create(1.5, 0.9);
            auto _scaleDefault = ScaleTo::create(1.5, 1);
            auto _scaleUp = ScaleTo::create(1.5, 1.1);
            
            auto _sed1 = Sequence::create(_scaleDown->clone(),_scaleDefault->clone(),_scaleUp->clone(),_scaleDefault->clone(), NULL);
            auto _sed2 = Sequence::create(_scaleUp->clone(),_scaleDefault->clone(),_scaleDown->clone(),_scaleDefault->clone(), NULL);
            
            auto _repeat1 = RepeatForever::create(_sed1);
            auto _repeat2 = RepeatForever::create(_sed2);
            
            
            sprTai->runAction(_repeat1);
            sprXiu->runAction(_repeat2);
        }
    }else{
        if (_isAttractSuccessfully){
            sprXiu->stopAllActions();
            sprTai->stopAllActions();
            sprTai->setScale(1);
            sprXiu->setScale(1);
        }
    }
    
}



