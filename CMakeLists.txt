cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

# PROJECTS BEGIN
project(model)
add_executable(model src/model.cpp)

project(l1exe1)
add_executable(l1exe1 src/L1/exe1.cpp)

project(l1exe2)
add_executable(l1exe2 src/L1/exe2.cpp)

project(l1exe3)
add_executable(l1exe3 src/L1/exe3.cpp)

project(l2exe1)
add_executable(l2exe1 src/L2/exe1.cpp)

project(l3exe1)
add_executable(l3exe1 src/L3/exe1.cpp)

project(l4exe1)
add_executable(l4exe1 src/L4/exe1.cpp)

project(l4exe2)
add_executable(l4exe2 src/L4/exe2.cpp)

project(l5exe1)
add_executable(l5exe1 src/L5/exe1.cpp)

project(l8exe1)
add_executable(l8exe1 src/L8/exe1.cpp)

project(l9exe1)
add_executable(l9exe1 src/L9/exe1.cpp)


project(l11exe1)
add_executable(l11exe1 src/L11/exe1.cpp)

# PROJECTS END


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${PNG_INCLUDE_DIR} )
#file(GLOB src/lib)


# TARGETS BEGIN
target_link_libraries(model  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l1exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l1exe2  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l1exe3  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l2exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l3exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l4exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l4exe2  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l5exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l8exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l9exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries(l11exe1  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${PNG_LIBRARIES})
# TARGETS END
