/*
 * =====================================================================================
 *
 *       Filename: actormessage.hpp
 *        Created: 05/03/2016 13:19:07
 *  Last Modified: 05/04/2016 22:31:34
 *
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
#include <cstdint>

enum MessagePackType: int {
    MPK_UNKNOWN = 0,
    MPK_HI,
    MPK_OK,
    MPK_ERROR,
    MPK_PING,
    MPK_LOGIN,
    MPK_REFUSE,
    MPK_MOVE,
    MPK_HELLO,
    MPK_ACTIVATE,
    MPK_METRONOME,
    MPK_ADDMONSTER,
    MPK_NEWPLAYER,
    MPK_NEWCONNECTION,
    MPK_PLAYERPHATOM,
    MPK_QUERYLOCATION,
    MPK_TRYMOVE,
    MPK_MOVEOK,
    MPK_COMMITMOVE,
    MPK_LOCATIION,
    MPK_MASTERPERSONA,
    MPK_INITREGIONMONITOR,
    MPK_READY,
    MPK_REGIONMONITORREADY,
    MPK_NEIGHBOR,
    MPK_NEWMONSTER,
    MPK_LOGINOK,
    MPK_FORWARDCM,
};

typedef struct {
    uint32_t GUID;
    uint32_t UID;
    uint32_t AddTime;
    int X;
    int Y;
    void *Data;
}AMNewMonster;

typedef struct {
    int  LocX;
    int  LocY;
}AMRegionMonitorReady;

typedef struct {
    int  X;
    int  Y;
}AMRequestMove;

typedef struct {
    int  X;
    int  Y;
    int  W;
    int  H;
    int  LocX;
    int  LocY;
}AMRegion;

typedef struct {
    uint32_t MonsterIndex;
    uint32_t MapID;

    bool Strict;
    int  X;
    int  Y;
}AMMasterPersona;

typedef struct {
    uint32_t MonsterIndex;
    uint32_t MapID;
    uint32_t UID;
    uint32_t AddTime;

    bool Strict;
    int  X;
    int  Y;
}AMAddMonster;

typedef struct {
    void *Data;
}AMNewPlayer;

typedef struct {
    uint32_t GUID;
    uint32_t UID;
    uint32_t SID;
    uint32_t AddTime;
    uint32_t MapID;
    uint64_t Key;

    int X;
    int Y;
}AMLogin;

typedef struct {
    uint32_t GUID;
}AMPlayerPhantom;

typedef struct {
    uint8_t    Type;
    uint32_t   UID;
    uint32_t   AddTime;
    void      *Data;

    int X;
    int Y;
    int R;
}AMTryMove;

typedef struct {
    int X;
    int Y;
    int OldX;
    int OldY;
}AMMoveOK;

typedef struct {
    int X;
    int Y;
    int OldX;
    int OldY;
}AMCommitMove;

typedef struct {
    int X;
    int Y;
    int OldX;
    int OldY;
}AMLocation;
