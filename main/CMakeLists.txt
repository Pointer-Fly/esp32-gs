#idf_component_register(SRCS "Servo.c" "hongwai.c" "blink_example_main.c"
#                             "st7789.c" "gpio_button.c"
#                        INCLUDE_DIRS "." "ui/"
#)
#
idf_build_get_property(target IDF_TARGET)

if(${target} STREQUAL "linux")
    set(requires esp_stubs protocol_examples_common nvs_flash)
endif()


file(GLOB_RECURSE srcs
        ui/components/*.c
        ui/fonts/*.c
        ui/images/*.c
        ui/screens/*.c
        ui/*.c
)


set(include_dirs
        .
        ui/components
        ui/fonts
        ui/images
        ui/screens
        ui
)


idf_component_register(
        SRCS "st7789.c" "gpio_button.c" "HX711.c" "hongwai.c"
        "blink_example_main.c" ${srcs}
        INCLUDE_DIRS ${include_dirs})

