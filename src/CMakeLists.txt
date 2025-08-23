# 실행 파일 생성
add_executable(${PROJECT_NAME} main.cc)

# 컴파일러별 특별한 설정
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
