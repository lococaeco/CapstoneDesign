# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "Total_msgs: 2 messages, 0 services")

set(MSG_I_FLAGS "-ITotal_msgs:/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(Total_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg" NAME_WE)
add_custom_target(_Total_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Total_msgs" "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg" ""
)

get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg" NAME_WE)
add_custom_target(_Total_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Total_msgs" "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Total_msgs
)
_generate_msg_cpp(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Total_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(Total_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Total_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(Total_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(Total_msgs_generate_messages Total_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_cpp _Total_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_cpp _Total_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Total_msgs_gencpp)
add_dependencies(Total_msgs_gencpp Total_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Total_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Total_msgs
)
_generate_msg_eus(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Total_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(Total_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Total_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(Total_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(Total_msgs_generate_messages Total_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_eus _Total_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_eus _Total_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Total_msgs_geneus)
add_dependencies(Total_msgs_geneus Total_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Total_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Total_msgs
)
_generate_msg_lisp(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Total_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(Total_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Total_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(Total_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(Total_msgs_generate_messages Total_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_lisp _Total_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_lisp _Total_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Total_msgs_genlisp)
add_dependencies(Total_msgs_genlisp Total_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Total_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Total_msgs
)
_generate_msg_nodejs(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Total_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(Total_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Total_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(Total_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(Total_msgs_generate_messages Total_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_nodejs _Total_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_nodejs _Total_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Total_msgs_gennodejs)
add_dependencies(Total_msgs_gennodejs Total_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Total_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Total_msgs
)
_generate_msg_py(Total_msgs
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Total_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(Total_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Total_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(Total_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(Total_msgs_generate_messages Total_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Control.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_py _Total_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Total_msgs/msg/Encoder.msg" NAME_WE)
add_dependencies(Total_msgs_generate_messages_py _Total_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Total_msgs_genpy)
add_dependencies(Total_msgs_genpy Total_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Total_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Total_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Total_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Total_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Total_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Total_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Total_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Total_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Total_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Total_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Total_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Total_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
