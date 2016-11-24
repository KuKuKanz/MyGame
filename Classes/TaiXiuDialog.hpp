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
#include "Clock.hpp"
#include "XiNgau.hpp"
#include "AnimatedCursor.hpp"
#include "TaiXiuHistory.hpp"
#include "AnimatedCoin.hpp"
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

enum TXBoardState{
    COUNT_DOWN = 1,
    XINGAU_ACTION = 2,
    RESULT = 3,
    NEXT_TIME = 4
};


using namespace cocos2d;
using namespace cocos2d::ui;


class TaiXiuDialog: public cocos2d::Layer
{
public:
    TaiXiuStatus curTaiXiuStatus;
    TXBoardState _boardState;
    TaiXiuResultType curTaiXiuResult;
    
    static TaiXiuDialog* getInstance();
    
    void startTimer(float dt);
    void startNextTime(float dt);
    
    void openTXDialog();
    void closeTXDialog();
    void setEnabledButton(TaiXiuButton _typeBtn,bool _enable);
    void resetTimer();
    
    void addHistoryResult(TaiXiuResultType _type);
    void clock(float dt);
    void miliClock(float dt);

    CREATE_FUNC(TaiXiuDialog);
    
    CC_SYNTHESIZE(bool, _pause, isPause);
private:
    TaiXiuBoard* _root;
    TaiXiuHistory* _historyDialog;
    
    Layout* _backGround;

    int _res1,_res2,_res3;
    
    ImageView* dialog,*_resultOnCursor;
    
    Sprite* sprTimeTable, *sprTimeEffect, *sprTai, *sprXiu, *sprTenGame;
    
    ListView* listViewResult;
    
    Button *btnClose, *btnBet, *btnRemove, *btnHistory, *btn1, *btn2, *btn3, *btn4,*btnRule;
    
    Button* txtuserBet, *txtXiuBettor, *txtTaiBettor;
    
    Text* txtClock, *txtTXResult, *txtSpecialResult, *txtXiuBet,*txtTaiBet, *txtCursorTime;
    
    Label *txtAddMoney,*txtSubMoney;
    LoadingBar* ldbTimeLine;
    
    ProgressTimer* ptTimeLine;
    
    EventListenerTouchOneByOne* _listener;
    
    ParticleSystemQuad* parTimeEffect;
    
    XiNgauController* _containerXiNgau;
    XiNgauController* _containerXiNgauCursor;
    
    int _betCash,_taiBetCash,_xiuBetCash;
    int _betCashShow,_taiBetCashShow,_xiuBetCashShow;
    int _curBetCash,_curTaiBetCash,_curXiuBetCash;
    
    bool _close;
    
    virtual bool init();
    
    void drawDialog();
    
    void storeChild(Node* _node);
    void reSettingVar();
    void buttonSetting();
    void addHistoryResultToListView(ImageView* _img);
    void createEffectOnClickTX(TaiXiuStatus _status);
    void setBet(float _value);
    void confirmBet();
    void showCashResult(bool _enable);
    
    float getExactRotation(float _per);
    void resetStatus();
    void showTxtResult(bool _enable);
    void showTxtClock(bool _enable);
    void showTxtClockNextTime(bool _enable);
    std::string getTimeClock(int _timeClock);
    
    void ShowBtnTaiXiuEffect(TaiXiuStatus _status, bool _enable);
    void createResultOnCursor(TaiXiuResultType _status);
    void castAnimationForLabel(Label* _lable);

    void createTouchListener();
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void callBackTouchBtn(Ref* pSender, ui::Widget::TouchEventType type);
    void callBackInvisible();
    void callBackDialogAppear();
    void callBackXiNgau(float _timeShowResult);
    void callBackTimeLine();
    
    
    int _time;
    int _nextTime;
    int _defaultNextTime;
    
    
    void testAddHistory(float dt);
    void testCallXiNgau(float dt);
    
    void resetTimeLine();
    
    
    void onEnter();
    void onExit();
    int getCountCoinToShow(int _cash);
    
    bool _isAttractSuccessfully;
    
    void enableAttractUserForSelecting(bool _enable);
    
    Node* CreatePhomBigWinEffect(int _cash);
    
    void showTxt(std::string _s);


};

#endif /* TaiXiuDialog_hpp */
