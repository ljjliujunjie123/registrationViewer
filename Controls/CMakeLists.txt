include_directories(../Utils)
aux_source_directory(. SRC)
list(REMOVE_ITEM SRC ./test.cpp)
message("Removed executable file from CONTROL_SRCS")
message(${SRC})

aux_source_directory(../Utils UTILS_SRC)
add_executable(ControlTest test.cpp ${SRC} ${UTILS_SRC})
#add_library(controls ${CONTROL_SRCS})