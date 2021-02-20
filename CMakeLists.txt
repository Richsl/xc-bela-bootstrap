
cmake_minimum_required(VERSION 3.6)
#project(my-bela-project VERSION 0.1.0)
message("top level cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fPIC -ftree-vectorize -ffast-math -lstdc++fs")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -march=armv7-a -mtune=cortex-a8 -mfloat-abi=hard -mfpu=neon -ftree-vectorize")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fPIC -ftree-vectorize -ffast-math -lstdc++fs")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fPIC -ftree-vectorize -ffast-math")
#changed these to match Jalv waf, originals are commented

include_directories(
    
    ${CMAKE_SYSROOT}/root/Bela/include
    ${CMAKE_SYSROOT}/usr/include
    ${CMAKE_SYSROOT}/usr/include/c++/6.3.0
    ${CMAKE_SYSROOT}/usr/include/arm-linux-gnueabihf
    ${CMAKE_SYSROOT}/usr/include/arm-linux-gnueabihf/c++/6.3.0
    ${CMAKE_SYSROOT}/root/Bela
    #${CMAKE_SYSROOT}/root/Bela/include
    #${CMAKE_SYSROOT}/root/Bela/include
    #${CMAKE_SYSROOT}/usr/include
    ${CMAKE_SYSROOT}/usr/xenomai/include
    ${CMAKE_SYSROOT}/usr/xenomai/include/rtdm
    ${CMAKE_SYSROOT}/usr/xenomai/include/trank
    ${CMAKE_SYSROOT}/usr/xenomai/include/cobalt
    #./Bela
    #./Bela/include
    #set(RICH_TEST ./Bela/include)
    #message("including $RICH_TEST")

    
)

link_directories(
    ${CMAKE_SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/6.3.0
    ${CMAKE_SYSROOT}/usr/local/lib
    ${CMAKE_SYSROOT}/usr/xenomai/lib
    ${CMAKE_SYSROOT}/root/Bela/lib
    #${CMAKE_SYSROOT}/root/Bela/include
)

link_libraries(
    cobalt modechk pthread rt
    prussdrv asound seasocks NE10 mathneon dl sndfile
    pd atomic
)

set(BELA_LINK_FLAGS "${BELA_LINK_FLAGS} \
    -B${CMAKE_SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/6.3.0 \
    -Wl,-rpath-link,${CMAKE_SYSROOT}/lib/arm-linux-gnueabihf,-lstdc++fs"
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BELA_LINK_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${BELA_LINK_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${BELA_LINK_FLAGS}")

add_subdirectory(src/jalv/jalv)
#add_subdirectory(src/sinetone/sinetone)

#add_subdirectory(src/LCD7789WS)