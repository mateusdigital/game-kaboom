//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Bomb.cpp                                  //
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
#include "Bomb.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int kSpriteFramesCount_Alive    = 4;
constexpr int kSpriteFramesCount_Exploded = 3;

constexpr float kTimerSpriteFrameChange_Alive     = 0.10f;
constexpr float kTimerSpriteFrameChange_Exploding = 0.04f;
constexpr int   kRepeatCount_Exploding            = 5;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Bomb::Bomb() :
    //HouseKeeping
    //m_turnInfo - Set in reset.
    m_state(Bomb::State::Dead),
    //Sprite / Animation
    //m_aliveAnimation     - Initialized in InitAnimations
    //m_explodingAnimation - Initialized in InitAnimations
    m_pCurrentAnimation(nullptr),
    //Movement / Bounds
    m_pos            (Lore::Vector2::Zero()),
    m_speed          (Lore::Vector2::Zero()),
    m_maxY           (0),
    //Callback
    m_reachTargetCallback     (nullptr),
    m_explodedFinishedCallback(nullptr)
{
    setOnReachTargetCallback(ReachTargetCallback());
    initAnimations();
    initTimers    ();
}

Bomb::~Bomb()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Bomb::update(float dt)
{
    if(m_state == Bomb::State::Dead)
        return;

    //Update timers.
    m_aliveAnimation.update    (dt);
    m_explodingAnimation.update(dt);

    //Just move if it is alive.
    if(m_state == Bomb::State::Alive)
    {
        setPosition(getPosition() + (m_speed * dt));

        if(getPosition().y >= m_maxY && m_reachTargetCallback)
            m_reachTargetCallback();
    }
}

void Bomb::draw()
{
    if(m_state == Bomb::State::Dead)
        return;

    m_pCurrentAnimation->draw(m_pos);
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomb::reset(const TurnInfo &turnInfo)
{
    m_turnInfo = turnInfo;

    m_state   = Bomb::State::Dead;
    m_speed.y = m_turnInfo.bombSpeed;
}

void Bomb::explode()
{
    m_state = Bomb::State::Exploding;

    m_pCurrentAnimation->stop();
    m_pCurrentAnimation = &m_explodingAnimation;
    m_pCurrentAnimation->start();
}

void Bomb::startDropping()
{
    m_state = Bomb::State::Alive;

    m_pCurrentAnimation->stop();
    m_pCurrentAnimation = &m_aliveAnimation;
    m_pCurrentAnimation->start();

    auto flipped = Lore::GameManager::instance()->getRandomBool();
    m_pCurrentAnimation->sprite.setFlipX(flipped);
}

void Bomb::stopDropping()
{
    m_speed = Lore::Vector2::Zero();
}

void Bomb::kill()
{
    KABOOM_DLOG("Killing bomb.");
    m_state = Bomb::State::Dead;
}


////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Bomb::setPosition(const Lore::Vector2 &pos)
{
    m_pos = pos;
    m_hitBox.x = m_pos.getX();
    m_hitBox.y = m_pos.getY();
}

void Bomb::setPosition(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
    m_hitBox.x = x;
    m_hitBox.y = y;
}

void Bomb::setMovementBounds(int maxY)
{
    m_maxY = maxY;
}

void Bomb::setOnReachTargetCallback(const ReachTargetCallback &callback)
{
    m_reachTargetCallback = callback;
}

void Bomb::setOnExplodeFinishedCallback(const ExplodeFinishedCallback &callback)
{
    m_explodedFinishedCallback = callback;
}



////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
const Lore::Vector2& Bomb::getPosition() const
{
    return m_pos;
}

const Rectangle& Bomb::getHitBox() const
{
    return m_hitBox;
}

Bomb::State Bomb::getState() const
{
    return m_state;
}



////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Inits
void Bomb::initAnimations()
{
    //Setup the Frames.
    m_aliveAnimation.name = "Alive";
    m_aliveAnimation.setupFrames("Bomb_Alive.png",
                                  kSpriteFramesCount_Alive);
    m_aliveAnimation.changeFrame(0);

    m_explodingAnimation.name = "Exploding";
    m_explodingAnimation.setupFrames("Bomb_Exploded.png",
                                     kSpriteFramesCount_Exploded);
    m_explodingAnimation.changeFrame(0);

    //Set the pointers.
    m_pCurrentAnimation = &m_aliveAnimation;

    //Set the hit box.
    auto s = m_pCurrentAnimation->framesVec[0];
	m_hitBox.w = s.w;
    m_hitBox.h = s.h;
}

void Bomb::initTimers()
{
    //Setup the Alive Timer
    m_aliveAnimation.setupTimer(
            kTimerSpriteFrameChange_Alive,
            CoreClock::Clock::kRepeatForever,
            COREGAME_CALLBACK_0(Bomb::onAliveAnimationTimerTick, this),
            [](){} //Empty callback.
    );

    //Setup the Exploding Timer
    m_explodingAnimation.setupTimer(
            kTimerSpriteFrameChange_Exploding,
            kRepeatCount_Exploding,
            COREGAME_CALLBACK_0(Bomb::onExplodingAnimationTimerTick, this),
            COREGAME_CALLBACK_0(Bomb::onExplodingAnimationFinished,  this)
    );
}


//Timer Callback
void Bomb::onAliveAnimationTimerTick()
{
    m_pCurrentAnimation->incrementFrame();
}

void Bomb::onExplodingAnimationTimerTick()
{
    auto gameMgr = Lore::GameManager::instance();
    auto framesCount = m_pCurrentAnimation->framesVec.size() - 1;

    auto r = gameMgr->getRandomNumber(0, 255);
    auto g = gameMgr->getRandomNumber(0, 255);
    auto b = gameMgr->getRandomNumber(0, 255);

    auto frameIndex = gameMgr->getRandomNumber(0, framesCount);

    Color c = {};
    c.r = r;
    c.g = g;
    c.b = b; 
    c.a = 255;

    m_pCurrentAnimation->sprite.setColor(c);
    m_pCurrentAnimation->changeFrame(frameIndex);
}

void Bomb::onExplodingAnimationFinished()
{
    m_state = Bomb::State::Dead;
    if(m_explodedFinishedCallback)
        m_explodedFinishedCallback();
}



////////////////////////////////////////////////////////////////////////////////
// Bomb Animation Info                                                        //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Animation Management                                                       //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::start()
{
    timer.start();
    auto gm = Lore::GameManager::instance();
    frameIndex = gm->getRandomNumber(0, framesVec.size()-1);
    changeFrame(frameIndex);
}

void Bomb::AnimationInfo::stop()
{
    timer.stop();
}


////////////////////////////////////////////////////////////////////////////////
// Frame Management                                                           //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::incrementFrame()
{
    frameIndex = (frameIndex + 1) % framesVec.size();
    changeFrame(frameIndex);
}

void Bomb::AnimationInfo::changeFrame(int index)
{
    KABOOM_DLOG("Bomb::AnimationInfo::changeFrame %d", index);

    COREGAME_ASSERT_ARGS(
        index >= 0 && index < (int)framesVec.size(),
        "Bomb::AnimationInfo::changeFrame received an invalid index (%d)",
        index
    );

    sprite.setSourceRectangle(framesVec[index]);
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::update(float dt)
{
    timer.update(dt);
}

void Bomb::AnimationInfo::draw(const Lore::Vector2 &pos)
{
    sprite.setPosition(pos);
    sprite.draw();
}


////////////////////////////////////////////////////////////////////////////////
// Setup                                                                      //
////////////////////////////////////////////////////////////////////////////////
void Bomb::AnimationInfo::setupFrames(const std::string &spriteName,
                                      int framesCount)
{
    //Load the texture.
    sprite.loadTexture(spriteName);

    //Get the Frame Properties.
    auto rect   = sprite.getSourceRectangle();
    auto frameW = rect.w / framesCount;
    auto frameH = rect.h;

    //Create the Frames Rectangles.
    framesVec.reserve(framesCount);

    for(int i = 0; i < framesCount; ++i)
    {
        Rectangle r;
        r.x = i * frameW;
        r.y = 0;
        r.w = frameW;
        r.h = frameH;

        framesVec.push_back(r);
    }

    frameIndex = 0;
    changeFrame(frameIndex);
}

void Bomb::AnimationInfo::setupTimer(float interval,
                                     int repeatCount,
                                     const CoreClock::Clock::Callback &tickCallback,
                                     const CoreClock::Clock::Callback &doneCallback)
{
    timer.setInterval    (interval);
    timer.setRepeatCount (repeatCount);
    timer.setTickCallback(tickCallback);
    timer.setDoneCallback(doneCallback);
}
