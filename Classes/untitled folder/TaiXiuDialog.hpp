//
//  TaiXiuDialog.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/31/16.
//
//

#ifndef TaiXiuDialog_hpp
#define TaiXiuDialog_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "TaiXiuBoard.hpp"
#include "XiNgau.hpp"
#include "AnimatedCursor.hpp"
#include <stdio.h>


enum TaiXiuResultType{
    TAI = 0,
    XIU = 1,
    XCT = 2
};

enum TaiXiuStatus{
    select_TAI = 0,
    select_XIU = 1,
    select_NONE = 3
};

enum TaiXiuButton{
    btn1 = 0,
    btn2 = 1,
    btn3 = 2,
    btn4 = 3,
    btnAll = 4
};


using namespace cocos2d;
using namespace cocos2d::ui;


class TaiXiuDialog: public cocos2d::Layer
{
public:
    TaiXiuStatus curTaiXiuStatus;
    
    static TaiXiuDialog* getInstance();
    
    void startTimer(float dt);
    
    void openTXDialog();
    void closeTXDialog();
    void setEnabledButton(TaiXiuButton _typeBtn,bool _enable);
    void resetTimer();
    
    void addHistoryResult(TaiXiuResultType _type);
    
    CREATE_FUNC(TaiXiuDialog);
    
private:
    TaiXiuBoard* _root;
    
    int _res1,_res2,_res3;
    
    ImageView* dialog;
    
    Sprite* sprTimeTable, *sprTimeEffect, *sprTai, *sprXiu, *sprTenGame;
    
    ListView* listViewResult;
    
    Button *btnClose, *btnBet, *btnRemove, *btnHistory, *btn1, *btn2, *btn3, *btn4;
    
    Button* txtuserBet, *txtXiuBettor, *txtTaiBettor;
    
    Text* txtClock, *txtAddMoney, *txtSubMoney, *txtTXResult, *txtSpecialResult, *txtXiuBet,*txtTaiBet, *txtCursorTime;
    
    LoadingBar* ldbTimeLine;
    
    ProgressTimer* ptTimeLine;
    
    EventListenerTouchOneByOne* _listener;
    
    ParticleSystemQuad* parTimeEffect;
    
    XiNgauController* _containerXiNgau;
    
    bool _close;
    
    virtual bool init();
    
    void drawDialog();
    
    void storeChild(Node* _node);
    void reSettingVar();
    void buttonSetting();
    void addHistoryResultToListView(ImageView* _img);
    void createEffectOnClickTX(TaiXiuStatus _status);
    
    float getExactRotation(float _per);
    void resetStatus();
    void showTxtResult(bool _enable);
    void showTxtClock(bool _enable);
    void ShowBtnTaiXiuEffect(TaiXiuStatus _status, bool _enable);
    
    
    void createTouchListener();
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void callBackTouchBtn(Ref* pSender, ui::Widget::TouchEventType type);
    void callBackInvisible();
    void callBackDialogAppear();
    void callBackXiNgau();
    void callBackTimeLine();
    
    
    int _time;
    void clock(float dt);
    
    void testAddHistory(float dt);
    void testCallXiNgau(float dt);
    void testCallBackResult();
    
    void resetTimeLine();
    void onExit();

};

#endif /* TaiXiuDialog_hpp */
