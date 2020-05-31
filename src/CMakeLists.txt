link_directories(/usr/lib/erostamas/)

add_library(garage_library STATIC
    Garage.cc
    StringCommandAdapter.cc
)

target_link_libraries(garage_library
    boost_log
    boost_thread
    boost_system
)

add_executable(garage
    main.cc)

target_link_libraries(garage
    garage_library
    et_logging
    et_command_processor
    et_config)

INSTALL(TARGETS garage
	DESTINATION /usr/bin/
	PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
