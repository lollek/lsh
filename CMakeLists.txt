cmake_minimum_required (VERSION 2.6)
project (lsh)

set (PROJECT_VERSION 0.0.4)

add_definitions (
  -DPROGNAME="${PROJECT_NAME}"
  -DVERSION="${PROJECT_VERSION}")

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address \
                         -fno-omit-frame-pointer")

file(GLOB PROJECT_SOURCES src/*.c src/command/*.c)
add_executable (lsh ${PROJECT_SOURCES})

target_link_libraries (lsh prompt)

install (TARGETS lsh DESTINATION bin)

add_custom_target(lint cppcheck --enable=all ${PROJECT_SOURCE_DIR}/src)
