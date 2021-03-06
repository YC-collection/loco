############################################################################################
# Software License Agreement (BSD License)
#
# Copyright (c) 2014, Christian Gehring, Péter Fankhauser, C. Dario Bellicoso, Stelian Coros
# All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#   * Neither the name of Autonomous Systems Lab nor ETH Zurich
#     nor the names of its contributors may be used to endorse or
#     promote products derived from this software without specific
#     prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
#  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#
# Project configuration
cmake_minimum_required (VERSION 2.8)

project(locomotion_control)



find_package(Eigen REQUIRED)
find_package(Kindr REQUIRED)



################
### INCLUDES ###
################
set(LOCO_INCL ${LOCO_INCL} 
	${EIGEN_INCLUDE_DIRS}
	${Kindr_INCLUDE_DIRS}
PARENT_SCOPE)

###############
### SOURCES ###
###############
set(LOCO_SRCS ${LOCO_SRCS} 
	${CMAKE_CURRENT_SOURCE_DIR}/LegBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegStarlETH.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegGroup.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TorsoBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TorsoStarlETH.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TorsoStateBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TorsoStateMeasured.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TorsoStateDesired.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TorsoPropertiesBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TorsoPropertiesStarlETH.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/LegGroup.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegStarlETH.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegStateBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegStateLiftOff.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegStateTouchDown.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegPropertiesBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegPropertiesStarlETH.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegLink.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LegLinkGroup.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/ParameterSet.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/GeneralizedStateBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GeneralizedStateStarlETH.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/TerrainModelBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TerrainModelHorizontalPlane.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TerrainModelSimulation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/TerrainModelFreePlane.cpp
	
PARENT_SCOPE)

#################
### LIBRARIES ###
#################
set(LOCO_LIBS ${LOCO_LIBS} 

PARENT_SCOPE)


set(USE_UTIL_XMLPARAMETERS ON CACHE BOOL "xml")
