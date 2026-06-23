# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置C++编译器标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
#add_executable(hello hello.cpp)# 设置CMake最低版本要求
#cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
# project(Hello VERSION 1.0)

# 指定C++编译器
set(CMAKE_C_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/gcc-arm-rockchip/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/gcc-arm-rockchip/bin/arm-rockchip830-linux-uclibcgnueabihf-g++")


# 设置项目名称和版本
project(Hello VERSION 1.0)



# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译器和链接器标志（可选）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

#set(CSERIALPORT_WITHOUT_QT ON CACHE INTERNAL "Disable Qt support for CSerialPort")
#add_subdirectory("../libs/CSerialPort" "CSerialPort_build")
# 添加可执行文件
add_executable(hello hello.cpp
        hello.cpp)

#target_link_libraries(CSerialPort)


