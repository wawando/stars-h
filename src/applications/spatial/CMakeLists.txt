# @copyright (c) 2017 King Abdullah University of Science and
#                      Technology (KAUST). All rights reserved.
#
# STARS-H is a software package, provided by King Abdullah
#             University of Science and Technology (KAUST)
#
# @file src/applications/spatial/CMakeLists.txt
# @version 1.3.0
# @author Aleksandr Mikhalev
# @date 2017-11-07

EXECUTE_PROCESS(COMMAND "python3" "--version"
			OUTPUT_VARIABLE py_out
			ERROR_VARIABLE py_err)
message("output: ${py_out}")
message("error: ${py_err}")

EXECUTE_PROCESS(COMMAND "python3"
    "${CMAKE_SOURCE_DIR}/misc_scripts/code_generation/applications/particles/kernel_nd.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/kernel_exp.c" "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_VARIABLE generated_files)
message("generated_files: ${generated_files}")

EXECUTE_PROCESS(COMMAND "python3"
    "${CMAKE_SOURCE_DIR}/misc_scripts/code_generation/applications/particles/kernel_nd.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/kernel_sqrexp.c" "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_VARIABLE generated_files2)
list(APPEND generated_files ${generated_files2})
message("generated_files2: ${generated_files2}")

if(GSL_FOUND OR DOCS STREQUAL "FULL")
    EXECUTE_PROCESS(COMMAND "python3"
        "${CMAKE_SOURCE_DIR}/misc_scripts/code_generation/applications/particles/kernel_nd.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/kernel_matern.c"
        "${CMAKE_CURRENT_BINARY_DIR}" OUTPUT_VARIABLE generated_files2)
    list(APPEND generated_files ${generated_files2})
    message("entered if - generated_files2: ${generated_files2}")

    EXECUTE_PROCESS(COMMAND "python3"
        "${CMAKE_SOURCE_DIR}/misc_scripts/code_generation/applications/particles/kernel_nd.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/kernel_matern2.c"
        "${CMAKE_CURRENT_BINARY_DIR}" OUTPUT_VARIABLE generated_files2)
    list(APPEND generated_files ${generated_files2})
    message("entered if2 - generated_files2: ${generated_files2}")
endif()
message("Cmake spatial generate files")
message("${generated_files}")
set(STARSH_SRC
    ${generated_files}
    ${STARSH_SRC} PARENT_SCOPE)
