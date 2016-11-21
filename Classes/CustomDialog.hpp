//
//  CustomDialog.hpp
//  MyGame
//
//  Created by Dao Hoang Tung on 9/26/16.
//
//

#ifndef CustomDialog_hpp
#define CustomDialog_hpp

#include "NCTCustomizedDialog.hpp"
#include <stdio.h>


class CustomizeDialog : public CustomizedDialog{
public:
    virtual bool init();

    CREATE_FUNC(CustomizeDialog);

private:
    

    virtual void modifyDialogContent();
    virtual void DialogTouchEventListener(Ref* pSender, Widget::TouchEventType _type);

};



#endif /* CustomDialog_hpp */
