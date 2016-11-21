//
//  DemoDialogScene.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/13/16.
//
//

#include "DemoDialogScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ResourceNew.h"

Scene* DemoDialogScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DemoDialogScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool DemoDialogScene::init(){
    
    if (!Layer::init()){
        return false;
    }
    

    auto root = CSLoader::createNode("TempResource/Scene/DialogScene.csb");
    auto _butBaseDialog = (Button*)root->getChildByTag(1);
    auto _butCustomDialog = (Button*)root->getChildByTag(2);
    
    _butBaseDialog->addTouchEventListener(CC_CALLBACK_2(DemoDialogScene::callBack, this));
    _butCustomDialog->addTouchEventListener(CC_CALLBACK_2(DemoDialogScene::callBack, this));
    
    this->addChild(root);

    return true;
}

BaseDialog* DemoDialogScene::createBaseDialog(){
    
    auto baseDig = BaseDialog::createBaseDialog("Base Dialog", DialogFont::UTM_NEO_SANS_INTEL_BOLD, 600, 250);
    baseDig->setBackGround(srcPNG_dialog_khung);
    baseDig->insertSeparateLine(srcPNG_dialog_seperateline);
    baseDig->setTextContent("Hello every body ! I am a base Dialog", DialogFont::UTM_NEO_SANS_INTEL_BOLD_ITALIC);
    
    baseDig->addButton("Yes", srcPNG_dialog_button_ok, srcPNG_dialog_button_ok_tap, srcPNG_dialog_button_ok_disable);
    baseDig->addButton("No", srcPNG_dialog_button_ok, srcPNG_dialog_button_ok_tap, srcPNG_dialog_button_ok_disable);
    
    baseDig->DialogTouchEvent(CC_CALLBACK_2(DemoDialogScene::callBackBaseDialog, this));
    return baseDig;
}

void DemoDialogScene::callBack(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    switch (_type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            if (static_cast<Button*>(pSender)->getTag() == 1){
                baseDig = this->createBaseDialog();
                this->getScene()->addChild(baseDig);
                baseDig->start();
            }else if (static_cast<Button*>(pSender)->getTag() == 2){
                auto dialog = CustomizeDialog::create();
                this->getScene()->addChild(dialog);
                dialog->start();
            }
            break;
        }
            
            
        default:
            break;
    }
}

void DemoDialogScene::callBackBaseDialog(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    switch (_type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            auto _button = static_cast<Button*>(pSender);
            if (_button->getName() == "Yes"){
                baseDig->stop();
            }else if (_button->getName() == "No"){
                baseDig->stop();
            }
        }
            break;
            
        default:
            break;
    }
}


void DemoDialogScene::onExit(){

}
