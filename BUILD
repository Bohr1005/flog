cc_library(
    name = "flog",
    includes = ["include"],
    hdrs = glob(["include/*"]),
    srcs = glob(["src/*"]),
)
cc_binary(
    name = "bm_any",
    srcs = ["benchmark/bm_any.cpp"],
    deps = [
        "flog",
        "@benchmark",
    ],
)

cc_binary(
    name = "log_cout",
    srcs = ["examples/log_cout.cpp"],
    deps = [
        "flog",
        "@benchmark",
    ],
)


cc_binary(
    name = "log_file",
    srcs = ["examples/log_file.cpp"],
    deps = [
        "flog",
        "@benchmark",
    ],
)
cc_binary(
    name = "bm_logger",
    srcs = ["benchmark/bm_logger.cpp"],
    deps = [
        "flog",
        "@benchmark",
    ],
)
cc_binary(
    name = "bm_log",
    srcs = ["benchmark/bm_log.cpp"],
    deps = [
        "flog",
        "@benchmark",
    ],
)


cc_test(
    name = "ut_fmt",
    deps = ["flog","@gtest//:gtest_main"],
    srcs = ["unittest/ut_fmt.cpp"],

)

cc_test(
    name = "ut_fatal",
    deps = ["flog","@gtest//:gtest_main"],
    srcs = ["unittest/ut_fatal.cpp"],

)

cc_test(
    name = "ut_any",
    deps = ["flog","@gtest//:gtest_main"],
    srcs = ["unittest/ut_any.cpp"],

)

cc_test(
    name = "ut_log",
    deps = ["flog","@gtest//:gtest_main"],
    srcs = ["unittest/ut_log.cpp"],

)

cc_test(
    name = "ut_logger",
    deps = ["flog","@gtest//:gtest_main"],
    srcs = ["unittest/ut_logger.cpp"],

)

cc_test(
    name = "ut_appender",
    deps = ["flog","@gtest//:gtest_main"],
    srcs = ["unittest/ut_appender.cpp"],

)