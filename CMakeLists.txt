cmake_minimum_required(VERSION 3.0.2)
project(jialiang_han_fulltime)


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  message_generation
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/astar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/node_3d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/planner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/path.cpp
    )
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/astar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/node_3d.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/planner.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/path.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/key_hash.h
    )
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

## Generate services in the 'srv' folder
add_service_files(
   FILES
   UpdateGoal.srv
   GetPlan.srv
 )


## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   geometry_msgs
   nav_msgs
 )


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES Jialiang_Han_Fulltime
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp message_runtime
  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(agent src/agent.cpp ${HEADERS} ${SOURCES})
target_link_libraries(agent ${catkin_LIBRARIES})
add_dependencies(agent ${${PORJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(get_plan_server src/get_plan_server.cpp ${HEADERS} ${SOURCES})
target_link_libraries(get_plan_server ${catkin_LIBRARIES})
add_dependencies(get_plan_server jialiang_han_fulltime_gencpp)

add_executable(grid_map src/grid_map.cpp )
add_dependencies(grid_map ${${PORJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(grid_map ${catkin_LIBRARIES})

add_executable(update_goal_server src/update_goal_server.cpp ${HEADERS} ${SOURCES})
target_link_libraries(update_goal_server ${catkin_LIBRARIES})
add_dependencies(update_goal_server jialiang_han_fulltime_gencpp)

add_executable(update_goal_client src/update_goal_client.cpp)
target_link_libraries(update_goal_client ${catkin_LIBRARIES})
add_dependencies(update_goal_client jialiang_han_fulltime_gencpp)

add_executable(test_a_star src/test_a_star.cpp ${HEADERS} ${SOURCES})
add_dependencies(test_a_star ${${PORJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_a_star ${catkin_LIBRARIES})

SET(CMAKE_BUILD_TYPE Debug)
