cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(engine)

# C++ 11
set (CMAKE_CXX_STANDARD 11)

# Set OpenGL preference to GLVND
set(OpenGL_GL_PREFERENCE GLVND)

# Set output properties to use folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add executable target with source files listed
add_executable(engine src/engine/engine.cpp src/engine/engine.cpp include/engine/engine.h include/generator/generator.h src/common/cg_math/Vec3f.cpp include/common/Vec3f.h src/engine/tinyxml2.cpp src/engine/world/Camera.cpp include/engine/world/Camera.h src/engine/world/model/Model.cpp include/engine/world/model/Model.h src/engine/world/model/VertexBuffer.cpp include/engine/world/model/VertexBuffer.h src/engine/world/model/VertexArray.cpp include/engine/world/model/VertexArray.h src/engine/world/World.cpp include/engine/world/World.h src/engine/world/Window.cpp include/engine/world/Window.h src/engine/world/Group.cpp include/engine/world/Group.h src/common/cg_utils/Parser.cpp include/common/Parser.h src/engine/transform/Transform.cpp include/engine/transform/Transform.h src/engine/transform/Translate.cpp include/engine/transform/Translate.h src/engine/transform/Rotate.cpp include/engine/transform/Rotate.h include/engine/transform/Scale.h src/engine/transform/Scale.cpp)

# Add include directories to target (PUBLIC means that the include directories will be added to the target and to any target that links to this target)
target_include_directories(engine PUBLIC ./include/engine ./include/common)

add_executable(generator src/generator/generator.cpp src/common/cg_math/Vec3f.cpp include/common/Vec3f.h src/generator/Plane.cpp include/generator/Plane.h src/generator/Utils.cpp include/generator/Utils.h include/generator/Primitives.h src/generator/Box.cpp include/generator/Box.h src/generator/Sphere.cpp include/generator/Sphere.h src/generator/Cone.cpp include/generator/Cone.h)
target_include_directories(generator PUBLIC ./include/generator ./include/common)

# Find OpenGL package and add include directories and link directories to target
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
# Add definitions to target
add_definitions(${OpenGL_DEFINITIONS})

# Check if OpenGL is found
if(NOT OPENGL_FOUND)
	# If not found, print error message
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

# If we are on Windows
if  (WIN32)
	# Set Toolkits folder
	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	# If GLUT is not found , print error message
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
	

	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} 
										  ${TOOLKITS_FOLDER}/glut/glut32.lib)
	
	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )	
	
	set_property(DIRECTORY .. PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	
else (WIN32) #Linux and Mac

	# Set C++ flags to ignore deprecated warnings
	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)
	
endif(WIN32)
