//
//  CFunGame.hpp
//  project
//
//  Created by liuzhiwei on 15/10/25.
//
//

#ifndef CFunGame_hpp
#define CFunGame_hpp

#include <stdio.h>
#include <stdlib.h>
#include <cocos2d.h>

USING_NS_CC;

class CFunGame {
public:
    CFunGame();
    ~CFunGame();
    
    static CFunGame* GetInstance();
    static void ReleaseInstance(void* pObj);
    
    
    void Initialize();
    
    void InitGameResource();
    
    void EnterGame();
    
    /*! game pause */
    void handlePause();
    
    /*! game resume */
    void handleResume();
private:
    static CFunGame* m_pThis;
};

#endif /* CFunGame_hpp */
