CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(PageEngine)

SET(BUILD_DIR "/home/xiayf/projects/optionHedge/build")

LINK_DIRECTORIES(${BUILD_DIR}/lib/memoryManage)
LINK_DIRECTORIES(${BUILD_DIR}/lib/boost)

ADD_EXECUTABLE(PageEngine main.cpp)
TARGET_LINK_LIBRARIES(PageEngine journal optionHedgelog paged)