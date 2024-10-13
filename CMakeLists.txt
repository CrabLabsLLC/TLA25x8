cmake_minimum_required(VERSION 3.10)

if(IDF_VERSION_MAJOR GREATER_EQUAL 4)

    idf_component_register( SRCS_DIR src
                            INCLUDE_DIRS include)

else()

    project(TLA25x8
            LANGUAGES C
            DESCRIPTION "A Hardware Agnostic driver for the TLA25x8 GPIO/ADC Chip")

    file(GLOB SOURCES "src/*.c")
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
    target_include_directories(${PROJECT_NAME} PUBLIC include)

endif()
