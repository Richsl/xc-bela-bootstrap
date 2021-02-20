
# targets
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR armv7a)
set(triple arm-linux-gnueabihf)

# compiler settings
set(CMAKE_C_COMPILER /usr/bin/clang-10 CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER /usr/bin/clang++-10 CACHE INTERNAL "")
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN /usr/lib/llvm-10)
set(CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN /usr/lib/llvm-10)

# misc settings
#set(CMAKE_SYSROOT /sysroot)
set(CMAKE_SYSROOT /workspace/xc-bela-bootstrap/sysroot)
#set(XC_SYSROOT /sysroot)
set(XC_SYSROOT /workspace/xc-bela-bootstrap/sysroot)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
message("sysroot set to $XC_SYSROOT")

# compiler args
set(CMAKE_C_FLAGS "-DXENOMAI_SKIN_posix -march=armv7-a -mtune=cortex-a8 -mfloat-abi=hard -mfpu=neon" CACHE STRING "")
set(CMAKE_CXX_FLAGS "-DXENOMAI_SKIN_posix -march=armv7-a -mtune=cortex-a8 -mfloat-abi=hard -mfpu=neon" CACHE STRING "")