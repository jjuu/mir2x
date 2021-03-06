/*
 * =====================================================================================
 *
 *       Filename: charobject.hpp
 *        Created: 04/10/2016 12:05:22
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */
#pragma once

#include <map>
#include <list>
#include <deque>
#include <vector>

#include "servermap.hpp"
#include "damagenode.hpp"
#include "actionnode.hpp"
#include "cachequeue.hpp"
#include "servicecore.hpp"
#include "protocoldef.hpp"
#include "serverobject.hpp"

enum _RangeType: uint8_t
{
    RANGE_VIEW,
    RANGE_MAP,
    RANGE_SERVER,

    RANGE_VISIBLE,
    RANGE_ATTACK,
    RANGE_TRACETARGET,
};

#pragma pack(push, 1)
typedef struct
{
    uint8_t     Level;
    uint16_t    HP;
    uint16_t    MP;
    uint16_t    MaxHP;
    uint16_t    MaxMP;
    uint16_t    Weight;
    uint16_t    MaxWeight;
    uint32_t    Exp;
    uint32_t    MaxExp;

    uint8_t     WearWeight;
    uint8_t     MaxWearWeight;
    uint8_t     HandWeight;
    uint8_t     MaxHandWeight;

    uint16_t    DC;
    uint16_t    MC;
    uint16_t    SC;
    uint16_t    AC;
    uint16_t    MAC;

    uint16_t    Water;
    uint16_t    Fire;
    uint16_t    Wind;
    uint16_t    Light;
    uint16_t    Earth;
}OBJECTABILITY;

typedef struct
{
    uint16_t    HP;
    uint16_t    MP;
    uint16_t    HIT;
    uint16_t    SPEED;
    uint16_t    AC;
    uint16_t    MAC;
    uint16_t    DC;
    uint16_t    MC;
    uint16_t    SC;
    uint16_t    AntiPoison;
    uint16_t    PoisonRecover;
    uint16_t    HealthRecover;
    uint16_t    SpellRecover;
    uint16_t    AntiMagic;
    uint8_t     Luck;
    uint8_t     UnLuck;
    uint8_t     WeaponStrong;
    uint16_t    HitSpeed;
}OBJECTADDABILITY;
#pragma pack(pop)

// cache entry for charobject location
// should be visible for CharObject and its derived classes
struct COLocation
{
    uint64_t UID;
    uint32_t MapID;
    uint32_t RecordTime;

    int X;
    int Y;
    int Direction;

    COLocation(
            uint64_t nUID        = 0,
            uint32_t nMapID      = 0,
            uint32_t nRecordTime = 0,

            int nX = -1,
            int nY = -1,
            int nDirection = DIR_NONE)
        : UID(nUID)
        , MapID(nMapID)
        , RecordTime(nRecordTime)
        , X(nX)
        , Y(nY)
        , Direction(nDirection)
    {}
};

class CharObject: public ServerObject
{
    protected:
        class COPathFinder final: public AStarPathFinder
        {
            private:
                friend class CharObject;

            private:
                const CharObject *m_CO;

            private:
                const int m_CheckCO;

            private:
                mutable std::map<uint32_t, int> m_Cache;

            public:
                COPathFinder(const CharObject *, int);
               ~COPathFinder() = default;

            private:
               int GetGrid(int, int) const;
        };

    protected:
        enum QueryType: int
        {
            QUERY_NONE    = 0,
            QUERY_OK      = 1,
            QUERY_ERROR   = 2,
            QUERY_PENDING = 3,
        };

    protected:
        enum SpeedType: int
        {
            SPEED_NONE = 0,
            SPEED_MOVE,
            SPEED_ATTACK,
        };

    protected:
        struct TargetRecord
        {
            uint64_t UID;
            uint32_t ActiveTime;

            TargetRecord(uint64_t nUID = 0, uint32_t nActiveTime = 0)
                : UID(nUID)
                , ActiveTime(nActiveTime)
            {}
        };

        struct HitterUIDRecord
        {
            uint64_t UID;
            uint32_t Damage;
            uint32_t ActiveTime;

            HitterUIDRecord(uint64_t nUID = 0, uint32_t nDamage = 0, uint32_t nActiveTime = 0)
                : UID(nUID)
                , Damage(nDamage)
                , ActiveTime(nActiveTime)
            {}
        };

    protected:
        const ServiceCore *m_ServiceCore;
        const ServerMap   *m_Map;

    protected:
        const ServerMap *GetServerMap() const
        {
            return m_Map;
        }

    protected:
        std::map<uint64_t, COLocation> m_LocationList;

    protected:
        int m_X;
        int m_Y;
        int m_Direction;

    protected:
        int m_HP;
        int m_HPMax;
        int m_MP;
        int m_MPMax;

    protected:
        bool     m_MoveLock;
        bool     m_AttackLock;
        uint32_t m_LastMoveTime;
        uint32_t m_LastAttackTime;

    protected:
        std::vector<HitterUIDRecord> m_HitterUIDRecord;

    protected:
        CacheQueue<TargetRecord, SYS_MAXTARGET> m_TargetQueue;

    protected:
        OBJECTABILITY       m_Ability;
        OBJECTABILITY       m_WAbility;
        OBJECTADDABILITY    m_AddAbility;

    public:
        CharObject(ServiceCore *,       // service core
                ServerMap *,            // server map
                uint64_t,               // uid
                int,                    // map x
                int,                    // map y
                int);                   // direction
       ~CharObject() = default;

    protected:
        int X() const { return m_X; }
        int Y() const { return m_Y; }

    protected:
        int HP()    const { return m_HP; }
        int MP()    const { return m_MP; }
        int HPMax() const { return m_HPMax; }
        int MPMax() const { return m_MPMax; }

    protected:
        int Direction() const
        {
            return m_Direction;
        }

        uint32_t MapID() const
        {
            return m_Map ? m_Map->ID() : 0;
        }

    public:
        virtual bool Update() = 0;
        virtual bool InRange(int, int, int) = 0;

    public:
        bool NextLocation(int *, int *, int, int);
        bool NextLocation(int *pX, int *pY, int nDistance)
        {
            return NextLocation(pX, pY, Direction(), nDistance);
        }

    public:
        uint64_t Activate();

    protected:
        virtual void ReportCORecord(uint64_t) = 0;

    protected:
        void DispatchHealth();
        void DispatchAttack(uint64_t, int);

    protected:
        virtual void DispatchAction(          const ActionNode &);
        virtual void DispatchAction(uint64_t, const ActionNode &);

    protected:
        virtual void ReportAction(uint64_t, const ActionNode &);

    protected:
        virtual int OneStepReach(int, int, int *, int *);

    protected:
        virtual int Speed(int) const;

    protected:
        virtual bool CanMove();
        virtual bool RetrieveLocation(uint64_t, std::function<void(const COLocation &)>);

    protected:
        virtual bool RequestMove(int,   // nX, should be one hop distance
                int,                    // nY, should be one hop distance
                int,                    // nSpeed, move speed
                bool,                   // bAllowHalfMove, tolerate CO occupied error
                std::function<void()>,  // fnOnOK
                std::function<void()>); // fnOnError

    protected:
        virtual bool RequestSpaceMove(uint32_t, int, int, bool, std::function<void()>, std::function<void()>);

    protected:
        bool AddHitterUID(uint64_t, int);
        bool DispatchHitterExp();

    protected:
        virtual bool CanAttack();

    protected:
        virtual bool DCValid(int, bool) = 0;

    protected:
        virtual DamageNode GetAttackDamage(int) = 0;

    protected:
        virtual bool StruckDamage(const DamageNode &) = 0;

    protected:
        void AddMonster(uint32_t, int, int, bool);

    protected:
        virtual void CheckFriend(uint64_t, const std::function<void(int)> &) = 0;

    protected:
        virtual bool GoDie()   = 0;
        virtual bool GoGhost() = 0;

    protected:
        virtual int MaxStep() const
        {
            return 1;
        }

        virtual int MoveSpeed()
        {
            return SYS_DEFSPEED;
        }

    protected:
        // estimate how many hops we need
        // this function checks map but can't check CO
        // if we found one-hop distance we need send move request to servermap
        // return: 
        //          -1: invalid
        //           0: no move needed
        //           1: one-hop can reach
        //           2: more than one-hop can reach
        int EstimateHop(int, int);

    protected:
        int AttackSpeed() const
        {
            return SYS_DEFSPEED;
        }

        int MagicSpeed() const
        {
            return SYS_DEFSPEED;
        }

        int Horse() const
        {
            return 0;
        }

    protected:
        std::array<PathFind::PathNode, 3> GetChaseGrid(int, int, int) const;

    protected:
        int CheckPathGrid(int, int, uint32_t = 0) const;
        double OneStepCost(const CharObject::COPathFinder *, int, int, int, int, int) const;
};
