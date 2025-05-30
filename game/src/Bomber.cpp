//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Bomber.cpp                                //
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

//Header
#include "Bomber.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kSpriteFrames = 3;

constexpr int kFrameIndex_Happy    = 1;
constexpr int kFrameIndex_Sad      = 0;
constexpr int kFrameIndex_BigMouth = 2;

constexpr int kBodyOffsetY =  10;
constexpr int kBombOffsetX =   5;
constexpr int kBombOffsetY = -45;

constexpr int kMoveMinDisplacement = 50;
constexpr int kMoveMaxDisplacement = 200;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Bomber::Bomber() :
    //Sprite / Animation
    //m_sprite       - Default initialized.
    //m_spriteFrames - Default initialized.
    m_frameIndex(kFrameIndex_Sad),
    //Movement / Bounds
    m_speed          (Lore::Vector2::Zero()),
    m_initialPosition(Lore::Vector2::Zero()),
    m_minBounds      (0),
    m_maxBounds      (0),
    //Turn / Bombs
    //m_turnInfo - Initialized in reset.
    m_bombsDropped   (0),
    m_bombsRemaining (0),
    m_isDroppingBombs(0)
    //Callbacks
    //m_bombDroppedCallback - Default initialized.
{
    initSprites();
}

Bomber::~Bomber()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Bomber::update(float dt)
{
    //Did drop all bombs already...
    if(!m_isDroppingBombs)
        return;

    auto x = m_sprite.getPosition().x;

    //Reach the drop spot - Drop a bomb.
    if((x <= m_dropSpot && m_speed.x < 0) ||
       (x >= m_dropSpot && m_speed.x > 0))
    {
        dropBomb();
        deciceNextDropSpot();
    }

    //Not at drop stop - Move towards it.
    else
    {
        m_sprite.move(m_speed * dt);
    }
}

void Bomber::draw()
{
    m_sprite.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomber::reset(const TurnInfo &turnInfo)
{
    m_isDroppingBombs = false;
    m_turnInfo        = turnInfo;
    m_bombsRemaining  = m_turnInfo.bombsCount;
    m_bombsDropped    = 0;
}

void Bomber::startDropBombs()
{
    m_isDroppingBombs = true;

    changeSpriteFrame(kFrameIndex_BigMouth);
    deciceNextDropSpot();
}

void Bomber::stopDropBombs()
{
    m_isDroppingBombs = false;
}

void Bomber::makeWinTurn()
{
    changeSpriteFrame(kFrameIndex_Happy);
}

void Bomber::makeLoseTurn()
{
    changeSpriteFrame(kFrameIndex_Sad);
}



////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
//Position / Movement
void Bomber::setInitialPosition(int x, int y)
{
    m_initialPosition.x = x - m_sprite.getBounds().w / 2;
    m_initialPosition.y = y + kBodyOffsetY;

    m_sprite.setOrigin(Lore::ITransformable::OriginHelpers::BottomLeft());
    m_sprite.setPosition(m_initialPosition);
}

void Bomber::setMovementBounds(int min, int max)
{
    m_minBounds = min;
    m_maxBounds = max - m_sprite.getBounds().w;
}


//Callbacks
void Bomber::setOnBombDroppedCallback(const BombDroppedCallback &callback)
{
    m_bombDroppedCallback = callback;
}


////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
int Bomber::getTurnBombsDroppedCount() const
{
    return m_bombsDropped;
}

int Bomber::getTurnBombsRemainingCount() const
{
    return m_bombsRemaining;
}


bool Bomber::isDroppingBombs() const
{
    return m_isDroppingBombs;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Bomber::initSprites()
{
    m_sprite.loadTexture("Bomber.png");

    //Get the Frame Properties.
    auto rect   = m_sprite.getSourceRectangle();
    auto frameW = rect.w  / kSpriteFrames;
    auto frameH = rect.h;

    //Create the Frames Rectangles.
    m_spriteFrames.reserve(kSpriteFrames);

    for(int i = 0; i < kSpriteFrames; ++i)
    {
        Rectangle r = {};
        r.x = i * frameW;
        r.y = 0;
        r.w = frameW;
        r.h = frameH;
        m_spriteFrames.push_back(r);
    }

    //Set the initial frame.
    changeSpriteFrame(kFrameIndex_Happy);
}

void Bomber::changeSpriteFrame(int frameIndex)
{
    m_frameIndex = frameIndex;
    m_sprite.setSourceRectangle(m_spriteFrames[m_frameIndex]);
}

void Bomber::deciceNextDropSpot()
{
    auto gm = Lore::GameManager::instance();

    int displacement = gm->getRandomNumber(kMoveMinDisplacement,
                                           kMoveMaxDisplacement);
    int direction = (gm->getRandomBool()) ? -1 : 1;
    int currX     = m_sprite.getPosition().x;

    //Bomber will go out of bounds - Go to the other direction instead.
    if((currX - displacement < m_minBounds && direction < 0) ||
       (currX + displacement > m_maxBounds && direction > 0))
    {
        direction *= -1;
    }

    m_speed.x  = m_turnInfo.bomberSpeed * direction;
    m_dropSpot = currX + (displacement * direction);
 }

void Bomber::dropBomb()
{
    //Dropped all bombs?
    if(m_bombsRemaining == 0)
    {
        KABOOM_DLOG("Bomber::dropBomb - All bombs has been dropped");

        m_isDroppingBombs = false;
        changeSpriteFrame(kFrameIndex_Happy);

        return;
    }

    //Update the bombs stats.
    --m_bombsRemaining;
    ++m_bombsDropped;

    //Adjust the bomb to be placed where the bomber is.
    auto bombPosition = m_sprite.getPosition();
    bombPosition.x += kBombOffsetX;
    bombPosition.y += kBombOffsetY;
    m_bombDroppedCallback(bombPosition);

    KABOOM_DLOG("Bomb dropped - Dropped %d - Remaining %d",
                m_bombsDropped,
                m_bombsRemaining);
}
