﻿file (GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)
target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCE_FILES} "../include/GameControll.h" "GameControll.cpp" "../include/Resources.h" "Resources.cpp" "../include/Board.h" "Board.cpp" "../include/Menu.h" "Menu.cpp" "Stick.cpp" "../include/Toolbar.h" "Toolbar.cpp")
