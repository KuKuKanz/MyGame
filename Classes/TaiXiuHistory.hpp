//
//  TaiXiuHistoryDialog.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/1/16.
//
//

#ifndef TaiXiuHistoryDialog_hpp
#define TaiXiuHistoryDialog_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <stdio.h>


using namespace cocos2d;
using namespace cocos2d::ui;

enum TXHistoryResult{
    historyTAI = 0,
    historyXIU = 1,
    historyXCT = 2
};

class TaiXiuHistory: public cocos2d::Layer
{
public:
    
    void addTXHistory(std::string _txtPhien,TXHistoryResult _result,std::string _totalMoney, bool _win);
    
    void openHistory();
    void closeHistory();
    void setEnableHistoricalData(bool _enable);
    
    CREATE_FUNC(TaiXiuHistory);
private:
    float _defaultScale;

    ListView* _listHistory;
    ImageView* _root;
    Layout* _backGround;
    
    Node* _historicalData;
    
    EventListenerTouchOneByOne* _listener;

    float wList,hList;

    virtual bool init();
    void initBoard();
    
    void onButtonTouch(Ref* pSender, Widget::TouchEventType type);
    
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void callBackClose();
};


#endif /* TaiXiuHistoryDialog_hpp */
