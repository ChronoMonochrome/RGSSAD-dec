cmake_minimum_required(VERSION 3.16)

project(RGSSAD-dec)

include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(RGSSAD-dec)
