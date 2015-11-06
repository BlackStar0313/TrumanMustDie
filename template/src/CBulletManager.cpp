//
//  CBulletManager.cpp
//  project
//
//  Created by peiyang  on 15/11/3.
//
//

#include <stdio.h>
#include "CBulletManager.h"

CBulletManager* CBulletManager::m_pThis = NULL;

CBulletManager::CBulletManager()
{

}

CBulletManager::~CBulletManager()
{
    if (m_BulletList.size() > 0)
    {
        for (auto it = m_BulletList.begin(); it != m_BulletList.end(); ++it)
        {
            CC_SAFE_RELEASE(*it);
        }
        m_BulletList.clear();
    }
    if (m_CollisionBulletList.size() > 0)
    {
        for (auto it = m_CollisionBulletList.begin(); it != m_CollisionBulletList.end(); ++it)
        {
            CC_SAFE_RELEASE(*it);
        }
        m_CollisionBulletList.clear();
    }
    if (m_OutBulletList.size() > 0)
    {
        for (auto it = m_OutBulletList.begin(); it != m_OutBulletList.end(); ++it)
        {
            CC_SAFE_RELEASE(*it);
        }
        m_OutBulletList.clear();
    }
}

CBulletManager* CBulletManager::GetInstance()
{
    if (m_pThis == NULL)
    {
        m_pThis = new CBulletManager();
    }
    return m_pThis;
}

void CBulletManager::ReleaseInstance()
{
    if (m_pThis)
    {
        delete m_pThis;
        m_pThis = NULL;
    }
}

void CBulletManager::AddBullet(CBullet* pBullet)
{
    if (pBullet)
    {
        m_BulletList.push_back(pBullet);
    }
}

CBullet* CBulletManager::CreateBullet(CBullet::m_type type)
{
    if (type == CBullet::m_type::empty)
    {
        
        type = (CBullet::m_type)(asUniversalInterface::randType());
    }
    CBullet* pBullet = CBullet::create(type);
    if (pBullet)
    {
        AddBullet(pBullet);
        return pBullet;
    }
    return NULL;
}

void CBulletManager::RemoveBullet(CBullet* pbullet)
{
    if ( !pbullet ) {
        return ;
    }
    m_BulletList.remove(pbullet);
    pbullet->Boom();

}

void CBulletManager::RemoveBulletFromList(list<CBullet*> &bulletList)
{
    if (bulletList.size() > 0)
    {
        for (auto it = bulletList.begin(); it != bulletList.end(); ++it)
        {
            RemoveBullet((*it));
        }
        bulletList.clear();
    }
}

void CBulletManager::RemoveCollisionList()
{
    RemoveBulletFromList(m_CollisionBulletList);
}

list<CBullet*> CBulletManager::Collision(CPlane* pPlane)
{
    if (m_BulletList.size() > 0) {
        for (auto it = m_BulletList.begin(); it != m_BulletList.end(); ++it)
        {
            if ((*it)->boundingBox().intersectsRect(pPlane->boundingBox())) {
                m_CollisionBulletList.push_back((*it));
            }
        }
    }
    return m_CollisionBulletList;
}

void CBulletManager::AllBulletMove()
{
    for (auto it = m_BulletList.begin(); it != m_BulletList.end(); ++it) {
        (*it)->setPosition((*it)->getPosition() + (*it)->getDirection());
    }
}

list<CBullet*> CBulletManager::checkFlyOut()
{
    if (m_BulletList.size() > 0)
    {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        for (auto it = m_BulletList.begin(); it != m_BulletList.end(); ++it) {
            //判断是否出边界
            if (((*it)->getPositionX() < -50) || ((*it)->getPositionX() > origin.x + visibleSize.width + 50) || ((*it)->getPositionY() < -50) || ((*it)->getPositionY() > origin.y + visibleSize.height + 50))
            {
                CCLOG("FLY OUT");
                m_OutBulletList.push_back(*it);
            }
        }
    }
    return m_OutBulletList;
}

void CBulletManager::RemoveOutList()
{
    RemoveBulletFromList(m_OutBulletList);
}

void CBulletManager::clear()
{
    m_BulletList.clear();
    m_CollisionBulletList.clear();
    m_OutBulletList.clear();
}


