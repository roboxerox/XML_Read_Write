cmake_minimum_required(VERSION 3.1.0)

project(ModifyXml
  VERSION
    1.0
  DESCRIPTION
    "Modify existing Xml"
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

set(SOURCES main.cpp)

add_executable(ModifyXml ${SOURCES})

add_definitions(-DQT_NO_VERSION_TAGGING)

#target_link_libraries(XML_ReadWrite Qt5::Widgets)

qt5_use_modules(ModifyXml Core Xml)

include_directories(. .)


