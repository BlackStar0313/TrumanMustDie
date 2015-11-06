//
//  CBulletManager.h
//  project
//
//  Created by peiyang  on 15/11/3.
//
//

#ifndef CBulletManager_h
#define CBulletManager_h

#include "cocos2d.h"
#include "CBullet.h"
#include <List>
#include <time.h>
#include "CPlane.h"
#include "asUniversalInterface.h"

using namespace std;
USING_NS_CC;

class CBulletManager
{
public:
    CBulletManager();
    
    ~CBulletManager();
    
    static CBulletManager* GetInstance();
    
    static void ReleaseInstance();
    
    void AddBullet(CBullet* pBullet);
    
    CBullet* CreateBullet(CBullet::m_type type = CBullet::m_type::empty);
    
    void RemoveBullet(CBullet* pbullet);
    
    void RemoveBulletFromList(list<CBullet*> &bulletList);

    void RemoveCollisionList();
    
    list<CBullet*> Collision(CPlane* pPlane);
    
    void AllBulletMove();
    
    list<CBullet*> checkFlyOut();
    
    void RemoveOutList();
    
    void clear();
private:
    static CBulletManager* m_pThis;
    
    list<CBullet*> m_BulletList;
    
    list<CBullet*> m_CollisionBulletList;
    
    list<CBullet*> m_OutBulletList;
    
};
#endif /* CBulletManager_h */
