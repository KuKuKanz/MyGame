//
//  TaiXiuDialog.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/31/16.
//
//

#include "TaiXiuDialog.hpp"
#include "ResourceNew.h"

#define MAX_TIME 5

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
    
    this->schedule(schedule_selector(TaiXiuDialog::clock), 1);
    _containerXiNgau = NULL;

    
    _root = TaiXiuBoard::create();
    _root->setAnchorPoint(Vec2(0.5,0.5));
    this->addChild(_root);
    _root->setVisible(false);
    
    
    curTaiXiuStatus = TaiXiuStatus::select_NONE;
    
    createTouchListener();
    storeChild(_root);
    reSettingVar();
    buttonSetting();
    setEnabledButton(TaiXiuButton::btnAll,false);

    startTimer(0);

    return true;
}

void TaiXiuDialog::onExit(){
    Node::onExit();
    
    sprTimeEffect->pause();
    ptTimeLine->pause();
}
void TaiXiuDialog::drawDialog(){
    
}

void TaiXiuDialog::resetTimer(){
    this->schedule(schedule_selector(TaiXiuDialog::clock), 1);

    resetTimeLine();
}

void TaiXiuDialog::resetTimeLine(){
    float per = _time/MAX_TIME*100;
    
    ptTimeLine->setPercentage(per);
    
    sprTimeEffect->setRotation(getExactRotation(per));
    
    auto _callXiNgau = CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackTimeLine, this));
    auto _sed = Sequence::create(ProgressFromTo::create(_time,per, 100),
                                 _callXiNgau, NULL);
    
    ptTimeLine->runAction(_sed);
    sprTimeEffect->runAction( RotateBy::create(_time, 405-(sprTimeEffect->getRotation())));

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
    if (Director::getInstance()->getRunningScene()->getChildByTag<TaiXiuDialog*>(1) == NULL){
        Director::getInstance()->getRunningScene()->addChild(this);
    }
    this->setVisible(true);
    //schedule(schedule_selector(TaiXiuDialog::testAddHistory), 1);

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
}

void TaiXiuDialog::closeTXDialog(){
    //ptTimeLine->stopAllActions();
    //ptTimeLine->setVisible(false);
    //sprTimeEffect->stopAllActions();
    
    auto _scale = ScaleTo::create(1, 0.0);
    auto _move = EaseElasticIn::create(MoveTo::create(1, AnimatedCursor::getInstance()->getPosition()),0.5);
    auto _ani = Spawn::create(_move, EaseElasticIn::create(_scale, 0.5),
                              NULL);
    auto _callBackInvisible = CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackInvisible, this));
    
    _root->runAction(Sequence::create(_ani, _callBackInvisible, NULL));
    //sprTenGame->stopAllActions();
    //resetStatus();
}


void TaiXiuDialog::storeChild(cocos2d::Node *_node){
    dialog = _node->getChildByTag<ImageView*>(kTagDialog);
    
    listViewResult = dialog->getChildByTag<ListView*>(KTagListView);
    
    sprTenGame = dialog->getChildByTag<Sprite*>(kTagTenGame);
    
    btnHistory = dialog->getChildByTag<Button*>(kTagBtnHistory);
    btnClose = dialog->getChildByTag<Button*>(kTagBtnClose);
    
    sprTimeTable = dialog->getChildByTag<Sprite*>(kTagTimeTable);
    ptTimeLine = sprTimeTable->getChildByTag<ProgressTimer*>(kTagTimeline);
    sprTimeEffect = ptTimeLine->getChildByTag<Sprite*>(kTagTimeEffect);
    parTimeEffect = sprTimeEffect->getChildByTag<ParticleSystemQuad*>(1);
    
    sprTai = sprTimeTable
    ->getChildByTag<Sprite*>(kTagSprTai);
    
    sprXiu = sprTimeTable
    ->getChildByTag<Sprite*>(kTagSprXiu);
    
    txtuserBet = dialog
    ->getChildByTag<Text*>(43)
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
    ->getChildByTag<Text*>(kTagTextSubMoney);
    
    txtAddMoney = sprTimeTable
    ->getChildByTag<Text*>(kTagTextAddMoney);
    
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
    
    btnBet = dialog
    ->getChildByTag<Sprite*>(43)
    ->getChildByTag<Button*>(kTagBtnBet);
    btnBet->addTouchEventListener(CC_CALLBACK_2(TaiXiuDialog::callBackTouchBtn, this));
    
    btnRemove = dialog
    ->getChildByTag<Sprite*>(43)
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
}

void TaiXiuDialog::startTimer(float dt){
    _time = MAX_TIME;

    ptTimeLine->setVisible(true);
    this->showTxtResult(false);
    testCallXiNgau(0);
    showTxtClock(true);
    //setEnabledButton(TaiXiuButton::btnAll, true);
    resetStatus();
    txtClock->setColor(Color3B::WHITE);
    
    ptTimeLine->setPercentage(0);
    
    sprTimeEffect->setRotation(getExactRotation(0));
    
    auto _callXiNgau = CallFuncN::create(CC_CALLBACK_0(TaiXiuDialog::callBackTimeLine, this));
    auto _sed = Sequence::create(ProgressFromTo::create(MAX_TIME,0, 100),
                                _callXiNgau, NULL);
    
    ptTimeLine->runAction(_sed);
    sprTimeEffect->runAction( RotateBy::create(MAX_TIME, 405-(sprTimeEffect->getRotation())));
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
}

void TaiXiuDialog::addHistoryResultToListView(ImageView* _img){
    listViewResult->addChild(_img);
    listViewResult->forceDoLayout();
    if (listViewResult->getItems().size() > 9){
        listViewResult->removeItem(0);
    }
    
}

void TaiXiuDialog::addHistoryResult(TaiXiuResultType _type){
    switch (_type) {
        case TAI:
            addHistoryResultToListView(ImageView::create(srcPNG_tx_results_tai,Widget::TextureResType::PLIST));
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
            btn1->setEnabled(_enable);
            break;
        case TaiXiuButton::btn2 :
            btn2->setEnabled(_enable);
            break;
        case TaiXiuButton::btn3 :
            btn3->setEnabled(_enable);
            break;
        case TaiXiuButton::btn4 :
            btn4->setEnabled(_enable);
            break;
        case TaiXiuButton::btnAll :{
            btn1->setEnabled(_enable);
            btn2->setEnabled(_enable);
            btn3->setEnabled(_enable);
            btn4->setEnabled(_enable);
            btnBet->setEnabled(_enable);
            btnRemove->setEnabled(_enable);
            break;
        }

        default:
            break;
    }
}

void TaiXiuDialog::resetStatus(){
    curTaiXiuStatus = TaiXiuStatus::select_NONE;
    this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_TAI, false);
    this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_XIU, false);
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
                    log("BTN 1 OK");
                    break;
                    
                    
                case kTagBtn2:
                    log("BTN 2 OK");
                    break;
                    
                    
                case kTagBtn3:
                    log("BTN 3 OK");
                    break;
                    
                    
                case kTagBtn4:
                    log("BTN 4 OK");
                    break;
                    
                case kTagBtnBet:
                    log("BTN BET OK");
                    break;

                case kTagBtnRemove:
                    log("BTN REMOVE OK");
                    break;

                    
                default:
                    break;
            }
            break;
        }
            
        default:
            break;
    }
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
}

void TaiXiuDialog::callBackTimeLine(){
    ptTimeLine->setVisible(false);
}

void TaiXiuDialog::callBackXiNgau(){
    _res1 = random(1, 6);
    _res2 = random(1, 6);
    _res3 = random(1, 6);
    
//    _res1 = random(6, 6);
//    _res2 = random(6, 6);
//    _res3 = random(6, 6);
    
    _containerXiNgau = XiNgauController::create3XiNgau(_res1,_res2,_res3,CC_CALLBACK_0(TaiXiuDialog::testCallBackResult, this));
    _containerXiNgau->setScale(0.75);
    sprTimeTable->addChild(_containerXiNgau);
    _containerXiNgau->setNormalizedPosition(Vec2(0.5,0.5));
}

void TaiXiuDialog::testCallXiNgau(float dt){
    if (_containerXiNgau != NULL){
        _containerXiNgau->removeFromParent();
        _containerXiNgau = NULL;
    }
}

void TaiXiuDialog::testCallBackResult(){
    this->showTxtResult(true);
    scheduleOnce(schedule_selector(TaiXiuDialog::startTimer), 5);
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
        
        
        if (_result >= 4 && _result <= 10){
            addHistoryResult(TaiXiuResultType::XIU);
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_XIU,true);
        }else if (_result >= 11 && _result <= 17){
            addHistoryResult(TaiXiuResultType::TAI);
            this->ShowBtnTaiXiuEffect(TaiXiuStatus::select_TAI,true);
        }else{
            addHistoryResult(TaiXiuResultType::XCT);
        }
    }else{
        txtTXResult->setVisible(false);

        if ((_res1 == _res2) && (_res2 == _res3)){
            txtSpecialResult->setVisible(false);
        }
    }
    
}

void TaiXiuDialog::showTxtClock(bool _enable){
    if (_enable){
        txtClock->setVisible(true);
        
        if (_time>= 10){
            txtClock->setString(StringUtils::format("00:%zd",_time));
            txtCursorTime->setString(StringUtils::format("00:%zd",_time));
        }else if (_time >=0 && _time<10){
            txtClock->setString(StringUtils::format("00:0%zd",_time));
            txtCursorTime->setString(StringUtils::format("00:0%zd",_time));
            if (_time == 0){
                txtClock->setColor(Color3B::RED);
            }
        }else{
            txtClock->setString("00:00");
        }
    }else{
        txtClock->setVisible(false);
        txtCursorTime->setString("Kết Quả");
    }
}


void TaiXiuDialog::clock(float dt){
    if (!txtClock->isVisible()) return;
    _time--;
    
    if (_time == 0){
        resetStatus();
        setEnabledButton(TaiXiuButton::btnAll,false);
    }
    
    if (_time < 0){
        showTxtClock(false);
        callBackXiNgau();
    }else{
        showTxtClock(true);
    }
    
}

bool TaiXiuDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    return true;
}

void TaiXiuDialog::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void TaiXiuDialog::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){

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



