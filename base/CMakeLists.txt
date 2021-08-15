SET (THIS_SRC
        consecutive_find.h
        find_last.h
        transform_if.h
        flag_mask.h
        improve_containers.h
        sorted_find.h

        manager_pattern.h
        registry_pattern.h

        helpers.h
        observer.h

        dummy.cpp
    )

add_library(aelib_base ${THIS_SRC})
set_property(TARGET aelib_base PROPERTY CXX_STANDARD 17)

add_subdirectory (ut)
