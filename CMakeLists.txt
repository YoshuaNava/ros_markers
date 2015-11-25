SET(PROJECT_NAME ros_markers)
PROJECT(${PROJECT_NAME})
CMAKE_MINIMUM_REQUIRED (VERSION 2.8.3)
SET(CMAKE_BUILD_TYPE Release) # Release, RelWithDebInfo
SET(CMAKE_VERBOSE_MAKEFILE ON)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
FIND_PACKAGE(catkin REQUIRED COMPONENTS 
        roscpp
        tf 
        cv_bridge 
        image_transport 
        image_geometry 
        nodelet)

## System dependencies
FIND_PACKAGE(OpenCV REQUIRED)

FIND_PACKAGE(chilitags REQUIRED)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
FIND_PACKAGE(catkin REQUIRED COMPONENTS roscpp tf nodelet OpenCV chilitags image_transport image_geometry cv_bridge cmake_modules)

catkin_package(
	DEPENDS OpenCV chilitags
	CATKIN_DEPENDS roscpp tf nodelet 
	INCLUDE_DIRS
	LIBRARIES
)

##########################################
##           Options                   ###
##########################################

# OPTION (WITH_KNOWLEDGE "Add support for exporting to a KB-API knowledge base" OFF)

###########
## Build ##
###########

INCLUDE_DIRECTORIES(include ${catkin_INCLUDE_DIRS} ${CHILITAGS_INCLUDE_DIRS})

ADD_DEFINITIONS(-std=c++11)

SET(LIBS 
    ${catkin_LIBRARIES}
    ${CHILITAGS_LDFLAGS}
    ${OpenCV_LIBRARIES}
    )

# IF (WITH_KNOWLEDGE)

#     add_definitions(-DWITH_KNOWLEDGE)
#     pkg_check_modules(LIBKB REQUIRED liboro)
#     include_directories(${LIBKB_INCLUDE_DIRS})
#     set (LIBS ${LIBS} ${LIBKB_LDFLAGS})

# ENDIF()

ADD_LIBRARY(chilitags_detector src/chilitagsdetector.cpp)
TARGET_LINK_LIBRARIES(chilitags_detector ${LIBS})

ADD_EXECUTABLE(detect src/chilitagsdetector.cpp src/detect.cpp)
TARGET_LINK_LIBRARIES(detect chilitags_detector)

# add_library(markers_nodelet src/nodelet.cpp)
# add_dependencies(markers_nodelet ${catkin_EXPORTED_TARGETS})
# target_link_libraries(markers_nodelet chilitags_detector)


# #############
# ## Install ##
# #############

# install(TARGETS detect markers_nodelet
#    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

# install(FILES
#     launch/detect.launch
#     launch/detect_gscam.launch
#     launch/gscam_nodelet_pipeline.launch
#     DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

# install(FILES
#     config/markers_configuration_sample.yml
#     DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
# )

# install(FILES
#     nodelet_markers.xml
#     DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

