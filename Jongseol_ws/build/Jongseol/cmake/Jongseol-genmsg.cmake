# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "Jongseol: 3 messages, 0 services")

set(MSG_I_FLAGS "-IJongseol:/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(Jongseol_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg" NAME_WE)
add_custom_target(_Jongseol_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Jongseol" "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg" ""
)

get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg" NAME_WE)
add_custom_target(_Jongseol_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Jongseol" "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg" ""
)

get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg" NAME_WE)
add_custom_target(_Jongseol_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "Jongseol" "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg" "Jongseol/obj"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Jongseol
)
_generate_msg_cpp(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Jongseol
)
_generate_msg_cpp(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg"
  "${MSG_I_FLAGS}"
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Jongseol
)

### Generating Services

### Generating Module File
_generate_module_cpp(Jongseol
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Jongseol
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(Jongseol_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(Jongseol_generate_messages Jongseol_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_cpp _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_cpp _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_cpp _Jongseol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Jongseol_gencpp)
add_dependencies(Jongseol_gencpp Jongseol_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Jongseol_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Jongseol
)
_generate_msg_eus(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Jongseol
)
_generate_msg_eus(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg"
  "${MSG_I_FLAGS}"
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Jongseol
)

### Generating Services

### Generating Module File
_generate_module_eus(Jongseol
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Jongseol
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(Jongseol_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(Jongseol_generate_messages Jongseol_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_eus _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_eus _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_eus _Jongseol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Jongseol_geneus)
add_dependencies(Jongseol_geneus Jongseol_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Jongseol_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Jongseol
)
_generate_msg_lisp(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Jongseol
)
_generate_msg_lisp(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg"
  "${MSG_I_FLAGS}"
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Jongseol
)

### Generating Services

### Generating Module File
_generate_module_lisp(Jongseol
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Jongseol
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(Jongseol_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(Jongseol_generate_messages Jongseol_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_lisp _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_lisp _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_lisp _Jongseol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Jongseol_genlisp)
add_dependencies(Jongseol_genlisp Jongseol_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Jongseol_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Jongseol
)
_generate_msg_nodejs(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Jongseol
)
_generate_msg_nodejs(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg"
  "${MSG_I_FLAGS}"
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Jongseol
)

### Generating Services

### Generating Module File
_generate_module_nodejs(Jongseol
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Jongseol
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(Jongseol_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(Jongseol_generate_messages Jongseol_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_nodejs _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_nodejs _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_nodejs _Jongseol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Jongseol_gennodejs)
add_dependencies(Jongseol_gennodejs Jongseol_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Jongseol_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Jongseol
)
_generate_msg_py(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Jongseol
)
_generate_msg_py(Jongseol
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg"
  "${MSG_I_FLAGS}"
  "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Jongseol
)

### Generating Services

### Generating Module File
_generate_module_py(Jongseol
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Jongseol
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(Jongseol_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(Jongseol_generate_messages Jongseol_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/init.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_py _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/obj.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_py _Jongseol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/autonav/Jongseol_2024/Jongseol_ws/src/Jongseol/msg/objs.msg" NAME_WE)
add_dependencies(Jongseol_generate_messages_py _Jongseol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(Jongseol_genpy)
add_dependencies(Jongseol_genpy Jongseol_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS Jongseol_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Jongseol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/Jongseol
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(Jongseol_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Jongseol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/Jongseol
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(Jongseol_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Jongseol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/Jongseol
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(Jongseol_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Jongseol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/Jongseol
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(Jongseol_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Jongseol)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Jongseol\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/Jongseol
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(Jongseol_generate_messages_py std_msgs_generate_messages_py)
endif()
