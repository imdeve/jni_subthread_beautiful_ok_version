# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

aux_source_directory(./callbacks CALL_BACKS)
aux_source_directory(./task TASK_SRC)
aux_source_directory(./sdkout SDKOUT_SRC)
aux_source_directory(./testexample2  TEST_EXAMPLE_SRC)

aux_source_directory(./main/cpp  MAIN_CPP_SRC)

include_directories(./callbacks)
include_directories(./sdkout)
include_directories(./task)



add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        ${CALL_BACKS}
        ${TASK_SRC}
        ${SDKOUT_SRC}
        ${TEST_EXAMPLE_SRC}
        ${MAIN_CPP_SRC}
        main/cpp/WlListener.cpp
        main/cpp/native-lib.cpp)

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)


target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})