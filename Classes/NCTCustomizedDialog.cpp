//
//  NCTCustomizedDialog.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/27/16.
//
//

#include "NCTCustomizedDialog.hpp"


bool CustomizedDialog::initCustomizedDialog(std::string title, DialogFont _font, float width, float height){
    
    if (!BaseDialog::initBaseDialog(title, _font, width, height)){
        return false;
    }
    

    this->_hasContentCustomized = true;

    this->_layContent = Layout::create();
    this->_layContent->setAnchorPoint(Vec2(0.5,0.5));
    this->_layContent->setContentSize(Size(width,height));
//    this->_layContent->setBackGroundColor(Color3B::GRAY);
//    this->_layContent->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    this->_layContent->retain();
    this->_layContent->setClippingEnabled(true);
    this->_layContent->setClippingType(Layout::ClippingType::STENCIL);
    
    this->modifyDialogContent();
    
    ///If we have a customized content, width of background will greater than a bit to cover this content.
    this->dialogWidth = 1.1*width;

    return true;
}

