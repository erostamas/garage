cmake_minimum_required(VERSION 3.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
set(Boost_USE_STATIC_LIBS ON)
enable_testing()

# compiler and linker flags
if ((NOT CMAKE_CXX_FLAGS) OR (CMAKE_CXX_FLAGS MATCHES "^[ \t]*$"))
  set(CXX11_FLAG "-std=c++11")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.2")
      set(CXX11_FLAG "-std=c++0x")
  endif()
  set(CMAKE_CXX_FLAGS "-O3 -g ${CXX11_FLAG} -Werror -Wall -DBOOST_LOG_DYN_LINK -DNDEBUG -Wno-unused-result -lpthread -lwiringPi")
  if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message("Coverage mode selected")
      set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall -DBOOST_LOG_DYN_LINK -fprofile-arcs -ftest-coverage -lpthread -lwiringPi")
  endif()
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall -lpthread -lwiringPi")
  endif()
endif()

#3pp
set(BOOST_UNITTEST_LIBS "boost_unit_test_framework")
if(BOOST_INCLUDE_DIRS AND BOOST_LIBRARY_DIRS)
  message("-- BOOST paths specified: -I${BOOST_INCLUDE_DIRS} -L${BOOST_LIBRARY_DIRS}")
  include_directories(BEFORE ${BOOST_INCLUDE_DIRS})
  link_directories(${BOOST_LIBRARY_DIRS})
else()
  find_package(BOOST)
  if(NOT BOOST_FOUND)
    message(FATAL_ERROR "-- Boost not found, not specified, specify with -DBOOST_INCLUDE_DIRS and -DBOOST_LIBRARY_DIRS")
  endif()
  include_directories(BEFORE ${BOOST_INCLUDE_DIRS})
endif()

add_subdirectory(src)

enable_testing()

INSTALL(FILES garage.service
	DESTINATION /etc/systemd/system/
	PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
