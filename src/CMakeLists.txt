cmake_minimum_required(VERSION 3.22)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 23)

# Because we are running inside the micromamba environment, CMake will
# automatically find these packages in the active Conda prefix.
find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
find_package(nanobind CONFIG REQUIRED)

if(WIN32)
    message(STATUS "Configuring for Windows (Conda Environment)")
    set(PLATFORM WINDOWS)

elseif(APPLE)
    message(STATUS "Configuring for macOS (Conda Environment)")
    set(PLATFORM DARWIN)

    set(ALL_COMPILER_ARGS
            -Werror=return-type
            -Wunused-variable
            -Wno-switch
            -Wno-narrowing
            -Wno-char-subscripts
            -O3
            -fno-strict-aliasing
    )

elseif(UNIX)
    message(STATUS "Configuring for GNU Linux (Conda Environment)")
    set(PLATFORM GNU_LINUX)

    set(ALL_COMPILER_ARGS -std=c++23)
    
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Unified list of imported library targets from Conda
# Using imported targets (Name::Name) automatically handles include paths and link flags!
set(CONDA_LIBRARIES
        ${OS_SPECIFIC_LIBRARIES}
)

set(ALL_COMPILER_DEFS
        ${OS_SPECIFIC_COMPILER_DEFS}
)

set(ALL_SRC
        Molecule.cpp
        ext.cpp
)

nanobind_add_module(_ext
        ${ALL_SRC}
)

set(EXT_PYTHON_MODULE_DIR "${CMAKE_SOURCE_DIR}/python_c_ext")

set_target_properties(_ext PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${EXT_PYTHON_MODULE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${EXT_PYTHON_MODULE_DIR}"
        # Ensure Windows RelWithDebInfo also goes to the right place
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXT_PYTHON_MODULE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXT_PYTHON_MODULE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${EXT_PYTHON_MODULE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXT_PYTHON_MODULE_DIR}"
)

install(TARGETS _ext DESTINATION python_c_ext)

# ----- Target compile section
target_compile_options(_ext PRIVATE ${ALL_COMPILER_ARGS})

set(ALL_COMPILER_DEFS
        ${OS_SPECIFIC_COMPILER_DEFS}
)
target_compile_definitions(_ext PUBLIC ${ALL_COMPILER_DEFS})
# --- end

# ----- Include section
set (ALL_INCLUDE_DIR
        src
        ${NUMPY_INCLUDE_DIR}
)
target_include_directories(_ext PUBLIC ${ALL_INCLUDE_DIR})
# --- end

# ----- Linker section
target_link_options(_ext PRIVATE ${OS_SPECIFIC_LINKER_OPTIONS})
target_link_libraries(_ext PRIVATE ${CONDA_LIBRARIES})
# --- end

nanobind_add_stub(
        add_stub_for_ext
        MODULE _ext
        OUTPUT "${EXT_PYTHON_MODULE_DIR}/_ext.pyi"
        PYTHON_PATH "${EXT_PYTHON_MODULE_DIR}"
        DEPENDS _ext
)

install(FILES "${EXT_PYTHON_MODULE_DIR}/_ext.pyi" DESTINATION python_c_ext)
