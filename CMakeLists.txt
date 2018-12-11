# Add as a subdirectory SimpleRenderEngineProject using add_subdirectory
IF (NOT DEFINED all_libs)
    message( FATAL_ERROR "This CMakeLists.txt must be included using the command add_subdirectory(name)" )
ENDIF (NOT DEFINED all_libs)
# Ensure SimpleRenderEngineProject is up-to-date
IF (WIN32)
    IF (NOT DEFINED DLLFileList)
        message( FATAL_ERROR "The SimpleRenderEngineProject has been updated. Clone the project (https://github.com/mortennobel/SimpleRenderEngineProject) again the project again and start over." )
    ENDIF(NOT DEFINED DLLFileList)
ENDIF(WIN32)

# Add hpp and cpp files to JunkDragon variable
file(GLOB JunkDragon
        "src/*.hpp"
        "src/*.h"
        "src/*.cpp"
        )

# Compile cpp files (from JunkDragon variable)
add_executable(junkdragon ${JunkDragon})
target_link_libraries(junkdragon ${all_libs})

# copy files to dest
file(COPY src/junkdragon.json src/junkdragon.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY src/junkdragon.json src/junkdragon.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY src/junkdragon.json src/junkdragon.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/background.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY src/background.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY src/background.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/level0.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY src/level0.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY src/level0.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/level1.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY src/level1.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY src/level1.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY assets/menu_music.wav assets/game_music.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY assets/menu_music.wav assets/game_music.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY assets/menu_music.wav assets/game_music.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY assets/breathe_fire.wav assets/pick_up.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY assets/breathe_fire.wav assets/pick_up.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY assets/breathe_fire.wav assets/pick_up.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

IF (WIN32)
    # Copy dll files to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
    file(COPY ${DLLFileList} DESTINATION .)

    # Set working directory to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    set_target_properties(junkdragon PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)
ENDIF(WIN32)
