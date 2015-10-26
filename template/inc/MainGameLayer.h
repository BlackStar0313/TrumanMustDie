//
//  MainGameLayer.h
//  project
//
//  Created by peiyang  on 15/10/26.
//
//

#ifndef MainGameLayer_h
#define MainGameLayer_h

#include <cocos2d.h>

USING_NS_CC;

class MainGameLayer : public cocos2d::CCLayer
{
public:
    
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainGameLayer);
    
    
    
private:
    void callBack1(CCNode* _node);
    void callBack2(CCNode* _node);
};



#endif /* MainGameLayer_h */


