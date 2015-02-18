cmake_minimum_required (VERSION 2.6)
project (lsh)

set (PROJECT_VERSION 0.0.4)

add_definitions (
  -DPROGNAME="${PROJECT_NAME}"
  -DVERSION="${PROJECT_VERSION}")

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address \
                         -fno-omit-frame-pointer")

add_executable (lsh
  src/argparse.c src/command.c src/io.c src/main.c src/signal.c
  src/string.c src/command/cd.c src/command/alias.c src/command/help.c
  src/command/path.c)

target_link_libraries (lsh prompt)

install (TARGETS lsh DESTINATION bin)

add_custom_target(lint cppcheck --enable=all ${PROJECT_SOURCE_DIR}/src)
