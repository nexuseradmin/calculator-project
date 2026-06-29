cmake_minimum_required(VERSION 3.10)

project(CalculatorProject C)

# Generate compile_commands.json (Required for SonarQube)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable testing
enable_testing()

# Include header files
include_directories(src)

# Create calculator library
add_library(calculator
    src/calculator.c
)

# Main executable
add_executable(calculator_app
    src/main.c
)

# Link library with executable
target_link_libraries(calculator_app
    calculator
)

# Unit Test
add_executable(test_calculator
    tests/test_calculator.c
)

target_link_libraries(test_calculator
    calculator
)

# Integration Test
add_executable(integration_test
    tests/integration_test.c
)

target_link_libraries(integration_test
    calculator
)

# Register tests
add_test(
    NAME UnitTest
    COMMAND test_calculator
)

add_test(
    NAME IntegrationTest
    COMMAND integration_test
)

# Labels (useful for CI)
set_tests_properties(UnitTest
    PROPERTIES LABELS "unit"
)

set_tests_properties(IntegrationTest
    PROPERTIES LABELS "integration"
)
