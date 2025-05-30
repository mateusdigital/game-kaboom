//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        WindowManager.cpp                         //
//            █ █        █ █        Lore                                      //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016, 2017                  //
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
#include "../include/WindowManager.h"
//Lore
#include "../include/AssetsManager.h"
#include "../include/SDLHelpers.h"


//Usings
USING_NS_LORE


// Init / Shutdown //
void WindowManager::initialize(const std::string &caption,
                               int designWidth, int designHeight,
                               int windowWidth, int windowHeight,
                               Uint32 windowFlags,
                               Uint32 rendererFlags)
{
    //Set the vars.
    m_designRect.x = 0; 
    m_designRect.y = 0;
    m_designRect.w = designWidth;
    m_designRect.h = designHeight;

    m_windowRect.x = 0; 
    m_windowRect.y = 0; 
    m_windowRect.w = windowWidth;
    m_windowRect.h = windowHeight;


    //COWTODO: Check the errors...
    //SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Window
    m_pWindow = SDL_CreateWindow(caption.c_str(),
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 m_windowRect.w,
                                 m_windowRect.h,
                                 windowFlags);

    //Renderer
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, rendererFlags);

    Color c = {};
    setClearColor(c);
}

void WindowManager::shutdown()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow  (m_pWindow);
}

// Draw //
void WindowManager::clear()
{
    SDL_RenderClear(m_pRenderer);
}

void WindowManager::render()
{
    SDL_RenderPresent(m_pRenderer);
}


// Public Methods //
//Renderer
SDL_Renderer* WindowManager::getRenderer() const
{
    return m_pRenderer;
}

//Design Size
const Rectangle& WindowManager::getDesignRect() const
{
    return m_designRect;
}

int WindowManager::getDesignWidth() const
{
    return m_designRect.w;
}

int WindowManager::getDesignHeight() const
{
    return m_designRect.h;
}

//Window Size
const Rectangle& WindowManager::getWindowRect() const
{
    return m_windowRect;
}

int WindowManager::getWindowWidth() const
{
    return m_windowRect.w;
}

int WindowManager::getWindowHeight() const
{
    return m_windowRect.h;
}

//Clear color
void WindowManager::setClearColor(const Color &color)
{
    m_clearColor = color;
    SDL_SetRenderDrawColor(m_pRenderer,
                           color.r,
                           color.g,
                           color.b,
                           255);
}

const Color& WindowManager::getClearColor() const
{
    return m_clearColor;
}

//Icon
void WindowManager::setIcon(const std::string &filename)
{
    auto full_filename = AssetsManager::instance()->fullpath(filename);
    auto pSurface      = SDLHelpers::load_surface_from_file(full_filename);


    //COWTODO: Check errors.

    SDL_SetWindowIcon(m_pWindow, pSurface);

    SDL_FreeSurface(pSurface);
}
