cmake_minimum_required(VERSION 3.10)
project(kaboom)

set(GAME_NAME kaboom)
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR}/../)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Source files
file(GLOB_RECURSE LIB_SRC ${PROJECT_ROOT_DIR}/lib/*.cpp)
file(GLOB_RECURSE GAME_SRC ${PROJECT_ROOT_DIR}/game/*.cpp)
add_executable(${GAME_NAME} ${LIB_SRC} ${GAME_SRC})

# Common includes
include_directories(
    ${PROJECT_ROOT_DIR}/lib/Lore
    ${PROJECT_ROOT_DIR}/lib/Lore/lib/CoreClock/include
    ${PROJECT_ROOT_DIR}/lib/Lore/lib/CoreGame/include
    ${PROJECT_ROOT_DIR}/lib/Lore/lib/CoreRandom/include
    ${PROJECT_ROOT_DIR}/game/include
)

message(STATUS "Building Kaboom")
message(STATUS "Detected system processor: ${CMAKE_SYSTEM_PROCESSOR}")

if(WIN32)
    message(STATUS "... - For Windows")
    # SDL2 setup from third_party
    set(WIN_LIB ${PROJECT_ROOT_DIR}/lib/sdl2-win)

    set(SDL2_DIR       "${WIN_LIB}/SDL2-2.32.6")
    set(SDL2_IMAGE_DIR "${WIN_LIB}/SDL2_image-2.5.2")
    set(SDL2_TTF_DIR   "${WIN_LIB}/SDL2_ttf-2.24.0")
    set(SDL2_MIXER_DIR "${WIN_LIB}/SDL2_mixer-2.8.1")

    include_directories(
        ${SDL2_DIR}/include
        ${SDL2_IMAGE_DIR}/include
        ${SDL2_TTF_DIR}/include
        ${SDL2_MIXER_DIR}/include
    )

    target_link_libraries(${GAME_NAME}
        "${SDL2_DIR}/lib/x64/SDL2.lib"
        "${SDL2_DIR}/lib/x64/SDL2main.lib"
        "${SDL2_IMAGE_DIR}/lib/x64/SDL2_image.lib"
        "${SDL2_TTF_DIR}/lib/x64/SDL2_ttf.lib"
        "${SDL2_MIXER_DIR}/lib/x64/SDL2_mixer.lib"
    )

    # Copy SDL2 DLLs after build
    add_custom_command(TARGET ${GAME_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DIR}/lib/x64/SDL2.dll"
        "${SDL2_IMAGE_DIR}/lib/x64/SDL2_image.dll"
        "${SDL2_TTF_DIR}/lib/x64/SDL2_ttf.dll"
        "${SDL2_MIXER_DIR}/lib/x64/SDL2_mixer.dll"

        $<TARGET_FILE_DIR:${GAME_NAME}>
    )

else()
    message(STATUS "... - For Unix")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_ROOT_DIR}/cmake/cmake_find")

    # System SDL2 (Linux/macOS)
    find_package(SDL2       REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf   REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    message(STATUS "SDL2 include dirs:       ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2 libraries:          ${SDL2_LIBRARIES}")
    message(STATUS "SDL2_Image include dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")
    message(STATUS "SDL2_Image libraries:    ${SDL2_IMAGE_LIBRARIES}")
    message(STATUS "SDL2_TTF include dirs:   ${SDL2_TTF_INCLUDE_DIRS}")
    message(STATUS "SDL2_TTF libraries:      ${SDL2_TTF_LIBRARIES}")
    message(STATUS "SDL2_Mixer include dirs: ${SDL2_MIXER_INCLUDE_DIRS}")
    message(STATUS "SDL2_Mixer libraries:    ${SDL2_MIXER_LIBRARIES}")

    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
    )

    target_link_libraries(${GAME_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
    )
endif()


## Copy assets to build directory
add_custom_command(TARGET ${GAME_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying to: $<TARGET_FILE_DIR:${GAME_NAME}>/../assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_ROOT_DIR}/assets
    $<TARGET_FILE_DIR:${GAME_NAME}>/../assets
)
