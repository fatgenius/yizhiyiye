## Add libraries
set(SCOUT_BASE_SRC 
    src/scout_base.cpp
    # src/scout_serial.cpp
)
add_library(scoutbase STATIC ${SCOUT_BASE_SRC})
set_target_properties(scoutbase PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(scoutbase asyncio)
target_include_directories(scoutbase PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
	$<INSTALL_INTERFACE:include>	
    PRIVATE src)

 ## Add executables
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()