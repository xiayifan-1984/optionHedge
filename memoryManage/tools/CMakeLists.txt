CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(tools)

SET(BUILD_DIR "/home/xiayf/projects/optionHedge/build")

LINK_DIRECTORIES(${BUILD_DIR}/lib/memoryManage)
LINK_DIRECTORIES(${BUILD_DIR}/lib/boost)

ADD_EXECUTABLE(journal_toolEXE main.cpp)
TARGET_LINK_LIBRARIES(journal_toolEXE journal optionHedgelog)
