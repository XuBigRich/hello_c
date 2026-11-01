#声明cmake最低版本
cmake_minimum_required(VERSION 3.17)
#设置项目名称
project(hello C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#设置可执行文件输出路径，为当前项目源文件的/bin目录下，PROJECT_SOURCE_DIR的意思是当前项目的源文件目录， 这里需要注意 这行必须写在 add_executable 之前才生效
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置头文件所在的文件夹为 include 文件夹，指定了头文件所在文件夹后，在源文件中就可以直接引用头文件了，无需指定头文件的路径。例如：#include "include/format.h" 可以简化为#include "format.h"
include_directories(include)
# 用来指定用哪个版本的 C 语言标准来编译你的代码。 17：值，代表 C17 标准（17年发布的 C 语言标准）
set(CMAKE_C_STANDARD 17)
# ----------------------------------------------------------------------------------------
#1. 使用单独罗列的方式创建可执行文件hello
#      声明生成的目标文件 和 目标文件所以来的代码文件。 这里生成hello 需要依赖 main.c和 format.c （ 手动罗列文件）
add_executable(hello main.c src/format.c)
# ----------------------------------------------------------------------------------------
# 2. 使用递归扫描的方式创建可执行文件hello2
#将当前目录下所有源文件放到SRC_LIST变量中  。
#.代表当前目录，他会扫描当前目录下的所有cpp文件， SRC_LIST 可以自己定义叫任何名字 他将所有cpp文件放到 SRC_LIST 这个变量中
aux_source_directory(. SRC_LIST)
#再扫描 src 子目录，否则 format.c 进不来，链接时会报 undefined reference to `result1'
aux_source_directory(src SRC_LIST_SRC)
#创建可执行文件hello2 ， 需要将所有源文件都放到可执行文件中。 注意. 只查询本目录下的可执行文件，不递归查询子目录下的可执行文件
add_executable(hello2 ${SRC_LIST} ${SRC_LIST_SRC})
# ----------------------------------------------------------------------------------------
# 3.通过共享库的方式创建可执行文件hello3
# 设置共享库的源文件
set(LIB_SRC src/format.c)
# 创建共享库 libformat.so   1.参数：库名称 2.参数：库类型 3.参数：库源文件
add_library(libformat SHARED ${LIB_SRC})
# 创建可执行文件 hello3，需要依赖 libformat.so
add_executable(hello3 main.c)
# 链接 libformat.so
target_link_libraries(hello3 libformat)
# 设置动态库的输出路径
set(LIB_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置hello3 的输出路径为当前项目的 bin 目录， 他和 上面  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 做的其实是一个事情， 不过 上面是设置全局，下面只针对 hello3 这个可执行文件。
set_target_properties(hello3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

