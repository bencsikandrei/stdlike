#include <gtest/gtest.h>

#include <Algorithm.hpp>

TEST(TestHysteresisComparator, correctlyComparesTwoNumbersWhenCalledWith0Hysteresis)
{
  stdlike::PositiveHysteresisComparator greaterThenComparator{};

  ASSERT_FALSE(greaterThenComparator(4, 10, std::greater<int>()));
  ASSERT_TRUE(greaterThenComparator(10, 4, std::greater<int>()));
}

TEST(TestHysteresisComparator,
     correctlyComparesTwoNumbersWhenCalledWith0HysteresisAndDifferentTypes)
{
  stdlike::PositiveHysteresisComparator greaterThenComparator{};

  ASSERT_FALSE(greaterThenComparator(4.f, 10, std::greater<int>()));
  ASSERT_FALSE(greaterThenComparator(9.f, 10, std::greater<int>()));
  ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
}

TEST(TestHysteresisComparator, correctlyComparesInTheCaseWhenFirstCallShouldReturnFalse)
{
  stdlike::PositiveHysteresisComparator greaterThenComparator{ 1 };

  ASSERT_FALSE(greaterThenComparator(4, 10, std::greater<int>()));
  ASSERT_FALSE(greaterThenComparator(3, 10, std::greater<int>()));
  ASSERT_TRUE(greaterThenComparator(10, 4, std::greater<int>()));
}

TEST(TestHysteresisComparator, correctlyComparesTwoNumbersWhenCalledWithNonZeroHysteresis)
{
  stdlike::PositiveHysteresisComparator greaterThenComparator{ 1 };

  ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
  ASSERT_TRUE(greaterThenComparator(3.f, 4, std::greater<int>()));
  ASSERT_FALSE(greaterThenComparator(3.f, 4, std::greater<int>()));

  /* Hysteresis resets when comparison returns true */
  ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
  ASSERT_TRUE(greaterThenComparator(3.f, 4, std::greater<int>()));
}

TEST(TestHysteresisComparator, correctlyEvaluatesAPredicateWithAgivenHysteresis)
{
  stdlike::PositiveHysteresisComparator greaterThenComparator{ 1 };

  ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
  ASSERT_TRUE(greaterThenComparator(1.F, 4, std::greater<int>()));
  ASSERT_FALSE(greaterThenComparator(0.F, 4, std::greater<int>()));

  // try a bigger state
  size_t hysteresisSize{ 500 };
  stdlike::PositiveHysteresisComparator greaterThenComparatorBig{ hysteresisSize };
  ASSERT_FALSE(greaterThenComparatorBig(0.F, 4, std::greater<int>()));
  ASSERT_TRUE(greaterThenComparatorBig(10.F, 4, std::greater<int>()));
  for (size_t count{ hysteresisSize }; count > 0; --count)
  {
    greaterThenComparatorBig(1.F, 4, std::greater<int>());
  }
  ASSERT_FALSE(greaterThenComparatorBig(0.F, 4, std::greater<int>()));
}