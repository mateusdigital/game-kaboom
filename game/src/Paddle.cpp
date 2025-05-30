//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Paddle.cpp                                //
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
#include "Paddle.h"

//Usings
USING_NS_GAMEKABOOM;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr int   kInitialLivesCount   = 1;
constexpr int   kPaddleOffsetY       = 55;
constexpr int   kFramesCount         = 4;
constexpr float kAnimationInterval   = 0.1;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Paddle::Paddle() :
    //HouseKeeping
    m_basePosition(Lore::Vector2::Zero()),
    m_speed       (Lore::Vector2::Zero()),    
    m_lives       (kInitialLivesCount),
    //Movement
    m_maxX(0),
    m_minX(0)
    //m_spritesInfoVec - Initialized in initSprites
{
    initSprites();
}

Paddle::~Paddle()
{
    //Empty...
}


////////////////////////////////////////////////////////////////////////////////
// Update / Draw                                                              //
////////////////////////////////////////////////////////////////////////////////
void Paddle::update(float dt)
{
    handleInput();
    m_basePosition = m_basePosition + (m_speed * dt);

    //Calculate the bounds.
         if(m_basePosition.x < m_minX) m_basePosition.x = m_minX;
    else if(m_basePosition.x > m_maxX) m_basePosition.x = m_maxX;

    for(int i = 0; i < m_lives; ++i)
        m_spritesInfoVec[i].update(dt);
}

void Paddle::draw()
{
    for(int i = 0; i < m_lives; ++i)
        m_spritesInfoVec[i].draw(m_basePosition, kPaddleOffsetY * i);
}


////////////////////////////////////////////////////////////////////////////////
// Setters                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Paddle::setInitialPosition(int x, int y)
{
    m_basePosition.x = x - m_spritesInfoVec[0].frames[0].w / 2;
    m_basePosition.y = y;
}

void Paddle::setMovementBounds(int min, int max)
{
    m_minX = min;
    m_maxX = max - m_spritesInfoVec[0].frames[0].w;
}


////////////////////////////////////////////////////////////////////////////////
// Getters                                                                    //
////////////////////////////////////////////////////////////////////////////////
const Lore::Vector2& Paddle::getPosition() const
{
    return m_basePosition;
}

int Paddle::getLives() const
{
    return m_lives;
}


////////////////////////////////////////////////////////////////////////////////
// Actions                                                                    //
////////////////////////////////////////////////////////////////////////////////
void Paddle::kill()
{
    --m_lives;
}

bool Paddle::checkCollision(const Rectangle &rect)
{
    for(int i = 0; i < m_lives; ++i)
    {
        auto paddleRect = m_spritesInfoVec[i].sprite.getBounds();
		auto result = SDL_IntersectRect(
			&paddleRect,
			&rect,
			&paddleRect
		);
        if(result)
        {
            m_spritesInfoVec[i].start();
            return true;
        }
    }

    return false;
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Inits
void Paddle::initSprites()
{
    m_basePosition = Lore::Vector2(100, 200);

    //Init the sprite and frames.
    Lore::Sprite sprite("Paddle.png");
    auto spriteBounds = sprite.getBounds();
    auto frameWidth   = spriteBounds.w / kFramesCount;
    auto frameHeight  = spriteBounds.h;

    std::vector<Rectangle> framesVec;
    framesVec.reserve(kFramesCount);

    for(int i = 0; i < kFramesCount; ++i)
    {
        Rectangle r = {};
        r.x = i * frameWidth;
        r.y = 0;
        r.w = frameWidth;
        r.h = frameHeight;
        framesVec.push_back(r);
    }


    //Init the Animation info.
    m_spritesInfoVec.reserve(kInitialLivesCount);
    for(int i = 0; i < kInitialLivesCount; ++i)
    {
        m_spritesInfoVec.push_back(Paddle::AnimationInfo());
        auto &anim = m_spritesInfoVec[i];

        CoreClock::Clock timer(kAnimationInterval, 4, [&](){
            anim.increaseFrame();
        });

        anim.sprite     = sprite;
        anim.frameIndex = 0;
        anim.frames     = framesVec;
        anim.timer      = timer;

        anim.resetFrame();
    }
}

//Input
void Paddle::handleInput()
{
    auto inputMgr = Lore::InputManager::instance();

    m_speed = Lore::Vector2::Zero();
    if(inputMgr->isKeyDown(SDL_SCANCODE_LEFT))
        m_speed.x += -800;
    if(inputMgr->isKeyDown(SDL_SCANCODE_RIGHT))
        m_speed.x += +800;
}


////////////////////////////////////////////////////////////////////////////////
// Animation Info Methods                                                     //
////////////////////////////////////////////////////////////////////////////////
void Paddle::AnimationInfo::start()
{
    KABOOM_DLOG("Starting paddle hit timer");

    resetFrame();

    timer.stop();
    timer.start();
}

void Paddle::AnimationInfo::update(float dt)
{
    timer.update(dt);
}

void Paddle::AnimationInfo::draw(const Lore::Vector2 &pos, int yOffset)
{
    sprite.setPosition(pos.x, pos.y + yOffset);
    sprite.draw();
}

void Paddle::AnimationInfo::resetFrame()
{
    changeFrame(0);
}

void Paddle::AnimationInfo::increaseFrame()
{
    frameIndex = (frameIndex + 1) % kFramesCount;
    changeFrame(frameIndex);
}

void Paddle::AnimationInfo::changeFrame(int index)
{
    frameIndex = index;
    sprite.setSourceRectangle(frames[frameIndex]);

    KABOOM_DLOG("Chaging Paddle frame to index: %d", frameIndex);
}
