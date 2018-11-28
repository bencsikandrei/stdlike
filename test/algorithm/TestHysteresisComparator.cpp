#include <gtest/gtest.h>

namespace stdlike
{

class PositiveHysteresisComparator
{
  public:
    PositiveHysteresisComparator(size_t hysteresis = 0) : mBaseHysteresis{hysteresis}, mHysteresis{mBaseHysteresis}, mResult{false} {}
    template <typename T, typename U, typename Predicate>
    bool operator()(T value, U thresh, Predicate &&p)
    {
        mResult = p(value, thresh);
        if (mResult or mHysteresis > 0)
        {
            resetOrDecrementHysteresis();
            return true;
        }
        return false;
    }

  private:
    void resetOrDecrementHysteresis()
    {
        if (not mResult)
        {
            decrement();
            return;
        }
        reset();
    }
    void reset()
    {
        mHysteresis = mBaseHysteresis;
    }
    void decrement()
    {
        --mHysteresis;
    }

  private:
    size_t const mBaseHysteresis;
    size_t mHysteresis;
    bool mResult;
};

} // namespace stdlike

TEST(TestHysteresisComparator, correctlyComparesTwoNumbersWhenCalledWith0Hysteresis)
{
    stdlike::PositiveHysteresisComparator greaterThenComparator{};

    ASSERT_FALSE(greaterThenComparator(4, 10, std::greater<int>()));
    ASSERT_TRUE(greaterThenComparator(10, 4, std::greater<int>()));
}

TEST(TestHysteresisComparator, correctlyComparesTwoNumbersWhenCalledWith0HysteresisAndDifferentTypes)
{
    stdlike::PositiveHysteresisComparator greaterThenComparator{};

    ASSERT_FALSE(greaterThenComparator(4.f, 10, std::greater<int>()));
    ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
}

TEST(TestHysteresisComparator, correctlyComparesTwoNumbersWhenCalledWithNonZeroHysteresis)
{
    stdlike::PositiveHysteresisComparator greaterThenComparator{1};

    ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
    ASSERT_TRUE(greaterThenComparator(3.f, 4, std::greater<int>()));
    ASSERT_FALSE(greaterThenComparator(3.f, 4, std::greater<int>()));

    /* Hysteresis resets when comparison returns true */
    ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
    ASSERT_TRUE(greaterThenComparator(3.f, 4, std::greater<int>()));
}

TEST(TestHysteresisComparator, correctlyEvaluatesAPredicateWithAgivenHysteresis)
{
    stdlike::PositiveHysteresisComparator greaterThenComparator{1};

    ASSERT_TRUE(greaterThenComparator(10.F, 4, std::greater<int>()));
    ASSERT_TRUE(greaterThenComparator(1.F, 4, std::greater<int>()));
    ASSERT_FALSE(greaterThenComparator(0.F, 4, std::greater<int>()));
}