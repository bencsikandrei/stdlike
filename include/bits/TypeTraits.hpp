#pragma once

namespace stdlike
{
template<typename T>
struct HasHandle
{
  HasHandle() { void (*p)() = constraits; }

private:
  static void constraits() { void (T::*test)() = &T::handle; }
};

// experimental
#define HasMethod(methodName, returnType, ...)                                                     \
  template<typename T>                                                                             \
  struct Has##methodName                                                                           \
  {                                                                                                \
    Has##methodName() { void(*p) = contraints; }                                                   \
                                                                                                   \
  private:                                                                                         \
    static void constraits() { returnType (T::*test)(__VA__ARGS__) = &T::methodName; }           \
  };
} // namespace stdlike