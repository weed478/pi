cmake_minimum_required(VERSION 3.12)

project(pi C)
set(CMAKE_C_STANDARD 99)

include(CTest)

find_program(bash bash)
find_program(diff diff)

if (NOT bash)
    message("Will not add tests, bash not found")
elseif (NOT diff)
    message("Will not add tests, diff not found")
endif ()

find_program(valgrind valgrind)
find_program(sh sh)

if (NOT valgrind)
    message("Will not add valgrind tests, valgrind not found")
elseif (NOT sh)
    message("Will not add valgrind tests, sh not found")
endif ()

file(GLOB labs lab*)

foreach (lab IN LISTS labs)
    string(REGEX MATCH "[^/]+$"
            lab_name "${lab}")

    message("Found ${lab_name}")

    file(GLOB srcs "${lab}/*.c")

    foreach (src IN LISTS srcs)
        string(REGEX MATCH "[^/]+$"
                src_name "${src}")

        string(REGEX REPLACE "\\.c$"
                "" src_name
                "${src_name}")

        set(target "${lab_name}_${src_name}")

        add_executable("${target}" "${src}")
        set(exec "${CMAKE_BINARY_DIR}/${target}")

        set(n_tests 0)

        file(GLOB test_ins "${lab}/${src_name}.*.in")

        foreach (test_in IN LISTS test_ins)
            string(REGEX REPLACE ".in$"
                    "" test_n
                    "${test_in}")

            string(REGEX MATCH "[^\\.]+$"
                    test_n "${test_n}")

            set(test_out "${lab}/${src_name}.${test_n}.out")
            set(test_name "${lab_name}_${src_name}_test_${test_n}")

            if (bash AND diff)
                add_test(NAME "${test_name}" COMMAND "${PROJECT_SOURCE_DIR}/run_tests.sh" "${exec}" "${test_in}" "${test_out}")
            endif ()

            if (valgrind AND sh)
                add_test(NAME "${test_name}_valgrind" COMMAND sh -c "${valgrind} ${exec} < ${test_in}")
            endif ()

            math(EXPR n_tests "${n_tests} + 1")
        endforeach ()

        if (${n_tests} GREATER 0)
            if (${n_tests} EQUAL 1)
                message(" - ${src_name} (${n_tests} test)")
            else ()
                message(" - ${src_name} (${n_tests} tests)")
            endif ()
        else ()
            message(" - ${src_name}")
        endif ()
    endforeach ()
endforeach ()
