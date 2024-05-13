# copyright 2024 -- contributors. see license.

load("//:bazel/copts.bzl", "COPTS")

package(default_visibility = ["//visibility:public"])

cc_library(
  name = "time",
  hdrs= ["time.hpp"],
  copts = COPTS,
)

cc_library(
  name = "testing",
  hdrs= ["testing.hpp"],
  srcs= ["testing.cpp"],
  deps = [
    "@catch2//:catch2_main",
  ],
  copts = COPTS,
)

cc_library(
  name = "type_macros",
  hdrs= ["type_macros.hpp"],
  copts = COPTS,
)

cc_test(
  name = "type_macros_test",
  srcs = ["type_macros_test.cpp"],
  deps = [
    ":testing",
    ":type_macros",
  ],
  copts = COPTS,
)
