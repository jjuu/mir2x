/*
 * =====================================================================================
 *
 *       Filename: processrun.hpp
 *        Created: 08/31/2015 03:42:07
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
#include <memory>
#include <cstdint>
#include <algorithm>

#include "myhero.hpp"
#include "process.hpp"
#include "message.hpp"
#include "creature.hpp"
#include "focustype.hpp"
#include "ascendstr.hpp"
#include "commonitem.hpp"
#include "indepmagic.hpp"
#include "labelboard.hpp"
#include "mir2xmapdata.hpp"
#include "controlboard.hpp"
#include "inventoryboard.hpp"
#include "clientluamodule.hpp"
#include "linebrowserboard.hpp"

class ClientPathFinder;
class ProcessRun: public Process
{
    private:
        struct UserCommandEntry
        {
            std::string Command;
            std::function<int(const std::vector<std::string> &)> Callback;

            UserCommandEntry(const char *szCommand, std::function<int(const std::vector<std::string> &)> rfnOP)
                : Command(szCommand ? szCommand : "")
                , Callback(rfnOP)
            {}
        };

    private:
        enum OutPortType: int
        {
            OUTPORT_NONE         = (0 << 0),
            OUTPORT_LOG          = (1 << 0),
            OUTPORT_SCREEN       = (2 << 1),
            OUTPORT_CONTROLBOARD = (3 << 1),
        };

    private:
        std::vector<UserCommandEntry> m_UserCommandGroup;

    private:
        uint32_t     m_MapID;
        Mir2xMapData m_Mir2xMapData;

    private:
        std::vector<std::vector<std::vector<CommonItem>>> m_GroundItemList;

    private:
        uint64_t m_MyHeroUID;

    public:
        bool ValidC(int nX, int nY) const
        {
            return m_Mir2xMapData.ValidC(nX, nY);
        }

    private:
        std::array<uint64_t, FOCUS_MAX> m_FocusTable;

    private:
        int m_ViewX;
        int m_ViewY;

    private:
        bool m_RollMap;

    private:
        ClientLuaModule m_LuaModule;

    private:
        ControlBoard m_ControbBoard;

    private:
        InventoryBoard m_InventoryBoard;

    private:
        std::list<std::shared_ptr<IndepMagic>> m_IndepMagicList;

    private:
        std::map<uint64_t, std::shared_ptr<Creature>> m_CreatureList;

    private:
        // use a tokenboard to show all in future
        LabelBoard m_MousePixlLoc;
        LabelBoard m_MouseGridLoc;

    private:
        std::list<std::shared_ptr<AscendStr>> m_AscendStrList;

    private:
        void ScrollMap();

    private:
        int LoadMap(uint32_t);

    public:
        ProcessRun();
        virtual ~ProcessRun() = default;

    public:
        int ID() const
        {
            return PROCESSID_RUN;
        }

        uint32_t MapID() const
        {
            return m_MapID;
        }

    public:
        void Notify(int, const char *);
        void Notify(const char *, const std::map<std::string, std::function<void()>> &);

    public:
        virtual void Update(double);
        virtual void Draw();
        virtual void ProcessEvent(const SDL_Event &);

    public:
        bool ScreenPoint2Grid(int, int, int *, int *);

    public:
        bool OnMap(uint32_t, int, int) const;

    public:
        void Net_EXP(const uint8_t *, size_t);
        void Net_GOLD(const uint8_t *, size_t);
        void Net_ACTION(const uint8_t *, size_t);
        void Net_OFFLINE(const uint8_t *, size_t);
        void Net_LOGINOK(const uint8_t *, size_t);
        void Net_PICKUPOK(const uint8_t *, size_t);
        void Net_CORECORD(const uint8_t *, size_t);
        void Net_UPDATEHP(const uint8_t *, size_t);
        void Net_FIREMAGIC(const uint8_t *, size_t);
        void Net_DEADFADEOUT(const uint8_t *, size_t);
        void Net_MONSTERGINFO(const uint8_t *, size_t);
        void Net_SHOWDROPITEM(const uint8_t *, size_t);

    public:
        bool CanMove(bool, int, int, int);
        bool CanMove(bool, int, int, int, int, int);

    public:
        double MoveCost(bool, int, int, int, int);

    private:
        uint64_t FocusUID(int);

    public:
        bool  LuaCommand(const char *);
        bool UserCommand(const char *);

    public:
        uint32_t GetFocusFaceKey();

    public:
        std::vector<int> GetPlayerList();

    public:
        bool AddOPLog(int, int, const char *, const char *, ...);

    public:
        bool RegisterUserCommand();

    public:
        bool RegisterLuaExport(ClientLuaModule *, int);

    public:
        Creature *RetrieveUID(uint64_t);
        bool LocateUID(uint64_t, int *, int *);

    private:
        bool TrackAttack(bool, uint64_t);

    public:
        void AddAscendStr(int, int, int, int);

    public:
        bool GetUIDLocation(uint64_t, bool, int *, int *);

    public:
        void CenterMyHero();

    public:
        MyHero *GetMyHero() const
        {
            // GetMyHero() is read-only
            // won't use RetrieveUID(), it may change m_CreatureList

            if(m_MyHeroUID){
                if(auto p = m_CreatureList.find(m_MyHeroUID); p != m_CreatureList.end()){
                    return dynamic_cast<MyHero *>(p->second.get());
                }
            }
            return nullptr;
        }

    public:
        const auto &GetGroundItemList(int nX, int nY) const
        {
            return m_GroundItemList[nX][nY];
        }

        int FindGroundItem(const CommonItem &rstCommonItem, int nX, int nY)
        {
            for(int nIndex = (int)(m_GroundItemList[nX][nY].size()) - 1; nIndex >= 0; --nIndex){
                if(m_GroundItemList[nX][nY][nIndex] == rstCommonItem){
                    return nIndex;
                }
            }
            return -1;
        }

        bool AddGroundItem(const CommonItem &rstCommonItem, int nX, int nY)
        {
            if(rstCommonItem && m_Mir2xMapData.ValidC(nX, nY)){
                m_GroundItemList[nX][nY].push_back(rstCommonItem);
                return true;
            }
            return false;
        }

        void RemoveGroundItem(const CommonItem &rstCommonItem, int nX, int nY)
        {
            for(auto pCurr = m_GroundItemList[nX][nY].begin(); pCurr != m_GroundItemList[nX][nY].end(); ++pCurr){
                if(*pCurr == rstCommonItem){
                    m_GroundItemList[nX][nY].erase(pCurr);
                    return;
                }
            }
        }

        void ClearGroundItem(int nX, int nY)
        {
            m_GroundItemList[nX][nY].clear();
        }

    public:
        int CheckPathGrid(int, int) const;
        double OneStepCost(const ClientPathFinder *, bool, int, int, int, int, int) const;

    public:
        bool RequestSpaceMove(uint32_t, int, int);

    public:
        void ClearCreature();

    public:
        void QueryCORecord(uint64_t) const;
        void OnActionSpawn(uint64_t, const ActionNode &);

    public:
        Widget *GetWidget(const char *);
};
