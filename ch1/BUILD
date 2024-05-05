# copyright 2024 -- contributors. see license.

load("//:bazel/copts.bzl", "COPTS")

package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "ex1",
  srcs= ["ex1.cpp"],
  defines = ["CATCH_CONFIG_MAIN"],
  deps = [
    "@catch2//:catch2",
  ],
  copts = COPTS,
)
