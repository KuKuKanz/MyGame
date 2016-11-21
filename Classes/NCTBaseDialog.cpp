//
//  NCTBaseDialog.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/23/16.
//
//

#include "NCTBaseDialog.hpp"
#include "ResourceNew.h"

static bool hasLoadResource = false;
static SpriteFrameCache* FRAME_CACHE;

static const char* UTM_NEO_SANS_INTEL               = "fonts/new/UTM_NEO_SANS INTEL_0.TTF";
static const char* UTM_NEO_SANS_INTEL_ITALIC        = "fonts/new/UTM_NEO_SANS INTEL_ITALIC_0.TTF";
static const char* UTM_NEO_SANS_INTEL_BOLD          = "fonts/new/UTM_NEO_SANS INTELBOLD_0.TTF";
static const char* UTM_NEO_SANS_INTEL_BOLD_ITALIC   = "fonts/new/UTM_NEO_SANS INTELBOLD_ITALIC_0.TTF";

const char* BaseDialog::getFontPath(DialogFont _font){
    switch (_font) {
        case DialogFont::UTM_NEO_SANS_INTEL:
            return UTM_NEO_SANS_INTEL;
            break;
            
        case DialogFont::UTM_NEO_SANS_INTEL_BOLD :
            return UTM_NEO_SANS_INTEL_BOLD;
            break;
            
        case DialogFont::UTM_NEO_SANS_INTEL_BOLD_ITALIC :
            return UTM_NEO_SANS_INTEL_BOLD_ITALIC;
            break;
            
        case DialogFont::UTM_NEO_SANS_INTEL_ITALIC :
            return UTM_NEO_SANS_INTEL_ITALIC;
            break;
            
        default:
            return UTM_NEO_SANS_INTEL;
            break;
    }
}


void BaseDialog::loadResource(){
    if (!hasLoadResource){
        
        FRAME_CACHE = SpriteFrameCache::getInstance();
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_dialog);
        hasLoadResource = true;
    }
}

BaseDialog* BaseDialog::createBaseDialog(std::string title, DialogFont _font,float width,float height){
    
    auto dialog = new (std::nothrow) BaseDialog();
    
    if (dialog){
        if (dialog->initBaseDialog(title,_font,width,height)){
            dialog->autorelease();
        }else{
            CC_SAFE_DELETE(dialog);
        }
    }
    
    return dialog;
}
    

bool BaseDialog::initBaseDialog(std::string title,DialogFont _font,float width,float height){
    
    if (!Layer::init()){
        return false;
    }
    
    this->backGround = NULL;
    this->lblTitle = NULL;
    this->lblContent = NULL;
    this->separateLine = NULL;
    this->layoutBG  = NULL;
    
    this->usedHeight = 0.;      //Used to caculate position of each childs in background.
    this->h = 50;              //Default heigh of Button in dialog
    this->curDialogState = DialogState::Idling;
    this->totalHeight = 0;      //This will caculate how heigh background will be
    
    this->dialogWidth = width;
    
    this->setTextTitle(title, _font);
    
    auto touchListen = EventListenerTouchOneByOne::create();
    touchListen->setSwallowTouches(true);
    touchListen->onTouchBegan = CC_CALLBACK_2(BaseDialog::onTouchBegan, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListen, this);
    
   
    return true;
}

bool BaseDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    return true;
}

void BaseDialog::setBackGround(const char *srcPNG){
    
    CCASSERT(FRAME_CACHE->getSpriteFrameByName(srcPNG),
             "Cant find background source by this path");
    
    if (this->backGround != NULL){
        this->layoutBG->removeChild(this->backGround);
        this->backGround->release();
    }
    
    this->backGround = Sprite::createWithSpriteFrame(FRAME_CACHE->getSpriteFrameByName(srcPNG));
    this->backGround->setAnchorPoint(Vec2(0.5,1));
    this->backGround->retain();
    this->setOpacity(0);
    
}

void BaseDialog::setTextTitle(std::string _text, DialogFont _font){
    if (this->lblTitle == NULL){
        this->lblTitle = Label::createWithTTF(TTFConfig(getFontPath(_font),20),_text, TextHAlignment::CENTER,dialogWidth*0.7);

        this->lblTitle->setAnchorPoint(Vec2(0.5,0.5));
        this->lblTitle->retain();
    }else{
        this->lblTitle->setString(_text);
        this->lblTitle->setTTFConfig(TTFConfig(getFontPath(_font),20));
    }

}

void BaseDialog::setTextContent(std::string _text, DialogFont _font){
    if (this->lblContent == NULL){
        this->lblContent = Label::createWithTTF(TTFConfig(getFontPath(_font),17),_text, TextHAlignment::CENTER,dialogWidth*0.9);
        
        this->lblContent->retain();
    }else{
        this->lblContent->setString(_text);
        this->lblContent->setTTFConfig( TTFConfig(getFontPath(_font),17));
    }
}


void BaseDialog::insertSeparateLine(const char *srcPNG){
    CCASSERT(FRAME_CACHE->getSpriteFrameByName(srcPNG),
             "Cant find Separate Line source by this path");
    
    this->separateLine = Sprite::createWithSpriteFrameName(srcPNG);
    this->separateLine->retain();
    
    usedHeight = this->separateLine->getContentSize().height + 10;
}

void BaseDialog::setScale(float _scaleValue){
    hasScale = true;
    _scale = _scaleValue;
}

void BaseDialog::refreshView(){
    totalHeight = 0;
    Vector<Node*> listNode;
    if (this->lblTitle != NULL){
        this->lblTitle->removeFromParent();
        totalHeight+= lblTitle->getContentSize().height + 5;
        listNode.pushBack(lblTitle);
    }
    if (this->separateLine != NULL){
        this->separateLine->removeFromParent();
        totalHeight+= separateLine->getContentSize().height + 10;
        listNode.pushBack(separateLine);
    }
    if (_hasContentCustomized){
        _layContent->removeFromParent();
        totalHeight+= this->_layContent->getContentSize().height + 10;
        listNode.pushBack(_layContent);
    }else if (this->lblContent != NULL){
        lblContent->removeFromParent();
        totalHeight+= this->lblContent->getContentSize().height*1.05;
        listNode.pushBack(lblContent);
    }
    if (this->listButton.size() > 0){
        totalHeight+= h + 10;
    }
    
    if (layoutBG != NULL){
        layoutBG->removeAllChildrenWithCleanup(false);
        layoutBG->removeFromParent();
        layoutBG->setContentSize(Size(dialogWidth,totalHeight));
        layoutBG->setPosition(this->getContentSize()/2);
        this->defaultSize = Size(dialogWidth,totalHeight);
    }else{
        layoutBG = Layout::create();
        layoutBG->setAnchorPoint(Vec2(0.5,0.5));
        layoutBG->setContentSize(Size(dialogWidth,totalHeight));
        layoutBG->setPosition(this->getContentSize()/2);
        this->defaultSize = Size(dialogWidth,totalHeight);
        layoutBG->retain();
    }
    
    layoutBG->addChild(this->backGround,0);
    
    for(auto content : listNode){
        content->setPosition(this->layoutBG->getContentSize()/2);
        layoutBG->addChild(content);
    }

    this->usedHeight = 0;
    
    if (this->lblTitle != NULL){
        this->lblTitle->setPositionY(layoutBG->getContentSize().height - this->lblTitle->getContentSize().height/2 - 5);
    
        usedHeight+= lblTitle->getContentSize().height + 5;
    }
    
    if (this->separateLine != NULL){
        this->separateLine->setPositionY(this->layoutBG->getContentSize().height - this->usedHeight - 10);
        usedHeight+= separateLine->getContentSize().height + 10;
    }
    
    if (_hasContentCustomized){
        this->_layContent->setPositionY(this->layoutBG->getContentSize().height - this->usedHeight - this->_layContent->getContentSize().height/2 - 5);
        usedHeight+= this->_layContent->getContentSize().height + 5;
    }else if (this->lblContent != NULL){
        this->lblContent->setPositionY(this->layoutBG->getContentSize().height - this->usedHeight - 0.5*this->lblContent->getContentSize().height);
        usedHeight+= this->lblContent->getContentSize().height*1.05;
    }
    
    if (this->listButton.size() > 0){
        
        ssize_t countLayout = listButton.size();
        
        if (this->bufferLayour){
            for(auto _layout : listLayout){
                _layout->removeAllChildren();
            }
            //this->bufferLayour->removeAllChildrenWithCleanup(false);
            this->layoutBG->removeChild(this->bufferLayour);
            
            this->listLayout.clear();
        }
 
        this->bufferLayour = Layout::create();
        bufferLayour->setAnchorPoint(Vec2(0.5,0.5));
        bufferLayour->setContentSize(Size(this->layoutBG->getContentSize().width*0.7,h));
        
        float y = this->layoutBG->getContentSize().height - this->usedHeight - h/2;
        bufferLayour->setPosition(this->layoutBG->getContentSize()/2);
        bufferLayour->setPositionY(y);

        
        for(int i = 0;i<countLayout;i++){
            auto _layout = Layout::create();
            _layout->setContentSize(Size(bufferLayour->getContentSize().width/countLayout,h));
            _layout->setAnchorPoint(Vec2(0.5,0.5));
            _layout->setPosition(bufferLayour->getContentSize()/2);
            _layout->setPositionX(_layout->getContentSize().width/2*(i) + _layout->getContentSize().width/2*(i+1));
            
            bufferLayour->addChild(_layout);
            listLayout.pushBack(_layout);
            
        }
        
        this->layoutBG->addChild(bufferLayour);
        usedHeight+= bufferLayour->getContentSize().height + 10;

        
        for(auto button : this->listButton){
            
            auto _layout = listLayout.at(this->listButton.getIndex(button));

            button->setPosition(_layout->getContentSize()/2);
            
            _layout->addChild(button);
        }

    }
    
    if (this->backGround != NULL){
        this->backGround->setPosition(this->layoutBG->getContentSize()/2);
        this->backGround->setPositionY(this->layoutBG->getContentSize().height);
        float width = this->backGround->getContentSize().width;
        
        this->_scaleX   = this->layoutBG->getContentSize().width/width;
        
        this->backGround->setScaleX(this->_scaleX);
        this->backGround->setScaleY(usedHeight/ this->backGround->getContentSize().height);
    }
    listNode.clear();

}

void BaseDialog::addButton(std::string _name, const char *srcNORMAL, const char *srcPRESS, const char *srcDISABLE){
    CCASSERT(FRAME_CACHE->getSpriteFrameByName(srcNORMAL), "Cant find this path");
    CCASSERT(FRAME_CACHE->getSpriteFrameByName(srcPRESS), "Cant find this path");
    CCASSERT(FRAME_CACHE->getSpriteFrameByName(srcDISABLE), "Cant find this path");
    

    Button* button = Button::create();
    
    button->setName(_name);
    button->loadTextureNormal(srcNORMAL,Widget::TextureResType::PLIST);
    button->loadTexturePressed(srcPRESS,Widget::TextureResType::PLIST);
    button->loadTextureDisabled(srcDISABLE,Widget::TextureResType::PLIST);
    
    float buttonHeight = button->getContentSize().height;
    float _scale = (0.65*h)/buttonHeight;
    
    button->setTitleText(_name);
    button->setTitleFontName(UTM_NEO_SANS_INTEL_BOLD);
    button->setTitleFontSize(20);
    button->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    button->setScale(_scale);
    
    button->addTouchEventListener(CC_CALLBACK_2(BaseDialog::DialogTouchEventListener,this));
    
    this->listButton.pushBack(button);
}

void BaseDialog::start(){
    if (this->curDialogState == DialogState::Idling){
        this->refreshView();
        this->addChild(this->layoutBG);
        this->layoutBG->setScale(0.7);

        float duration = 1;
        
        for(auto child : this->layoutBG->getChildren()){
            child->setOpacity(0);
            child->runAction(FadeIn::create(duration));
            
        }
        
        if (_hasContentCustomized){
            listNode.clear();
            listNode = this->getChild(_layContent, listNode);
            for(auto child : listNode){
                child->setOpacity(0);
                child->runAction(FadeIn::create(duration));
            }
        }

        for(auto but : listButton){
            but->setOpacity(0);
            but->runAction(FadeIn::create(duration));
        }

        this->layoutBG->runAction(ScaleTo::create(0.5, 1));
        
        this->curDialogState = DialogState::Opening;
    }
    
}

void BaseDialog::stop(){
    if (this->curDialogState == DialogState::Opening){
        float duration = 0.5;
        auto scaleUp = ScaleTo::create(0.1, 1.05);
        auto scaleDown = ScaleTo::create(duration-0.1, 0.7);
        
        for(auto child : this->layoutBG->getChildren()){
            auto fadeOut = FadeOut::create(duration);
            child->runAction(fadeOut);
        }
        
        if (_hasContentCustomized){
            listNode.clear();
            listNode = this->getChild(_layContent, listNode);
            for(auto child : listNode){
                child->runAction(FadeOut::create(duration));
            }
        }

        for(auto but : listButton){
            auto fadeOut = FadeOut::create(duration);
            but->runAction(fadeOut);
        }
        
 
        CallFuncN* clear = CallFuncN::create(CC_CALLBACK_0(BaseDialog::clear, this));
        this->layoutBG->runAction(Sequence::create(scaleUp,scaleDown,clear,NULL));
    }
    
}

void BaseDialog::DialogTouchEvent(const cocos2d::ui::AbstractCheckButton::ccWidgetTouchCallback &callback){
    for(auto button : listButton){
        button->addTouchEventListener(callback);
    }
}

void BaseDialog::clear(){
    
    this->curDialogState = DialogState::Destroyed;
    bufferLayour->removeAllChildren();

    for(auto _layout : listLayout){
        _layout->removeAllChildren();
    }
    
    for(auto _node : listNode){
        if (_node->getNumberOfRunningActions()>0){
            _node->stopAllActions();
        }
    }
    
    layoutBG->removeAllChildren();
    this->removeAllChildren();
    listLayout.clear();
    listButton.clear();
    listNode.clear();
    
    if (this->lblTitle != NULL){CC_SAFE_RELEASE_NULL(lblTitle);}
    if (this->lblContent != NULL){CC_SAFE_RELEASE_NULL(lblContent);}
    if (this->layoutBG != NULL){CC_SAFE_RELEASE_NULL(layoutBG);}
    if (_hasContentCustomized){
        _layContent->stopAllActions();
        this->_layContent->removeAllChildren();
        if (this->_layContent != NULL){CC_SAFE_RELEASE_NULL(_layContent);}
    }
    
    this->removeFromParent();
}


Vector<Node*> BaseDialog::getChild(cocos2d::ui::Layout *_layout, Vector<cocos2d::Node *> _listNode){
    for(auto child : _layout->getChildren()){
        auto _castLayout = dynamic_cast<Layout*>(child);
        if (_castLayout != NULL){
            _listNode = this->getChild(_castLayout, _listNode);
        }else{
            _listNode.pushBack(child);
        }
    }
    return _listNode;
}

void BaseDialog::modifyDialogContent(){
    //Virtual function
}

void BaseDialog::DialogTouchEventListener(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    ///Virtual function
}
