//
//  SceneCenter.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/12/16.
//
//

#include "SceneCenter.hpp"
#include "cocostudio/CocoStudio.h"

#include "ResourceNew.h"


USING_NS_CC;
using namespace cocostudio::timeline;


Scene* SceneCenter::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneCenter::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void SceneCenter::addLabelItem(std::string _s){
    auto _layout = Layout::create();
    _layout->setContentSize(Size(listItem->getContentSize().width,50));
    
    auto _text = Text::create(_s, srcTFF_Roboto_Bold, 20);
    _text->setPosition(_layout->getContentSize()/2);
    _layout->addChild(_text);
    listItem->pushBackCustomItem(_layout);
    
    _layout->setTouchEnabled(true);
}

// on "init" you need to initialize your instance
bool SceneCenter::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    BaseDialog::loadResource();
    
    root = CSLoader::createNode("TempResource/Scene/DemoScene.csb");
    root->setScaleX(this->getContentSize().width/root->getContentSize().width);
    root->setScaleY(this->getContentSize().height/root->getContentSize().height);
    
    layerBack = CSLoader::createNode("TempResource/Scene/LayerBack.csb");
    layerBack->retain();
    
    listItem = root->getChildByName<ListView*>("listItem");
    
    _checkCursor = layerBack->getChildByName<CheckBox*>("checkCursor");
    _checkCursor->addEventListener(CC_CALLBACK_2(SceneCenter::checkCallBack, this));
    
    _backButton = layerBack->getChildByName<Button*>("backButton");
    _backButton->addTouchEventListener(CC_CALLBACK_2(SceneCenter::callBackButton, this));
    
    this->addLabelItem("Test PhomBigWin Effect");
    this->addLabelItem("Test Animated Coin Wave");
    this->addLabelItem("Test Animated Cursor");
    this->addLabelItem("Test Download Resources");
    this->addLabelItem("Test Dialog");
    this->addLabelItem("Test Label");
    this->addLabelItem("Tai Xiu");
    this->addLabelItem("Material");




    
    listItem->addEventListener(CC_CALLBACK_2(SceneCenter::callBackItemClicked, this));
    
    this->addChild(root);
    this->addChild(AnimatedCursor::getInstance());
    //AnimatedCursor::getInstance()->setNormalizedPosition(Vec2(0.2,0.8));

    //layerBack->addChild(AnimatedCursor::getInstance());
    
    return true;
}


void SceneCenter::callBackItemClicked(cocos2d::Ref *pSender, ui::ListView::EventType _type){
    switch (_type) {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            switch (listItem->getCurSelectedIndex()) {
                case 0:
                {
                    auto scene = PhomBigWinScene::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    break;
                }
                    
                case 1:{
                    auto scene = CoinScene::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    break;
                }
                    
                case 2:{
                    auto scene = DemoAnimatedCursor::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    _checkCursor->setSelected(true);
                    break;
                }
                    
                case 3:{
                    auto scene = ResourceUpdateManagerScene::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    break;
                }
                    
                case 4:{
                    auto scene = DemoDialogScene::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    break;
                }
                    
                case 5:{
                    auto scene = Demo::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    break;
                }
                    
                case 6:{
                    auto scene = TaiXiuScene::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    break;
                }
                    
                case 7:{
                    auto scene = MaterialTest::createScene();
                    Director::getInstance()->pushScene(scene);
                    scene->addChild(layerBack);
                    break;
                }
                    
                default:
                    break;
            }
           
            break;
        }
            
        default:
            break;
    }
}

void SceneCenter::callBackButton(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    switch (_type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            layerBack->removeFromParent();
            Director::getInstance()->popToRootScene();
            break;
        }
        default:
            break;
    }
}

void SceneCenter::checkCallBack(cocos2d::Ref *pSender, CheckBox::EventType _type){
    switch (_type) {
        case cocos2d::ui::CheckBox::EventType::SELECTED:{
            AnimatedCursor::getInstance()->setVisible(true);

            break;
        }
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            AnimatedCursor::getInstance()->setVisible(false);
            break;
            
        default:
            break;
    }
}




