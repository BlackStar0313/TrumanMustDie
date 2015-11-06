//
//  CTestScene.hpp
//  project
//
//  Created by liuzhiwei on 15/10/25.
//
//

#ifndef CTestScene_hpp
#define CTestScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <map>
using namespace std;

class CTestScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* createScene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(CTestScene);
    
private:
    void callBack(CCNode* _node);
    void update(float dt);
    cocos2d::CCSprite *m_p;
};


#endif /* CTestScene_hpp */
