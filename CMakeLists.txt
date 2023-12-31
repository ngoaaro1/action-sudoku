cmake_minimum_required(VERSION 3.26)
project(Project1)
set(APPLICATION_LIBRARY SudokuLib)

set(CMAKE_CXX_STANDARD 17)

# Turn off wxWidgets precompiled header system.
set(wxBUILD_PRECOMP OFF)

# WxWidgets libs.
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp
        pch.h
        SudokuApp.cpp
        SudokuApp.h
        ActionSudoku.rc
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)

add_subdirectory(Tests)
