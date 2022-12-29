add_executable(RGSSAD-dec)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "*.cpp"
)

target_sources(RGSSAD-dec PRIVATE ${SRC_FILES})

if(${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
    target_compile_options(RGSSAD-dec PUBLIC "/std:c++latest")
else()
    target_compile_options(RGSSAD-dec PUBLIC "-std=c++17")
endif()

target_include_directories(RGSSAD-dec PUBLIC include)

target_link_libraries(RGSSAD-dec
  PRIVATE
    fmt::fmt
)