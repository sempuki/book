# copyright 2024 -- contributors. see license.

load("//:bazel/copts.bzl", "COPTS")

package(default_visibility = ["//visibility:public"])

cc_test(
  name = "ex1_test",
  srcs = ["ex1_test.cpp"],
  deps = [
    "//lib:testing",
    "//lib:type_macros",
  ],
  copts = COPTS,
)
