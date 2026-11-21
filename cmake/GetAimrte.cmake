include(FetchContent)

message(STATUS "get aimrte ...")

FetchContent_Declare(
  aimrte #
  GIT_REPOSITORY https://${CODE_IQIYUAN_COM_HTTP_TOKEN}code.iqiyuan-robot.com/software/qiyuan/modules/aimrte.git #
  GIT_TAG feat/t1)

set(AIMRTE_BUILD_SOME_OF_ROBOT_PROTOCOLS "mc;hal")

set(AIMRTE_IMPORT_PROTOCOL_ONLY ON)
set(AIMRTE_BUILD_ALL_OF_OMP_PROTOCOLS OFF)

# 交叉编译时使用本地 x86 protoc 生成代码，避免编译出 ARM64 的 protoc 无法执行
set(Protobuf_PROTOC_EXECUTABLE "/usr/local/bin/protoc" CACHE STRING "" FORCE)

FetchContent_GetProperties(aimrte)

if(NOT aimrte_POPULATED)
  FetchContent_MakeAvailable(aimrte)
  aimrte_project_init()
endif()
