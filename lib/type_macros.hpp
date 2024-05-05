// Copyright 2024 -- CONTRIBUTORS. See LICENSE.

#pragma once

#define DECLARE_COPY_DEFAULT(ClassName)  \
  ClassName(const ClassName&) = default; \
  ClassName& operator=(const ClassName&) = default;

#define DECLARE_COPY_DELETE(ClassName)  \
  ClassName(const ClassName&) = delete; \
  ClassName& operator=(const ClassName&) = delete;

#define DECLARE_MOVE_DEFAULT(ClassName)      \
  ClassName(ClassName&&) noexcept = default; \
  ClassName& operator=(ClassName&&) noexcept = default;

#define DECLARE_MOVE_DELETE(ClassName) \
  ClassName(ClassName&&) = delete;     \
  ClassName& operator=(ClassName&&) = delete;

