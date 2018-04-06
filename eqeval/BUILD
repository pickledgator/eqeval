cc_library(
    name = "equation_evaluator_lib",
    srcs = [
        "equation_evaluator.cpp",
        "equation_parser.cpp",
        "string_utils.cpp",
        "io_utils.cpp",
        "shunting_yard.cpp",
    ],
    hdrs = [
        "equation_evaluator.h",
        "equation_parser.h",
        "exception.h",
        "string_utils.h",
        "io_utils.h",
        "shunting_yard.h",
    ],
)

cc_binary(
    name = "equation_evaluator",
    srcs = ["main.cpp"],
    deps = [":equation_evaluator_lib",
            "@boost//:program_options"],
)

cc_test(
    name = "unittests",
    srcs = [
        "test/test_string_utils.cpp",
        "test/test_io_utils.cpp",
        "test/test_exception.cpp",
        "test/test_equation_parser.cpp",
        "test/test_equation_evaluator.cpp",
        "test/test_shunting_yard.cpp",
    ],
    deps = [
        "@catch//:catch_main",
        ":equation_evaluator_lib",
    ],
    data = [
        "test/test_equations_valid.txt",
        "test/test_equations_invalid.txt",
    ],
    size = 'small',
)
