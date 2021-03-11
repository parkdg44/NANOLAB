# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "test_mapping: 2 messages, 0 services")

set(MSG_I_FLAGS "-Itest_mapping:/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Inav_msgs:/opt/ros/kinetic/share/nav_msgs/cmake/../msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(test_mapping_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg" NAME_WE)
add_custom_target(_test_mapping_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_mapping" "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg" ""
)

get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg" NAME_WE)
add_custom_target(_test_mapping_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test_mapping" "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_mapping
)
_generate_msg_cpp(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_mapping
)

### Generating Services

### Generating Module File
_generate_module_cpp(test_mapping
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_mapping
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(test_mapping_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(test_mapping_generate_messages test_mapping_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_cpp _test_mapping_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_cpp _test_mapping_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_mapping_gencpp)
add_dependencies(test_mapping_gencpp test_mapping_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_mapping_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_mapping
)
_generate_msg_eus(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_mapping
)

### Generating Services

### Generating Module File
_generate_module_eus(test_mapping
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_mapping
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(test_mapping_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(test_mapping_generate_messages test_mapping_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_eus _test_mapping_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_eus _test_mapping_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_mapping_geneus)
add_dependencies(test_mapping_geneus test_mapping_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_mapping_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_mapping
)
_generate_msg_lisp(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_mapping
)

### Generating Services

### Generating Module File
_generate_module_lisp(test_mapping
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_mapping
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(test_mapping_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(test_mapping_generate_messages test_mapping_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_lisp _test_mapping_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_lisp _test_mapping_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_mapping_genlisp)
add_dependencies(test_mapping_genlisp test_mapping_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_mapping_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_mapping
)
_generate_msg_nodejs(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_mapping
)

### Generating Services

### Generating Module File
_generate_module_nodejs(test_mapping
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_mapping
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(test_mapping_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(test_mapping_generate_messages test_mapping_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_nodejs _test_mapping_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_nodejs _test_mapping_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_mapping_gennodejs)
add_dependencies(test_mapping_gennodejs test_mapping_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_mapping_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_mapping
)
_generate_msg_py(test_mapping
  "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_mapping
)

### Generating Services

### Generating Module File
_generate_module_py(test_mapping
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_mapping
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(test_mapping_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(test_mapping_generate_messages test_mapping_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/PSD.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_py _test_mapping_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/park/Desktop/Link to catkin_ws/src/test_mapping/msg/Cmd_val.msg" NAME_WE)
add_dependencies(test_mapping_generate_messages_py _test_mapping_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test_mapping_genpy)
add_dependencies(test_mapping_genpy test_mapping_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test_mapping_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_mapping)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test_mapping
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(test_mapping_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(test_mapping_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(test_mapping_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_mapping)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test_mapping
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(test_mapping_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(test_mapping_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET nav_msgs_generate_messages_eus)
  add_dependencies(test_mapping_generate_messages_eus nav_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_mapping)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test_mapping
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(test_mapping_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(test_mapping_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(test_mapping_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_mapping)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test_mapping
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(test_mapping_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(test_mapping_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET nav_msgs_generate_messages_nodejs)
  add_dependencies(test_mapping_generate_messages_nodejs nav_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_mapping)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_mapping\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test_mapping
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(test_mapping_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(test_mapping_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(test_mapping_generate_messages_py nav_msgs_generate_messages_py)
endif()
