//
//  TaiXiuBoard.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 11/2/16.
//
//

#ifndef TaiXiuBoard_hpp
#define TaiXiuBoard_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <stdio.h>

using namespace cocos2d;
using namespace cocos2d::ui;

enum TXChildTag{
    kTagDialog = 32,
    kTagTenGame = 33,
    kTagSprTai = 37,
    kTagSprXiu = 40,
    kTagTimeTable = 36,
    kTagTimeline = 49,
    kTagTimeEffect = 50,
    KTagListView = 65,
    kTagBtnClose = 63,
    kTagBtnBet = 45,
    kTagBtnRemove = 46,
    kTagBtnHistory = 51,
    kTagBtn1 = 55,
    kTagBtn2 = 60,
    kTagBtn3 = 61,
    kTagBtn4 = 62,
    kTabTextUserBet = 44,
    kTagTextXiuBet = 42,
    kTagTextTaiBet = 39,
    kTagTextXiuBettor = 35,
    kTagTextTaiBettor = 53,
    kTagTextClock = 47,
    kTagTextSubMoney =  48,
    kTagTextTaiXiuResult = 84,
    kTagTextAddMoney = 81,
    kTagTextSpecialResult = 86,
};


class TaiXiuBoard : public Node{
    
public:
    static void loadResource();
    
    RepeatForever* _aniTenGame;

    
    CREATE_FUNC(TaiXiuBoard);
    
private:
    virtual bool init();
    
    
    void drawBoard();
    
    void createAnimationForTenGame();
    
    
};


#endif /* TaiXiuBoard_hpp */
