#pragma once

#include <cstddef>

namespace stdlike
{

class PositiveHysteresisComparator final
{
  public:
    PositiveHysteresisComparator(size_t hysteresis = 0);

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

    size_t getHysteresis() const { return mBaseHysteresis; }

  private:
    void resetOrDecrementHysteresis();
    void reset();
    void decrementIfNotZero();

  private:
    size_t const mBaseHysteresis;
    size_t mHysteresis;
    bool mResult;
};

} // namespace stdlike