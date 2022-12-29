add_executable(RGSSAD_dec)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "*.cpp"
)

target_sources(RGSSAD_dec PRIVATE ${SRC_FILES})

if(${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
    target_compile_options(RGSSAD_dec PUBLIC "/std:c++latest")
else()
    target_compile_options(RGSSAD_dec PUBLIC "-std=c++14")
endif()

target_include_directories(RGSSAD_dec PUBLIC include)