# copyright 2024 -- contributors. see license.

load("//:bazel/copts.bzl", "COPTS")

package(default_visibility = ["//visibility:public"])

cc_library(
  name = "ex1",
  srcs = ["ex1.hpp"],
  deps = [
    "//lib:type_macros",
  ],
  copts = COPTS,
)

cc_binary(
  name = "ex1_main",
  srcs = ["ex1_main.cpp"],
  deps = [
    ":ex1",
    "//lib:time",
  ],
  copts = COPTS,
)

cc_test(
  name = "ex1_test",
  srcs = ["ex1_test.cpp"],
  deps = [
    "//ch1:ex1",
    "//lib:testing",
  ],
  copts = COPTS,
)
