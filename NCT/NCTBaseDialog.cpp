//
//  NCTBaseDialog.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/23/16.
//
//

#include "NCTBaseDialog.hpp"

static bool hasLoadResource = false;

void BaseDialog::loadResource(){
    if (!hasLoadResource){
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_dialog);
        hasLoadResource = true;
    }
}

BaseDialog* BaseDialog::createBaseDialogWithTitle(std::string _title){
    
    auto dialog = new (std::nothrow) BaseDialog();
    
    if (dialog){
        if (dialog->initBaseDialog(_title)){
            dialog->autorelease();
        }else{
            CC_SAFE_DELETE(dialog);
        }
    }
    
    return dialog;
}
    

bool BaseDialog::initBaseDialog(std::string _title){
    
    if (!Layer::init()){
        return false;
    }
    
    this->backGround = Layout::create();
    this->backGround->setBackGroundImage(srcPNG_dialog_khung);
    this->setAnchorPoint(Vec2(0.5,0.5));
    this->setPosition(this->getContentSize()/2);
    
    this->addChild(this->backGround);
    
    return true;
}
