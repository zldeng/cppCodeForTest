#include_directories(/usr/local/mioji/include)
include_directories(${PROJECT_SOURCE_DIR})
#link_directories(/usr/local/mioji/lib)

add_executable (test_task 
	MiojiVerifyRouter.cpp
	tool.cpp
	test_task.cpp
	)
target_link_libraries (test_task )
install(TARGETS test_task DESTINATION bin)


