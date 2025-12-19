cmake_minimum_required(VERSION 3.14)
project(lab_7 VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard with threading support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Create the library from your implementation
add_library(DungeonGameLib STATIC
    # NPC implementations
    src/npc/npc.cpp
    src/npc/orc.cpp
    src/npc/squirrel.cpp
    src/npc/druid.cpp
    src/npc/knight.cpp
    src/npc/elf.cpp
    src/npc/dragon.cpp
    src/npc/bear.cpp
    src/npc/robber.cpp
    src/npc/werewolf.cpp
    src/npc/princess.cpp
    src/npc/toad.cpp
    src/npc/slaver.cpp
    src/npc/pegasus.cpp
    src/npc/bittern.cpp
    src/npc/desman.cpp
    src/npc/bull.cpp
    
    # Factory
    src/factory/npc_factory.cpp
    src/factory/visitor_factory.cpp
    
    # Visitor
    src/visitor/battle_visitor.cpp
    
    # Observer
    src/observer/console_observer.cpp
    src/observer/file_observer.cpp
    
    # Game
    src/game/game_map.cpp
    
    # Main editor
    src/dungeon_editor.cpp
)

find_package(Threads REQUIRED)

# Include directories
target_include_directories(DungeonGameLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set properties for the library
target_compile_features(DungeonGameLib PUBLIC cxx_std_17)

# Link threading library
target_link_libraries(DungeonGameLib PRIVATE Threads::Threads)

# Main executable
add_executable(dungeon_game
    src/main.cpp
)

target_link_libraries(dungeon_game
    DungeonGameLib
)

# Download GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(tests 
    tests/test_npc.cpp
    tests/test_dungeon.cpp
)

# Link test executable with library and gtest
target_link_libraries(tests 
    DungeonGameLib 
    GTest::gtest_main
)

# Include directories for tests
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Register tests
include(GoogleTest)
gtest_discover_tests(tests
    TEST_PREFIX "lab7_"
    TEST_SUFFIX ""
)

# Optional: Add post-build events or custom targets
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tests
    COMMENT "Running tests..."
)

add_custom_target(run_game
    COMMAND dungeon_game
    DEPENDS dungeon_game
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running dungeon game..."
)

# Set output directories for better organization
set_target_properties(dungeon_game tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(DungeonGameLib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Print configuration info
message(STATUS "========================================")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source Directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Binary Directory: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "========================================")

# Create install targets (optional)
install(TARGETS dungeon_game
    RUNTIME DESTINATION bin
)

install(TARGETS tests
    RUNTIME DESTINATION bin
)

install(TARGETS DungeonGameLib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Add target for building everything
add_custom_target(build_all
    DEPENDS dungeon_game tests
    COMMENT "Building all targets..."
)