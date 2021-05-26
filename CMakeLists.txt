cmake_minimum_required(VERSION 3.12)

project(pi C)
set(CMAKE_C_STANDARD 99)

file(GLOB labs lab*)

foreach(lab IN LISTS labs)
    file(GLOB srcs ${lab}/*.c)

    foreach(src IN LISTS srcs)
        string(REGEX MATCH "/[^/]+$"
                target ${src})

        string(REGEX REPLACE "^/"
                "" target
                ${target})

        string(REGEX REPLACE "\\.c$"
                "" target
                ${target})

        add_executable(${target} ${src})
    endforeach()
endforeach()
