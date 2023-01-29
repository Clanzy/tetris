cmake_minimum_required(VERSION 3.0.0)
project(tetris VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCE_FILES main.c ui.c ui.h graphics.c graphics.h gameplay.c 
gameplay.h bwindow.c bwindow.h figure.c figure.h constants.h constants.c settings.h settings.c)

add_executable(tetris ${SOURCE_FILES})
target_link_libraries(tetris panel ncurses)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
