# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置C++编译器标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定C++编译器, 已经包含在目录里面了, 开箱即用
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

# [修复] 设置BUILD_SHARED_LIBS为OFF，构建静态库以适配嵌入式Linux部署
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static library" FORCE)
# [修复] 添加CSerialPort子项目，启用add_subdirectory
add_subdirectory(libs/CSerialPort)

add_executable(hello hello.cpp)

# [修复] 添加CSerialPort头文件搜索路径，使hello.cpp中的 #include "CSerialPort/SerialPort.h" 能够找到对应的头文件
target_include_directories(hello PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/CSerialPort/include)
# [修复] 链接libcserialport库（注意：CSerialPort子项目的CMake目标名是libcserialport，而不是CSerialPort）
# 同时libcserialport依赖pthread，链接时会自动传递
target_link_libraries(hello PRIVATE libcserialport)



##################################################################################
#一键拷贝到luckfox pico的/root目录下
set(BOARD_IP "172.32.0.93") # luckfox pico ip
set(BOARD_USER "root")
set(BOARD_PWD "luckfox")  # luckfox pico密码

##假设你的可执行文件目标叫 hello
##定义一个名为 "deploy" 的伪目标
add_custom_target(deploy
        # 核心动作：用 sshpass 和 scp 将编译好的二进制文件传到板子的 /root/ 目录
        # $<TARGET_FILE:hello> 是 CMake 的生成器表达式，会自动获取 hello 的绝对路径
        COMMAND sshpass -p ${BOARD_PWD} scp $<TARGET_FILE:hello> ${BOARD_USER}@${BOARD_IP}:/root/

        # 可选：赋予下位机执行权限
        COMMAND sshpass -p ${BOARD_PWD} ssh ${BOARD_USER}@${BOARD_IP} "chmod 777 /root/hello"

        # 依赖：在执行 deploy 之前，必须先保证 hello 被编译出来
        DEPENDS hello
        COMMENT ">>> 正在将程序烧录到下位机 ${BOARD_IP}:/root/ <<<"
)
