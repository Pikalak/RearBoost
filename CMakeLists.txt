cmake_minimum_required(VERSION 3.20)

project(RearBoost VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    vst3sdk
    GIT_REPOSITORY https://github.com/steinbergmedia/vst3sdk.git
    GIT_TAG v3.7.14.0
)

FetchContent_MakeAvailable(vst3sdk)

smtg_enable_vst3_sdk()

smtg_add_vst3plugin(RearBoost
    source/RearBoost.cpp
    source/RearBoostController.cpp
)

target_include_directories(RearBoost PRIVATE
    source
)

smtg_target_configure_version_file(RearBoost)
