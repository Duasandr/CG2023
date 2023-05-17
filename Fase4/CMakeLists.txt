cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(engine)

# C++ 11
set(CMAKE_CXX_STANDARD 11)

# Set OpenGL preference to GLVND
set(OpenGL_GL_PREFERENCE GLVND)

# Set output properties to use folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE ENGINE_SOURCES
        src/engine/*.cpp
        src/engine/world/*.cpp
        src/engine/transform/*.cpp
        src/engine/utils/*.cpp
        src/common/math/*.cpp
        src/common/utils/*.cpp
        )
file(GLOB_RECURSE ENGINE_INCLUDE
        include/engine/*.h
        include/common/math/*.h
        include/common/utils/*.h
        )

file(GLOB_RECURSE GENERATOR_SOURCES
        src/generator/*.cpp
        src/generator/primitives/*.cpp
        src/common/math/*.cpp
        src/common/utils/*.cpp
        )
file(GLOB_RECURSE GENERATOR_INCLUDE
        include/generator/*.h
        include/generator/primitives/*.h
        include/common/math/*.h
        include/common/utils/*.h
        )

# Add executable targets
add_executable(engine ${ENGINE_SOURCES} ${ENGINE_INCLUDE})
add_executable(generator ${GENERATOR_SOURCES} ${GENERATOR_INCLUDE})

# Add include directories to target
target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/world
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/transform
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common/math
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common/utils
        /opt/homebrew/Cellar/devil/1.8.0_6/include
        )

target_include_directories(generator PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/generator
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common/math
        ${CMAKE_CURRENT_SOURCE_DIR}/include/common/utils
        /opt/homebrew/Cellar/devil/1.8.0_6/include
        )


find_package(DevIL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS} ${DevIL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS} ${DevIL_LIBRARY_DIRS})
# Add definitions to target
add_definitions(${OpenGL_DEFINITIONS} ${DevIL_DEFINITIONS})

# Check if OpenGL is found
if (NOT OPENGL_FOUND)
    # If not found, print error message
    message(ERROR " OPENGL not found!")
endif (NOT OPENGL_FOUND)

if (NOT DEVIL_FOUND)
    # If not found, print error message
    message(ERROR " DEVIL not found!")
endif (NOT DEVIL_FOUND)

# If we are on Windows
if (WIN32)
    # Set Toolkits folder
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

    # If GLUT is not found , print error message
    if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(ERROR ": GLUT not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")


    include_directories(${TOOLKITS_FOLDER}/glut)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
            ${TOOLKITS_FOLDER}/glut/glut32.lib)

    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")

    set_property(DIRECTORY .. PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else (WIN32) #Linux and Mac

    set( CMAKE_CXX_FLAGS† "${CMAKE_CXX_FLAGS} Wno-deprecated")
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    if (NOT APPLE)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif(NOT APPLE)

    find_package(DevIL REQUIRED)
    link_libraries(${IL_LIBRARIES} )
    include_directories(${IL_INCLUDE_DIR})

    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
    if(NOT GLUT_FOUND)
        message(ERROR ": GLUT not found!")
    endif(NOT GLUT_FOUND)

endif (WIN32)



