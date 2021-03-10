
# 2021y-02m-12d. WorkSpace project.
# 2021y-02m-20d. WorkSpace project.
# 2021y-03m-05d. WorkSpace project.
################################################################################
################################################################################

set(gDEBUG "$ENV{eDEBUG}")
cmake_minimum_required(VERSION 3.1)

include("${CMAKE_CURRENT_LIST_DIR}/setup.cmake")
cmake_scenario("minimalist")

project(${gNAME_PROJECT})

################################################################################
################################################################################

if(MINGW)
    make_target(
        DEPENDENCIES 
            "crypt32"  # secure
            "urlmon"   # url
    )
else()
    make_target()
endif()

make_target(PATH_TO_SOURCES "test/test-modern")
make_target(PATH_TO_SOURCES "test/test-000-platform")
make_target(PATH_TO_SOURCES "test/test-100-macro")
make_target(PATH_TO_SOURCES "test/test-200-types")
make_target(PATH_TO_SOURCES "test/test-600-others")

################################################################################
################################################################################

