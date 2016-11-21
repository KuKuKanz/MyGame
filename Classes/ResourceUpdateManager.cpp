//
//  ResourceUpdateManager.cpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#include "ResourceUpdateManager.hpp"



ResourceUpdateManager* ResourceUpdateManager::createResourceUpdateManager(const char *pathManifest, const char *storePath){
    
    auto _resMag = new (std::nothrow) ResourceUpdateManager();
    
    if (_resMag){
        if (!_resMag->init(pathManifest,storePath)){
            CC_SAFE_DELETE(_resMag);
        }
    }
    
    return _resMag;
}

bool ResourceUpdateManager::init(const char *pathManifest, const char *storePath){
    
    if (!Node::init()){
        return false;
    }
    
    this->_pathManifest = pathManifest;
    this->_storePath = storePath;
    this->_searchPath = FileUtils::getInstance()->getWritablePath() + _storePath;
    
    this->assMag = AssetsManagerEx::create(pathManifest, _searchPath);
    this->assMag->retain();
    
    onFinish = NULL;
    onFailed = NULL;
    onProgressing = NULL;
    
    return true;
}

void ResourceUpdateManager::startUpdateResource(){
    if (!assMag->getLocalManifest()->isLoaded())
    {
        CCLOG("Fail to update assets, step skipped.");
    }
    else
    {
        assMag_listener = EventListenerAssetsManagerEx::create(assMag, CC_CALLBACK_1(ResourceUpdateManager::callBack, this));
        getEventDispatcher()->addEventListenerWithFixedPriority(assMag_listener, 1);
        assMag->update();
    }
}

void ResourceUpdateManager::resetUpdateReousrce(){
    assMag->release();
    
    this->assMag = AssetsManagerEx::create(_pathManifest, FileUtils::getInstance()->getWritablePath() + _storePath);
    this->assMag->retain();
    
    getEventDispatcher()->removeEventListener(assMag_listener);
    
    assMag_listener = EventListenerAssetsManagerEx::create(assMag, CC_CALLBACK_1(ResourceUpdateManager::callBack, this));
    getEventDispatcher()->addEventListenerWithFixedPriority(assMag_listener, 1);
    assMag->update();
}

std::string ResourceUpdateManager::getCurrentVersion(){
    if (assMag->getLocalManifest()->isLoaded()){
        return assMag->getLocalManifest()->getVersion();
    }
    return "Load current version failed";
}

std::string ResourceUpdateManager::getResourcePath(){
    return _searchPath;
}


void ResourceUpdateManager::callBack(cocos2d::extension::EventAssetsManagerEx *event){
    switch (event->getEventCode()) {
            
        case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
            
            break;
            
        case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
            if (onProgressing != NULL){this->onProgressing(event->getAssetId(),event->getPercent());}

            break;
            
        case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
        case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
            if (onFinish != NULL){this->onFinish();}
            break;
            
        case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
        case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
        case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
        case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
        case EventAssetsManagerEx::EventCode::UPDATE_FAILED:{
    
            if (onFailed != NULL){this->onFailed(StringUtils::format("Error updating: %s",event->getMessage().c_str()));}
            break;
        }
            
        case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
            break;
            
        case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
            break;
        
        default:
            break;
    }
}


void ResourceUpdateManager::clear(){
    assMag->release();
    getEventDispatcher()->removeEventListener(assMag_listener);
    onFinish = NULL;
    onFailed = NULL;
    onProgressing = NULL;
    
    this->release();
}


