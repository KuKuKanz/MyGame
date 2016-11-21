//
//  NCTBaseDialog.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/23/16.
//
//

#ifndef NCTBaseDialog_hpp
#define NCTBaseDialog_hpp

#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocos2d;
using namespace cocos2d::ui;

enum class DialogState{
    Idling = 0,
    Opening = 1,
    Destroyed
};

enum class DialogFont{
    UTM_NEO_SANS_INTEL              = 0,
    UTM_NEO_SANS_INTEL_ITALIC       = 1,
    UTM_NEO_SANS_INTEL_BOLD         = 2,
    UTM_NEO_SANS_INTEL_BOLD_ITALIC  = 3
};

class BaseDialog : public Layer{
private:
    
    float _scaleX,_scaleY,_scale;
    float totalHeight,usedHeight,h;
    
    Sprite* backGround;
    Sprite* separateLine;
    
    Layout* layoutBG;
    Layout* bufferLayour;
   
    cocos2d::Size defaultSize;
    
    Label* lblTitle;
    Label* lblContent;
    
    Vector<Button*> listButton;
    Vector<Layout*> listLayout;
    Vector<Node*> listNode;
    bool hasScale;
    DialogState curDialogState;

protected:
    bool _hasContentCustomized;
    
    float dialogWidth;
    
    Layout* _layContent;
    
public:
    static void loadResource();
    
    static BaseDialog* createBaseDialog(std::string title,DialogFont _font,float width,float height);
    bool initBaseDialog(std::string title, DialogFont _font,float width,float height);
    void setBackGround(const char* srcPNG);
    void setTextTitle(std::string _text, DialogFont _font);

    void setTextContent(std::string _text, DialogFont _font);
    void insertSeparateLine(const char* srcPNG);
    void setScale(float _scaleValue) override;
    
    void addButton(std::string _name,const char* srcNORMAL, const char* srcPRESS, const char* srcDISABLE);

    void DialogTouchEvent(const cocos2d::ui::AbstractCheckButton::ccWidgetTouchCallback& callback);
    void start();
    void stop();
    void clear();
    
private:
    bool onTouchBegan(Touch* touch, Event* event) override;

    void refreshView();
    Vector<Node*> getChild(Layout* _layout,Vector<Node*> _listNode);
    const char* getFontPath(DialogFont _font);
    
protected:
    virtual void DialogTouchEventListener(Ref* pSender, Widget::TouchEventType _type);
    virtual void modifyDialogContent();
    
};

#endif /* NCTBaseDialog_hpp */
