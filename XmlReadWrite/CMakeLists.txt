cmake_minimum_required(VERSION 3.1.0)

project(XML_ReadWrite
  VERSION
    1.0
  DESCRIPTION
    "XML Read Write"
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Qt5Core REQUIRED)

set(SOURCES test.cpp test.h XML_ReadWrite.cpp XML_ReadWrite.h
		main.cpp)

add_executable(XML_ReadWrite ${SOURCES})

add_definitions(-DQT_NO_VERSION_TAGGING)

#target_link_libraries(XML_ReadWrite Qt5::Widgets)

qt5_use_modules(XML_ReadWrite Core Xml PrintSupport)

include_directories(. .)


