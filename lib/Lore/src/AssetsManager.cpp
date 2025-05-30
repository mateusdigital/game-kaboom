//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        AssetsManager.cpp                         //
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
#include "../include/AssetsManager.h"
//std
#include <sys/types.h> //For stat(2)
#include <sys/stat.h>  //For stat(2)
#include <errno.h>
//Lore
#include "../include/SDLHelpers.h"
#include "../include/WindowManager.h"
//Lore_Private
#include "./private/include/Lore_Private_Utils.h"
#include "./private/include/Log.h"

//Usings
USING_NS_LORE;
#include <filesystem>

namespace fs = std::filesystem;


////////////////////////////////////////////////////////////////////////////////
// Init / Shutdown                                                            //
////////////////////////////////////////////////////////////////////////////////
void AssetsManager::initialize(const std::string& searchPath)
{
    AssetsManager::initialize(std::vector<std::string>{searchPath});
}

void AssetsManager::initialize(const std::vector<std::string> &searchPaths)
{
    PVT_LORE_DLOG_DEBUG(
        "AssetsManager::initialize",
        "Search Paths size: (%d)",
        searchPaths.size()
    );
    
    for(auto path : searchPaths)
    {
        struct stat status;
        stat(path.c_str(), &status);

        PVT_LORE_DLOG_DEBUG(
            "AssetsManager::initialize",
            "Checking path: (%s)",
            path.c_str()
        );

        auto p = fs::current_path();
        auto pp = p.assign("assets");

        if(fs::is_directory(path))
        {
            PVT_LORE_DLOG_DEBUG(
                "AssetsManager::initialize",
                "Found valid search path: (%s)",
                path.c_str()
            );

            m_searchPath = path;
            break;
        }
    }

    if(m_searchPath.back() != '/')
        m_searchPath += "/";


    //COWTODO: Check errors.
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
}

void AssetsManager::shutdown()
{
}


////////////////////////////////////////////////////////////////////////////////
// Public Functions                                                           //
////////////////////////////////////////////////////////////////////////////////
Texture::SPtr AssetsManager::getTexture(const std::string &filename)
{
    auto it = m_texturesMap.find(filename);
    if(it == std::end(m_texturesMap))
        return loadTexture(filename);

    return it->second;
}

Font::SPtr AssetsManager::getFont(const std::string &filename, int size)
{
    auto it = m_fontsMap.find(std::make_pair(filename, size));
    if(it == std::end(m_fontsMap))
        return loadFont(filename, size);

    return it->second;
}

std::string AssetsManager::fullpath(const std::string &filename) const
{
    return m_searchPath + filename;
}

// @XXX(stdmatt): Very hacky way to check if the file exists...
// Doing this because the compiler on mac doesn't provide access to the
// std;:experimental::filesystem stuff...
bool HACK_file_exists(std::string const &filename)
{
    std::ifstream infile(filename.c_str());
    return infile.good();
}

std::vector<std::string> AssetsManager::checkFilesExists(
    const std::vector<std::string> &filesList) const
{
    std::vector<std::string> missingFiles;
    missingFiles.reserve(filesList.size());

    for(auto &filename : filesList)
    {
        if(!HACK_file_exists(fullpath(filename)))
            missingFiles.push_back(filename);
    }

    return missingFiles;
}


////////////////////////////////////////////////////////////////////////////////
// Private Functions                                                          //
////////////////////////////////////////////////////////////////////////////////
Texture::SPtr AssetsManager::loadTexture(const std::string &filename)
{
    PVT_LORE_DLOG_DEBUG(
        "AssetsManager::loadTexture",
        "Filename: (%s)",
        filename.c_str()
    );

    auto sdlTexture = SDLHelpers::load_texture_from_file(fullpath(filename));
    auto texture    = std::make_shared<Texture>(sdlTexture);

    m_texturesMap[filename] = texture;

    return texture;
}

Font::SPtr AssetsManager::loadFont(const std::string &filename,
                                   int size)
{
    PVT_LORE_DLOG_DEBUG(
        "AssetsManager::loadFont",
        "Filename: (%s) - Size: (%d)",
        filename.c_str(),
        size
    );

    auto sdlFont   = SDLHelpers::load_font_from_file(fullpath(filename), size);
    auto font      = std::make_shared<Font>(sdlFont);
    auto fontValue = std::make_pair(filename, size);

    m_fontsMap[fontValue] = font;

    return font;
}

