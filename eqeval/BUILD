cc_library(
    name = "equation_evaluator_lib",
    srcs = [
        "equation_evaluator.cpp",
        "equation_parser.cpp",
        "string_utils.cpp",
    ],
    hdrs = [
        "equation_evaluator.h",
        "equation_parser.h",
        "exception.h",
        "string_utils.h",
    ],
)

cc_binary(
    name = "equation_evaluator",
    srcs = ["main.cpp"],
    deps = [":equation_evaluator_lib",
            "@boost//:program_options"],
)

cc_test(
    name = "test_hello",
    srcs = ["test/test_hello.cpp"],
    deps = ["@catch//:catch_main"],
    size = 'small',
)