cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

# PROJECTS BEGIN
project(model)
add_executable(model src/model.cpp)

project(exe1)
add_executable(exe1 src/L1/exe1.cpp)

project(exe2)
add_executable(exe2 src/L1/exe2.cpp)
# PROJECTS END


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


# TARGETS BEGIN
target_link_libraries(model  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(exe2  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
# TARGETS








