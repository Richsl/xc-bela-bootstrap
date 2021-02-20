
#[[
mkdir build # if it doesn't exist already
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain.cmake ../
cmake -DCMAKE_TOOLCHAIN_FILE=../../../../Toolchain.cmake ../../../../
cmake --build .

debug with 
gdbserver localhost:9999 ./<application>
]]#


set(USELIB USE_DEV_LIB)
message( "USELIB set to" ${USELIB} )
set(NAME LCD7789WS)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Config
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/GUI
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/LCD
  ${CMAKE_CURRENT_BINARY_DIR}
  
)

#IDIR= -I ../../drivers -I ../../u8g2src -I ../../port
message( "CMake_source_dir " ${CMAKE_SOURCE_DIR} )
message( "CMake_binary_dir " ${CMAKE_BINARY_DIR} )
message( "CMake_current_source_dir " ${CMAKE_CURRENT_SOURCE_DIR} )
message( "CMake_current_binary_dir " ${CMAKE_CURRENT_BINARY_DIR} )
message( "Name variable " ${NAME} )

#configure_file (${CMAKE_SOURCE_DIR}/samplv1/samplv1-code/src/cmake_config.h.in ${CMAKE_SOURCE_DIR}/samplv1/samplv1-code/src/config.h)
#BELA_AUDIO_THREAD_NAME?=bela-audio 
#BELA_IDE_HOME?=/root/Bela/IDE
#XENO_CONFIG=/usr/xenomai/bin/xeno-config
set(XENOMAI_SKIN posix)
#XENOMAI_VERSION=$(shell $(XENO_CONFIG) --version | grep -o "2\.6" || echo "3")

set (XENOMAI_VERSION 3)

if (${XENOMAI_VERSION} EQUAL 2.6)
set (XENOMAI_MAJOR 2)
endif()
if (${XENOMAI_VERSION} EQUAL 3)
set (XENOMAI_MAJOR 3)
endif()
#define XENOMAI_MAJOR 3
#[[
if (${XENOMAI_VERSION} EQUAL 2.6)
XENOMAI_STAT_PATH=/proc/xenomai/stat
LIBPD_LIBS=-lpd -lpthread_rt
endif
if(${XENOMAI_VERSION} EQUAL 3)
XENOMAI_STAT_PATH=/proc/xenomai/sched/stat
LIBPD_LIBS=-lpd -lpthread
endif
]]

if (${XENOMAI_VERSION} EQUAL 2.6)
  set(BELA_USE_DEFINE BELA_USE_POLL)
  add_compile_definitions(BELA_USE_POLL)
endif()
if (${XENOMAI_VERSION} EQUAL 3)
  set(BELA_USE_DEFINE BELA_USE_RTDM)
  add_compile_definitions(BELA_USE_RTDM)
endif()


#message( "___XENOMAI VERSION___" ${XENOMAI_VERSION} "\n")
#message( "___XENOMAI MAJOR___" ${XENOMAI_MAJOR} "\n")
#set (XENOMAI_TEST 3)
add_compile_definitions(XENOMAI_VERSION=${XENOMAI_VERSION} XENOMAI_MAJOR=${XENOMAI_MAJOR}  XENOMAI_SKIN=${XENOMAI_SKIN})
#add_definitions(-DXENOMAI_VERSION -DXENOMAI_MAJOR -DXENOMAI_SKIN)
add_executable(LCD7789WS
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/examples/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Config/DEV_Config.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Config/dev_hardware_SPI.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Config/sysfs_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts/font8.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts/font12.c
    #${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts/font12CN.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts/font16.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts/font20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts/font24.c
    #${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Fonts/font24CN.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/GUI/GUI_BMPfile.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/GUI/GUI_Paint.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/GUI/image.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/LCD/LCD_2inch.c


)

target_link_libraries(LCD7789WS PRIVATE
    #${CMAKE_SYSROOT}/root/Bela/lib/libbelafull.a
    #${CMAKE_SYSROOT}/usr/lib/liblilv-0.so
    #${CMAKE_SYSROOT}/usr/local/lib/libserd-0.so
    #${CMAKE_SYSROOT}/usr/local/lib/libsord-0.so
    #${CMAKE_SYSROOT}/usr/local/lib/libsratom-0.so
    #${CMAKE_SYSROOT}/usr/local/lib/libsuil-0.so
    #stdc++fs
)

## this PRE_BUILD command is to build the pru code 


#this is to uploade to the BELA
if(true)
add_custom_command(
    TARGET LCD7789WS
    POST_BUILD
    COMMAND scp ${CMAKE_BINARY_DIR}/bin/LCD7789WS root@$ENV{BBB_HOSTNAME}:~/Bela/uploads
)
endif()