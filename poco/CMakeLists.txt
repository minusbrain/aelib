SET (THIS_SRC
        logger.h
        logging.h
        logmanager.h
        logsource.h

        dummy.cpp
    )

add_library(aelib_poco ${THIS_SRC})
set_property(TARGET aelib_poco PROPERTY CXX_STANDARD 17)
target_link_libraries(aelib_poco PUBLIC Poco::Foundation Poco::Util)

#add_subdirectory (ut)
