/*
 * =====================================================================================
 *
 *       Filename: monsterrecord.inc
 *        Created: 05/12/2017 17:58:02
 *  Last Modified: 08/10/2017 22:50:50
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

// +-Name---------+-Level-+-Undead-+-Tameable-+-CoolEye-+-LookID-+-HP-----+-MP-----+-Hit----+-Exp----+-DC-----+-DCMax--+-MDC----+-MDCMax-+-AC-----+-ACMax--+-MAC----+-MACMax-+-ACFire----+-ACIce-----+-ACLight---+-ACWind----+-ACHoly----+-ACDark----+-ACPhantom-+-WalkWait-+-WalkSpeed-+-AttackMode-+-AttackWait-+-AttackEffect-+-DC[0]----------------+-DC[1]----------------+-DC[2]----------------+-DC[3]----------------+-DC[4]----------------+-DC[5]----------------+-DC[6]----------------+-DC[7]----------------+
{  u8""           , 0     , 0      , 0        , 0       , 0      , 0      , 0      , 0      , 0      , 0      , 0      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 0         , 0         , 0         , 0        , 0         , 0          , 0          , 0            , u8""                 , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"沙漠蜥蜴"   , 35    , 0      , 1        , 0       , 0X00   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"夜行鬼"     , 35    , 0      , 1        , 0       , 0X01   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"沙漠石人"   , 35    , 0      , 1        , 0       , 0X04   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"沙鬼"       , 35    , 0      , 1        , 0       , 0X05   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"沙漠树魔"   , 35    , 0      , 1        , 0       , 0X5F   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"狼"         , 9     , 0      , 1        , 0       , 0X41   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"名字3"      , 1     , 0      , 1        , 0       , 10     , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"名字d"      , 1     , 0      , 1        , 0       , 10     , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"名字&"      , 1     , 0      , 1        , 0       , 10     , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"名字t"      , 1     , 0      , 1        , 0       , 10     , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"名字d"      , 1     , 0      , 1        , 0       , 10     , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"名字u"      , 1     , 0      , 1        , 0       , 10     , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 }, 
{  u8"名字f"      , 1     , 0      , 1        , 0       , 10     , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"尸王"       , 1     , 0      , 1        , 0       , 0X35   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"红蛇"       , 1     , 0      , 1        , 0       , 0X36   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"虎卫"       , 1     , 0      , 1        , 0       , 0X37   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"变异骷髅"   , 30    , 1      , 0        , 0       , 0X38   , 100    , 10     , 10     , 10     , 5      , 20     , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"虎蛇"       , 1     , 0      , 1        , 0       , 0X39   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"羊"         , 1     , 0      , 1        , 0       , 0X3A   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },
{  u8"猎鹰"       , 1     , 0      , 1        , 0       , 0X3B   , 20     , 10     , 10     , 10     , 1      , 1      , 0      , 0      , 0      , 0      , 0      , 0      , 0         , 0         , 0         , 0         , 1         , 2         , 0         , 1000     , 100       , 0          , 1000       , 0            , u8"普通攻击"         , u8""                 , u8""                  , u8""                , u8""                 , u8""                 , u8""                 , u8""                 },