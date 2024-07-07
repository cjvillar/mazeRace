cmake_minimum_required(VERSION 3.10)

# set project name required C++ standard
project(mazeRace VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# source files
add_executable(mazeRace
    src/startScreen.cpp
    src/mapRandomizer.cpp
    src/drawPlayer.cpp
    src/mazeMap.cpp
    src/savePlayerScore.cpp
    src/readPlayerScore.cpp
    src/endScreen.cpp
    src/main.cpp 
)

# include directories
target_include_directories(mazeRace PRIVATE dependencies/include)

# copy assets directory into build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# link SFML libraries based on the platform
if(WIN32)
    set(SFML_LIB_DIR "${CMAKE_SOURCE_DIR}/dependencies/lib")

    find_library(SFML_AUDIO sfml-audio PATHS ${SFML_LIB_DIR})
    find_library(SFML_GRAPHICS sfml-graphics PATHS ${SFML_LIB_DIR})
    find_library(SFML_NETWORK sfml-network PATHS ${SFML_LIB_DIR})
    find_library(SFML_SYSTEM sfml-system PATHS ${SFML_LIB_DIR})
    find_library(SFML_WINDOW sfml-window PATHS ${SFML_LIB_DIR})

    target_link_libraries(mazeRace PRIVATE
        ${SFML_AUDIO}
        ${SFML_GRAPHICS}
        ${SFML_NETWORK}
        ${SFML_SYSTEM}
        ${SFML_WINDOW}
    )

    # copy dynamic libraries to output directory
    add_custom_command(TARGET mazeRace POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SFML_LIB_DIR} $<TARGET_FILE_DIR:mazeRace>
    )
elseif(APPLE)
    find_package(SFML 2.5 COMPONENTS audio graphics network system window REQUIRED)
    target_link_libraries(mazeRace PRIVATE
        sfml-audio
        sfml-graphics
        sfml-network
        sfml-system
        sfml-window
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo"
    )
endif()