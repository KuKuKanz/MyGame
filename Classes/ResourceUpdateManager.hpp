//
//  ResourceUpdateManager.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 10/11/16.
//
//

#ifndef ResourceUpdateManager_hpp
#define ResourceUpdateManager_hpp

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <extensions/assets-manager/AssetsManagerEx.h>
#include <extensions/assets-manager/CCEventListenerAssetsManagerEx.h>

using namespace cocos2d;
using namespace network;
using namespace ui;
using namespace extension;

class ResourceUpdateManager : public Node{
protected:
     typedef std::function<void()> ccUpdateFinish;
     typedef std::function<void(std::string)> ccUpdateFailed;
    typedef std::function<void(std::string,float)> ccUpdateProgressing;

public:
    /**
     * Create a new and non-autorelease object of Resource Update Manager
     *
     * @param pathManifest path link to the project.manifest file.
     * @param storePath  place to store download resources.
     */
    static ResourceUpdateManager* createResourceUpdateManager(const char* pathManifest,
                                                              const char* storePath);
    
    /**
     * Throw a call back when update progression done !
     */
    ccUpdateFinish onFinish;
    
    /**
     * Throw a call back with a message when update procession is failed
     */
    ccUpdateFailed onFailed;
    
    /**
     * Throw call back with downloaded percent value during progression.
     */
    ccUpdateProgressing onProgressing;
    
    /**
     * Return the current verison of this resources
     */
    std::string getCurrentVersion();
    
    /**
     * Return path of root directory containing updated resources
     */
    std::string getResourcePath();
    
    /**
     * start to update resources
     */
    void startUpdateResource();
    
    /**
     * If updating resources is failed, call this method to re-update/
     */
    void resetUpdateReousrce();
    
    /**
     * Remove object
     */
    void clear();
    
private:
    std::string _pathManifest, _storePath, _searchPath;
    AssetsManagerEx* assMag;
    EventListenerAssetsManagerEx* assMag_listener;
    
    void callBack(EventAssetsManagerEx* event);

    
    bool init(const char* pathManifest,
              const char* storePath);
    
    

};
#endif /* ResourceUpdateManager_hpp */
