cmake_minimum_required(VERSION 3.1.0)

project(iDownloadServer
  VERSION
    1.0
  DESCRIPTION
    "Download files via TCP/IP (server - client method)"
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_subdirectory(ModifyXml)
add_subdirectory(XmlReadWrite)


