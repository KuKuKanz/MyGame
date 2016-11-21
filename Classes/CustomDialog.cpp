//
//  CustomDialog.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/26/16.
//
//

#include "CustomDialog.hpp"
#include "ResourceNew.h"


bool CustomizeDialog::init(){
    
    if (!CustomizedDialog::initCustomizedDialog("Custom Dialog", DialogFont::UTM_NEO_SANS_INTEL_BOLD, 300, 150)){
        return false;
    }
    
    this->setBackGround(srcPNG_report_dropdownMenu);
    this->insertSeparateLine(srcPNG_dialog_seperateline);
    
    this->addButton("Yes",srcPNG_dialog_button_ok
                      ,srcPNG_dialog_button_ok_tap
                      ,srcPNG_dialog_button_ok_disable);
    
    this->addButton("No",srcPNG_dialog_button_ok,
                      srcPNG_dialog_button_ok_tap,
                      srcPNG_dialog_button_ok_disable);
    
    
    return true;
}


void CustomizeDialog::modifyDialogContent() {
    auto _hBox = VBox::create();

    _hBox->setContentSize(_layContent->getContentSize());
    
    
    for(int i = 0;i< 3;i++){
        auto _lay = Layout::create();
        
        auto _label = Label::createWithTTF("MOD THE CONTENT", srcTFF_UTM_NEO_SANS_INTELBOLD_0, 15);
        _label->setAlignment(TextHAlignment::CENTER);
        _label->setAnchorPoint(Vec2(0,0.5));
        _lay->setContentSize(_label->getContentSize());
        _lay->addChild(_label);
        
        LinearLayoutParameter* para = LinearLayoutParameter::create();
        para->setMargin(Margin(0, 0, 0, _label->getContentSize().height/2));
        
        _lay->setLayoutParameter(para);
        _hBox->addChild(_lay);
    }
    
    auto _sprite = Sprite::createWithSpriteFrameName(srcPNG_dialog_Ncoin);
    _sprite->setPosition(_layContent->getContentSize()/2);
    
    
    auto _animation = RepeatForever::create(Sequence::create(ScaleTo::create(1, 1.2),ScaleTo::create(1, 1), NULL));
    _sprite->runAction(_animation);
    
    _layContent->addChild(_sprite);
    _layContent->addChild(_hBox);
    
}

void CustomizeDialog::DialogTouchEventListener(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    auto button = static_cast<Button*>(pSender);
    
    switch (_type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            if (button->getName() == "Yes"){
                this->stop();
            }else if (button->getName() == "No"){
                this->stop();
            }
        break;
            
        default:
            break;
    }
    
    
}
