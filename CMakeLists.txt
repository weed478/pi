cmake_minimum_required(VERSION 3.12)

project(pi C)
set(CMAKE_C_STANDARD 99)

include(CTest)

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

        message(" - ${src_name}")

        file(GLOB test_ins "${lab}/${src_name}.*.in")

        foreach (test_in IN LISTS test_ins)
            string(REGEX REPLACE ".in$"
                    "" test_n
                    "${test_in}")

            string(REGEX MATCH "[^\\.]+$"
                    test_n "${test_n}")

            set(test_out "${lab}/${src_name}.${test_n}.out")
            set(test_name "${lab_name}_${src_name}_test_${test_n}")

            add_test(NAME "${test_name}" COMMAND "${PROJECT_SOURCE_DIR}/run_tests.sh" "${exec}" "${test_in}" "${test_out}")

            message("   - test ${test_n}")
        endforeach ()
    endforeach ()
endforeach ()
