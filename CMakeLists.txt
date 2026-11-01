#声明cmake最低版本
cmake_minimum_required(VERSION 3.17)
#设置项目名称
project(hello C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#设置可执行文件输出路径，为当前项目源文件的/bin目录下
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置头文件所在的文件夹为 include 文件夹
include_directories(include)
# 用来指定用哪个版本的 C 语言标准来编译你的代码。 17：值，代表 C17 标准（17年发布的 C 语言标准）
set(CMAKE_C_STANDARD 17)
#声明生成的目标文件 和 目标文件所以来的代码文件。 这里生成hello 需要依赖 main.c和 format.c （ 手动罗列文件）
add_executable(hello main.c src/format.c)
#将当前目录下所有源文件放到SRC_LIST变量中  。
#.代表当前目录，他会扫描当前目录下的所有cpp文件， SRC_LIST 可以自己定义叫任何名字 他将所有cpp文件放到 SRC_LIST 这个变量中
aux_source_directory(. SRC_LIST)
#再扫描 src 子目录，否则 format.c 进不来，链接时会报 undefined reference to `result1'
aux_source_directory(src SRC_LIST_SRC)
#创建可执行文件hello2 ， 需要将所有源文件都放到可执行文件中。 注意. 只查询本目录下的可执行文件，不递归查询子目录下的可执行文件
add_executable(hello2 ${SRC_LIST} ${SRC_LIST_SRC})

