//
//  MaterialTest.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#include "MaterialTest.hpp"


Scene* MaterialTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MaterialTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MaterialTest::init(){
    
    if (!Layer::init()){
        return false;
    }
    
    
    auto _layout = Layout::create();
    _layout->setContentSize(this->getContentSize());
    _layout->setBackGroundColor(Color3B::WHITE);
    _layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    this->addChild(_layout);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Test/pelatuk_default.plist");
    
    auto propertie = Properties::createNonRefCounted("Material/2d_effects.material#sample");

    Material* _mat = Material::createWithProperties(propertie);
    
    auto _sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pelatuk1.png"));
    
    _sprite->setNormalizedPosition(Vec2(0.5,0.5));
    _sprite->setGLProgramState(_mat->getTechniqueByName("blur")->getPassByIndex(0)->getGLProgramState());
    
    this->addChild(_sprite);
    

    return true;
}
