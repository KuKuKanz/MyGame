#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "ResourceNew.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(srcPLIST_tlmn);
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("MyGame", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
//    director->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
//    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
//    director->getOpenGLView()->setDesignResolutionSize(1334, 750, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
//    Director* pDirector = Director::getInstance();
//    auto pEGLView = pDirector->getOpenGLView();
//    //	pDirector->setOpenGLView(pEGLView);
//    pDirector->setAnimationInterval(1.0 / 60);
//    
//    
//    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    //    TestinCrashHelper::initTestinAgent("5e1ce731fa80c925db66f09b22f17223", "NPlay Android");
//    //#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    //    TestinCrashHelper::initTestinAgent("218e8cab563cdecf648a5155a1b24ea0", "NPlay iOS");
//    //#endif
//    
//    //Size screenSize = pEGLView->getFrameSize();
//    Size devSize= pEGLView->getFrameSize();
//    
//    Size designSize = Size(960,960*devSize.height/devSize.width);
//    pEGLView->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
//
    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    Clock::getInstance();
    AnimatedCoin::loadResource();
    TaiXiuBoard::loadResource();
    XiNgau::loadResource();
    AnimatedCursor::getInstance();


    auto scene = SceneCenter::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
