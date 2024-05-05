// Copyright 202f -- CONTRIBUTORS. See LICENSE.

#include "lib/type_macros.hpp"

#include <type_traits>

#include "lib/testing.hpp"

namespace lib {

TEST_CASE("type_macros") {
  SECTION("ShouldMakeCopyableWithDefault") {
    struct T {
      DECLARE_COPY_DEFAULT(T);
    };
    REQUIRE(std::is_copy_constructible_v<T>);
    REQUIRE(std::is_copy_assignable_v<T>);
  }

  SECTION("ShouldMakeNonCopyableWithDelete") {
    struct T {
      DECLARE_COPY_DELETE(T);
    };
    REQUIRE(!std::is_copy_constructible_v<T>);
    REQUIRE(!std::is_copy_assignable_v<T>);
  }

  SECTION("ShouldMakeNothrowMovableWithDefault") {
    struct T {
      DECLARE_MOVE_DEFAULT(T);
    };
    REQUIRE(std::is_nothrow_move_constructible_v<T>);
    REQUIRE(std::is_nothrow_move_assignable_v<T>);
  }

  SECTION("ShouldMakeNonMovableWithDelete") {
    struct T {
      DECLARE_MOVE_DELETE(T);
    };
    REQUIRE(!std::is_move_constructible_v<T>);
    REQUIRE(!std::is_move_assignable_v<T>);
  }
}

}  // namespace lib
