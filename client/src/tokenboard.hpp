/*
 * =====================================================================================
 *
 *       Filename: tokenboard.hpp
 *        Created: 06/17/2015 10:24:27 PM
 *  Last Modified: 03/31/2016 20:37:08
 *
 *    Description: Design TBD.
 *
 *                 For scenario we need text-emoticon mixed boards:
 *
 *                 1. button like text terminal. which we only need to support emoticon
 *                    and eventtext, eventtext accept button click event only. This is
 *                    the simple case. no select/edit support needed.
 *
 *                 2. chatbox, two parts:
 *                      a. already sent chat messages.
 *                      b. editting chatting messages.
 *
 *                      +--------------------------+ 
 *                      | xxxxx :), xxxxxxxxxxxxxx |
 *                      | xxxxxxxxxxxxxxxxxxx.     |
 *                      | xx                       | <----- already sent messages
 *                      | xxxxxxxxxxxxxxxxxxxxxxxx |
 *                      | xxxxxxxxxxxxxxxxxxxxxxxx |
 *                      | xxxxxxxxxxxxxxxxxxxxxxxx |
 *                      +--------------------------+
 *                      | xxx :( xxxx |            |
 *                      |                          | <----- editting messages
 *                      +--------------------------+
 *
 *                      for 2-a: there is emoticon, normal text, eventtext, eventtext for hyperlinks
 *                               to trigger event, just like 1. 2-a should support select.
 *
 *                      for 2-b: there is emoticon and normal text. need to support select/edit. as
 *                               analyzed, edit is insert, and insert can be implemented by select.
 *                               so 2-b we need to support select.
 *
 * ================Analysis on 03/22/2016===========================================================
 *                 Analysis: why we use select to support insert:
 *
 *                   for insert, we add new tokens to current board, we can everytime insert a new
 *                   token and re-padding, or we can return the underlying XML/plainText, and then
 *                   re-generate the whole board. Re-generatioin is better since re-padding every-
 *                   time is a re-generation. Even if we implement a new class EditBoard, it's still
 *                   a decision for re-padding and re-generation. So just use TokenBoard.
 *
 *                 For boards need to support insert, we need to supprt insert at anywhere we want,
 *                 this means we need to support select anywhere we want by click at the token of 
 *                 the place. So problem comes with eventtext, which already take click as event tr-
 *                 igger.
 *
 *                   But it's OK since for editable board, we don't need eventtext(hyperlinks), the
 *                 place we need hyperlinks is for case 2-a. This means at which we need to trigger
 *                 event, just trigger it, don't think about place location for insert. Since if we
 *                 really need to insert in current board, this board doesn't need trigger event.
 *
 *                   Another problem, how to support insert before current cursor? We can use func-
 *                 tion like GetXML() or GetPlainText(), but both just return formated text. inside
 *                 the tokenboard, cursor is something like (x, y) or (section, offset). we can't do
 *                 insert based on the returned text.
 *
 *                   Currently what I can get is inside the board class for each section I keep a
 *                 copy of its stinrg content, this helps to return GetXML() and GetPlainText() qui-
 *                 ckly and also we can maintain the mapping inside, and each time warpper class can
 *                 only ask for insert a token or a piece of text. Internal text mapping will handle
 *                 it properly, with update of string copy.
 * 
 *                 BUT, if we use this strategy, why not keep an external copy in the wrapper class
 *                 and just make TokenBoard only support case 1???
 *
 *                 No matter what, we need a string copy seems, since directly insert between token
 *                 cause more re-padding. So keep internal or external? Currently I prefer external,
 *                 and tokenboard is just a show board to reflect the text operation.
 *
 *                 Or just do directly tokenbox insert? because this affect only by para-graph, bet-
 *                 ween paragraphes maybe there is blank space left for the last line of the current
 *                 paragraph then we can just add Y for rest of paragraph? This logic will be much 
 *                 more complicated, but useful, since most likely if we insert, we only insert at
 *                 the end of the current line. And for editable tokenboard, get text is expensive 
 *                 but not very often, we only get it when we need to send it.
 *                   
 *                 Event for handling or not:
 *
 *                 1. click, motion,  for sure we need to handle it for trigger event, for select.
 *                 2. ctrl+c/p/x, a/b/c..., Tokenboard won't handle this. alternatively, wrapper of
 *                    tokenboard handle it and query TokenBoard for proper behavor. IE:
 *                          ChatBox get event:
 *                          if it's "a":
 *                             1. if there is selected part, replace this part with ``a"
 *                             2. if not, put ``a" before the cursor.
 *                          if it's click:
 *                             1. directly pass it to tokenboard, to set cursor.
 *                          if it's ctrl-x:
 *                             1. query the tokenboard, if there is selected part, cut it.
 *                             2. otherwise do nothing.
 * ================Analysis on 03/23/2016===========================================================
 *
 *                 1. what's needed?
 *
 *                      What we need is to have class which can support case-1, case-2(a) and case-
 *                      2-(b), for case-1, we need support click event trigger, and the board is as
 *                      non-state class. For case-2(a) we need to support click event trigger, sele-
 *                      ct. For case-2(b) we need to support select, insert.
 *
 *                 2. how to support it?
 *                      Case-1 is simple and already supported. For select, we need to locate the
 *                      token under pointer. For insert we need to support builtin cursor. Both need
 *                      a (int, int) to support. Use (x, y) or (section, offset)?
 *
 *                      Let's use (x, y), since (x, y)->section is quick, but (section, offset)->
 *                      (x, y) is slow.
 *
 *                 3. let me add a (bSelectable, bEditable) to the class, when disable both, we have
 *                    the button-like text-terminal.
 *
 *                    (bSelectable, bEditable) with value:
 *
 *                    1. (0, 0): basic button-like text-terminal
 *                    2. (0, 1): no idea of this mode
 *                    3. (1, 0): sent-message box
 *                    4. (1, 1): input box
 *
 *                    or use (bSelectable, bWithCursor) with value:
 *                    1. (0, 0): basic button-like text-terminal
 *                    2. (0, 1): can't select, but can put cursor everywhere and insert, when push
 *                               and moving mouse, the cursor moving respectively
 *                    3. (1, 0): sent-message box, no cursor shown
 *                    4. (1, 1): classical input box
 *
 *                    Let's use (bSelectable, bWithCursor), having cursor means editable.
 *
 * ===================================================
 *
 *                    Add another flag: bCanThrough, if true
 *
 *
 *                    +-----+  +---+
 *                    |     |  |   |
 *                    |     |  |   |  +----+
 *                L1  +-----+--+   +- |    |  <--- this is can through
 *                             |   |  |    |
 *                             +---+  |    |
 *                           +-----+  |    |
 *                           |     |  |    |
 *                           |     |  |    |
 *                L2  -------+-----+--+----+
 *
 *
 *                    if bCanThrough = false:
 *
 *                    +-----+  +---+
 *                    |     |  |   |
 *                    |     |  |   | 
 *                 L1 +-----+--+   +---------
 *                             |   |
 *                             +---+
 *                                    +----+  <--- this is can't through
 *                                    |    |
 *                                    |    |
 *                           +-----+  |    |
 *                           |     |  |    |
 *                           |     |  |    |
 *                 L2 -------+-----+--+----+
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

#include <SDL2/SDL.h>
#include <vector>
#include <tinyxml2.h>
#include <functional>
#include "section.hpp"
#include "tokenbox.hpp"
#include "widget.hpp"
#include <unordered_map>


    enum XMLObjectType: int{
        OBJECTTYPE_UNKNOWN      = 0,
        OBJECTTYPE_RETURN       = 1,
        OBJECTTYPE_PLAINTEXT    = 2,
        OBJECTTYPE_EVENTTEXT    = 3,
        OBJECTTYPE_EMOTICON     = 4,
        OBJECTTYPE_ENDOFLINE    = 5,
    };

class TokenBoard: public Widget
{
    // +-----------------------------+
    // |           0                 |
    // |  +---------------------+    |
    // |  |XXXXXXXX:)           |    |
    // |3 |XXXXXXXXXXXXXXX      | 1  |
    // |  |          XX         |    |
    // |  +---------------------+    |
    // |                             |
    // |           2                 |
    // +-----------------------------+

    // 1. Marg0 ~ Marg3 is for cursor blitting
    // 2. Internal box is for tokenbox *only*, |X X X  X|, no extra space
    //    any more in it beside the boundary
    // 3. The outer box as a whole to accept events

    public:
        // parameters
        //
        // bSelectable:       can select and copy
        // bWithCursor:       enable with: 1. can insert before cursor
        //                             2. show a cursor
        //                             3. select has nothing to do with current cursor
        // nMaxWidth  :       positive for wrap, non-positive for no-wrap
        // nWordSpace
        // nLineSpace
        //
        TokenBoard(
                int              nX,
                int              nY,
                bool             bSelectable,
                bool             bWithCursor,
                bool             bSpacing,
                bool             bCanThrough,
                int              nMaxWidth       = -1,
                int              nWordSpace      = 0,
                int              nLineSpace      = 0,
                uint8_t          nDefaultFont    = 0,
                uint8_t          nDefaultSize    = 10,
                uint8_t          nDefaultStyle   = 0,
                const SDL_Color &rstDefaultColor = {0XFF, 0XFF, 0XFF, 0XFF},
                int              nMargin0        = 0,
                int              nMargin1        = 0,
                int              nMargin2        = 0,
                int              nMargin3        = 0,
                Widget          *pWidget         = nullptr,
                bool             bFreeWidget     = false):
            Widget(nX, nY, 0, 0, pWidget, bFreeWidget)
            , m_WithCursor(bWithCursor)
            , m_Selectable(bSelectable)
            , m_Spacing(bSpacing)
            , m_CanThrough(bCanThrough)
            , m_PW(nMaxWidth)
            , m_CurrentWidth(0)
            , m_SkipEvent(false)
            , m_Resolution(20)
            , m_WordSpace(nWordSpace)
            , m_LineSpace(nLineSpace)
            , m_CursorLoc(-1, -1)
            , m_DefaultFont(nDefaultFont)
            , m_DefaultSize(nDefaultSize)
            , m_DefaultStyle(nDefaultStyle)
            , m_DefaultColor(rstDefaultColor)
            , m_SkipUpdate(false)
            , m_Margin{
                nMargin0, nMargin1, nMargin2, nMargin3
            }
        {
            if(m_PW > 0){
                m_W = m_PW;
            }
        }

        virtual ~TokenBoard() = default;

    public:
        bool ProcessEvent(const SDL_Event &, bool *);

    public:
        int XMLObjectType(const tinyxml2::XMLElement &);

    public:
        bool    Add(TOKENBOX &);
        void    Clear();
        void    Update(double);
        bool    Empty();
        int     MaxHeight();

    private:
        void GetTokenBoxMetrics(TOKENBOX &, int &, int &, int &, int &);
    private:
        void LoadUTF8CharBoxCache(TOKENBOX &, int);
        void LoadEmoticonCache(TOKENBOX &, int);

    private:
        int  DoPadding(int, int);
        bool InRect(int, int, int, int, int, int);
    private:
        void SetTokenBoxStartX(int);
        void SetTokenBoxStartY(int, int);

    public:
        int     LinePadding(int);
        int     DoLinePadding(int, int, int);
        void ResetLine(int);

    private:
        bool    m_WithCursor;
        bool    m_Selectable;
        bool    m_Spacing;
        bool    m_CanThrough;
        int     m_MaxH1;
        int     m_MaxH2;
        int     m_CurrentLineMaxH2;
        int     m_PW;
        int     m_W;
        int     m_H;
        int     m_CurrentWidth;
        bool    m_SkipEvent;

    private:
        const TOKENBOX *m_LastTokenBox;

    private:
        void UpdateSection(SECTION &, Uint32);

    public:
        int W();
        int H();

    private:
        const tinyxml2::XMLElement *NextObject(const tinyxml2::XMLElement *);
        void AddNewTokenBoxLine(bool);

    private:
        int  TokenBoxType(const TOKENBOX &);

    public:
        // load the content and it's callback table
        bool Load(const tinyxml2::XMLDocument &,
                const std::unordered_map<std::string, std::function<void()>> &);

    private:
        bool ParseXMLContent(const tinyxml2::XMLElement *);

    private:
        bool ParseReturnObject();
        bool ParseEmoticonObject(const tinyxml2::XMLElement &);
        bool ParseTextObject(const tinyxml2::XMLElement &,
                int, const std::unordered_map<std::string, std::function<void()>> &);

    private:
        int CreateSection(const SECTION &, std::function<void()>);
    private:
        bool GetAttributeColor(SDL_Color *, const SDL_Color &,
                const tinyxml2::XMLElement &, const std::vector<std::string> &);
        bool GetAttributeAtoi(int *, int,
                const tinyxml2::XMLElement &, const std::vector<std::string> &);

    private:
        SDL_Color   GetFontColor(const tinyxml2::XMLElement &);
        int         GetFontIndex(const tinyxml2::XMLElement &);
        int         GetFontStyle(const tinyxml2::XMLElement &);
        int         GetFontSize (const tinyxml2::XMLElement &);

    private:
        SDL_Color   GetEventTextCharColor(const tinyxml2::XMLElement &);
        SDL_Color   GetEventTextCharColor(const tinyxml2::XMLElement &, int);

    private:
        void        ParseTextContentSection(const tinyxml2::XMLElement *, int);

    private:
        int         GetEmoticonSet  (const tinyxml2::XMLElement &);
        int         GetEmoticonIndex(const tinyxml2::XMLElement &);

    public:
        bool ObjectEmocticon(const tinyxml2::XMLElement &);
        bool ObjectReturn(const tinyxml2::XMLElement &);
        bool ObjectEventText(const tinyxml2::XMLElement &);


    private:
        void RedrawToken(int, int, TOKENBOX &, bool);
        bool DrawTextureCache();

    private:
        bool ParseXML(const char *);

    public:
        void Draw(int nX, int nY)
        {
            DrawEx(nX, nY, 0, 0, W(), H());
        }

    public:
        void DrawEx(int, int, int, int, int, int);

    private:
        bool AddNewTokenBox(TOKENBOX &);

    public:

    private:
        int GetNthLineIntervalMaxH2(int, int, int);
        int GetNthLineTokenBoxStartY(int, int, int, int);
        int GetNthNewLineStartY(int);

        bool GetTokenBoxLocation(int, int, int &, int &, int &, int &);
        bool GetTokenBoxStartPoint(int, int, int &, int &);
        void SetDrawToTextureCache();
        void SetDrawToScreen();

    private:
        void ClearCurrentLine();

    public:
        int Width();
        int Height();
    private:
        void RedrawSection(int);

    private:
        std::vector<std::vector<TOKENBOX>> m_LineV;
        std::vector<TOKENBOX>              m_CurrentLine;
        std::unordered_map<int, SECTION>   m_SectionV;
        std::vector<int>                   m_LineStartY;
    private:
        std::vector<std::vector<std::vector<std::pair<int, int>>>> m_TokenBoxBitmap;

    private:
        void ResetCurrentLine();

    private:
        void MakeTokenBoxEventBitmap();
        void MarkTokenBoxEventBitmap(int, int);
        int  m_Resolution;
        int  m_WordSpace;
        int  m_LineSpace;

    private:
        std::pair<int, int> m_CursorLoc;

    private:
        // this is used when insert words, empty lines, etc.
        uint8_t   m_DefaultFont;
        uint8_t   m_DefaultSize;
        uint8_t   m_DefaultStyle;
        SDL_Color m_DefaultColor;

        bool      m_SkipUpdate;

    private:
        // margins for the board, this is needed for balabala..
        //
        //  +-------------------------+
        //  |        M0               |
        //  |  +-------------+        |
        //  |  |             |        |
        //  |M3|             |  M1    |
        //  |  |             |        |
        //  |  +-------------+        |
        //  |        M2               |
        //  +-------------------------+
        //
        int  m_Margin[4];

        std::vector<bool> m_EndWithReturn;

    private:
        // callbacks
        std::unordered_map<int, std::function<void()>> m_IDFuncV;

    private:
        int SectionTypeCount(int, int);

        void DrawRectLine(const SDL_Rect &);

    public:
        const std::string &ContentExport();
        int GuessResoltion();

        void TokenBoxGetMouseButtonUp(int, int, bool);
        void TokenBoxGetMouseButtonDown(int, int, bool);
        void TokenBoxGetMouseMotion(int, int, bool);

        void ProcessEventMouseButtonUp(int, int);
        void ProcessEventMouseButtonDown(int, int);
        void ProcessEventMouseMotion(int, int);

    public:
        bool AddTokenBoxV(int, int, const std::vector<TOKENBOX> &);

    public:
        void GetCursor(int *pX, int *pY)
        {
            if(pX){ *pX = m_CursorLoc.first;  }
            if(pY){ *pY = m_CursorLoc.second; }
        }

        int GetWordSpace()
        {
            return m_WordSpace;
        }

        int GetLineSpace()
        {
            return m_LineSpace;
        }

        void Delete(bool);


        bool AddTokenBoxV(const std::vector<TOKENBOX> &rstTBV)
        {
            return AddTokenBoxV(m_CursorLoc.first, m_CursorLoc.second, rstTBV);
        }

        // always we need an default environment
        void SetDefaultFont(
                uint8_t nFont, uint8_t nSize, uint8_t nStyle, const SDL_Color &rstColor)
        {
            m_DefaultFont  = nFont;
            m_DefaultSize  = nSize;
            m_DefaultStyle = nStyle;
            m_DefaultColor = rstColor;
        }


    public:
        const tinyxml2::XMLElement *XMLFirstObject(const tinyxml2::XMLElement &);
        const tinyxml2::XMLElement *XMLNextObject(const tinyxml2::XMLElement &);
        bool  LoadXML(const char *, const std::unordered_map<std::string, std::function<void()>> &);
        bool  InnInsert(const tinyxml2::XMLDocument &, const std::unordered_map<std::string, std::function<void()>> &);

        int LineFullWidth(int);
        int LineRawWidth(int, bool);
        int SetTokenBoxWordSpace(int);

        std::pair<int, int> m_LastTokenBoxLoc;

    private:
        bool TokenBoxValid(int nX, int nY)
        {
            return true
                && nY >= 0
                && nY < (int)m_LineV.size()
                && nX >= 0
                && nX < (int)m_LineV[nY].size();
        }

        bool LastTokenBoxValid()
        {
            return TokenBoxValid(m_LastTokenBoxLoc.first, m_LastTokenBoxLoc.second);
        }


        std::string GetXML(bool);


        std::string InnGetXML(int, int, int, int);

        bool GetTokenBoxInfo(int, int, int *, int *, int *, int *, int *, int *, int *);

        void DeleteTokenBox(int, int, int, int);
    private:

        std::pair<int, int> m_SelectLoc[2];

    private:
        int     m_SelectState;  // 0: no selection
        // 1: selecting
        // 2: selection done with result available
};