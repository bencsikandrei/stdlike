#include <bits/PositiveHysteresisComparator.hpp>

namespace stdlike
{

PositiveHysteresisComparator::PositiveHysteresisComparator(size_t hysteresis) : mBaseHysteresis{hysteresis}, mHysteresis{}, mResult{false} {}
void PositiveHysteresisComparator::resetOrDecrementHysteresis()
{
    if (not mResult)
    {
        decrementIfNotZero();
        return;
    }
    reset();
}
void PositiveHysteresisComparator::reset()
{
    mHysteresis = mBaseHysteresis;
}
void PositiveHysteresisComparator::decrementIfNotZero()
{
    if (mHysteresis == 0)
        return;
    --mHysteresis;
}

} // namespace stdlike
