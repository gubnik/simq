file(GLOB SOURCES *.cpp)

add_library(SimQLib SHARED ${SOURCES})

target_include_directories(SimQLib PRIVATE ../include/)
