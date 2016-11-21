//
//  CursorController.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/12/16.
//
//

#include "CursorController.hpp"
#include "cocostudio/CocoStudio.h"

static CursorController* _root;

CursorController* CursorController::getInstance(){
    if (_root == NULL){
        _root = CursorController::create();
        _root->retain();
    }
    
    return _root;
}

bool CursorController::init(){
    
    if (!Layer::init()){
        return false;
    }
    
    auto root = CSLoader::createNode("TempResource/Scene/LayerCursor.csb");
    checkAuto = root->getChildByName<CheckBox*>("checkBoxBorder");
    speedSlide = root->getChildByName<Slider*>("slideSpeed");
    sleepSlide = root->getChildByName<Slider*>("slideSleep");
    lblSpeed = root->getChildByName<Text*>("lblSpeed");
    lblSleep = root->getChildByName<Text*>("lblSleep");
    
    speedSlide->setName("speed");
    sleepSlide->setName("sleep");
    
    checkAuto->addEventListener(CC_CALLBACK_2(CursorController::checkBoxCallback, this));
    speedSlide->addEventListener(CC_CALLBACK_2(CursorController::slideCallback, this));
    sleepSlide->addEventListener(CC_CALLBACK_2(CursorController::slideCallback, this));
    
    this->addChild(root);
    return true;
}



void CursorController::checkBoxCallback(cocos2d::Ref *pSender, CheckBox::EventType _type){
    switch (_type) {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            AnimatedCursor::getInstance()->setAutoPushToBorder(true);
            break;
            
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            AnimatedCursor::getInstance()->setAutoPushToBorder(false);
            break;
            
        default:
            break;
    }
}

void CursorController::slideCallback(cocos2d::Ref *pSender, Slider::EventType _type){
    switch (_type) {
        case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:{
            auto slider = dynamic_cast<Slider*>(pSender);
            if (slider->getName() == "speed"){
                curSpeed = (float)slider->getPercent() * (0.5/100.0);
                AnimatedCursor::getInstance()->setSpeed(curSpeed);
                lblSpeed->setString("Speed: " + StringUtils::format("%.1f",curSpeed*10));
            }else if (slider->getName() == "sleep"){
                curSleep = (float)slider->getPercent() * (5./100.);
                AnimatedCursor::getInstance()->setSleepingTime(curSleep);
                lblSleep->setString("Sleep: " + StringUtils::format("%.1f",curSleep));
            }
            break;
        }
            
        default:
            break;
    }
}



void CursorController::onExit(){
    Node::onExit();
    if (CursorController::getInstance()->getParent() != NULL){
        CursorController::getInstance()->removeFromParent();
    }
}
