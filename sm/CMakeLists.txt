SET (THIS_SRC
        sml_event.cpp
        sml_event.h
        sml_eventhandlerexpression.cpp
        sml_eventhandlerexpression.h
        sml.h
        sml_ids.cpp
        sml_ids.h
        sml_if_action.h
        sml_if_guard.h
        sml_if_statemachineinstance.h
        sml_interfaceaction.h
        sml_interfaceguard.h
        sml_simpleaction.cpp
        sml_simpleaction.h
        sml_simpleguard.cpp
        sml_simpleguard.h
        sml_state.cpp
        sml_state.h
        sml_statemachine.cpp
        sml_statemachine.h
        sml_statemachineinstance.cpp
        sml_statemachineinstance.h
    )

add_library(aelib_sm ${THIS_SRC})
set_property(TARGET aelib_sm PROPERTY CXX_STANDARD 17)

add_subdirectory (ut)
