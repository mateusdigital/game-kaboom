//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Bomber.h                                  //
//            █ █        █ █        Game_Kaboom                               //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __Game_Kaboom_include_Bomber_h__
#define __Game_Kaboom_include_Bomber_h__

//std
#include <functional>
//Game_Kaboom
#include "GameKaboom_Utils.h"
#include "TurnInfo.h"


NS_GAMEKABOOM_BEGIN

class Bomber : public Lore::IDrawable, public Lore::IUpdatable
{
    // Enums / Constants / Typdefs //
public:
    typedef std::function<void (const Lore::Vector2 &bombPos)> BombDroppedCallback;

private:
    enum class MoveState { MovingToTarget, DroppingBomb };


    // CTOR / DTOR //
public:
    Bomber();
    virtual ~Bomber();


    // Update / Draw //
public:
    virtual void update(float dt) override;
    virtual void draw()           override;


    // Actions //
public:
    void reset(const TurnInfo &turnInfo);

    void startDropBombs();
    void stopDropBombs ();

    void makeWinTurn ();
    void makeLoseTurn();


    // Setters //
public:
    //Position / Movement
    void setInitialPosition(int x, int y);
    void setMovementBounds(int min, int max);

    //Callbacks
    void setOnBombDroppedCallback(const BombDroppedCallback &callback);


    // Getters //
public:
    int getTurnBombsDroppedCount  () const;
    int getTurnBombsRemainingCount() const;

    bool isDroppingBombs() const;


    // Private Methods //
private:
    void initSprites();

    void changeSpriteFrame(int frameIndex);

    void deciceNextDropSpot();
    void dropBomb();

    // iVars //
private:
    //Sprite / Animation
    Lore::Sprite                 m_sprite;
    std::vector<Rectangle> m_spriteFrames;
    int                          m_frameIndex;

    //Movement / Bounds
    Lore::Vector2 m_speed;
    Lore::Vector2 m_initialPosition;
    int           m_minBounds;
    int           m_maxBounds;

    //Turn / Bombs
    TurnInfo m_turnInfo;
    int      m_bombsDropped;
    int      m_bombsRemaining;

    bool m_isDroppingBombs;

    //Callbacks
    BombDroppedCallback m_bombDroppedCallback;

    MoveState m_moveState;
    float     m_dropSpot;
};

NS_GAMEKABOOM_END
#endif // __Game_Kaboom_include_Bomber_h__ //
