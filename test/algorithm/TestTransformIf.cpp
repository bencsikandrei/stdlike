#include <gtest/gtest.h>
#include <vector>

namespace stdlike
{

template<typename InputIterator,
         typename OutputIterator,
         typename Transformation,
         typename UnaryPredicate>
void transformIf(InputIterator first1,
                 InputIterator last1,
                 OutputIterator out,
                 Transformation &&t,
                 UnaryPredicate &&p)
{
  while (first1 != last1)
  {
    if (p(*first1)) *out++ = t(*first1);
    ++first1;
  }
}
} // namespace stdlike

TEST(TestTransformIf, doesOkWithAnEmptyIteratorRange)
{
  std::vector<int> empty{};
  std::vector<int> output{};
  stdlike::transformIf(empty.begin(),
                       empty.end(),
                       output.begin(),
                       [](int val) { return 1; },
                       [](int val) { return true; });
  ASSERT_TRUE(output.empty());
}

TEST(TestTransformIf, transformsOnlyElementsForWhichThePredicateHoldsTrue)
{
  std::vector<int> someValues{ 1, 2, 3, 4 };
  std::vector<int> output(someValues.size());
  stdlike::transformIf(someValues.begin(),
                       someValues.end(),
                       output.begin(),
                       [](int val) { return 1; },
                       [](int val) { return true; });
  ASSERT_TRUE(not output.empty());
  ASSERT_TRUE(std::all_of(output.begin(), output.end(), [](int val) { return val == 1; }));

  std::vector<int> someEvenAndOdd{ 1, 2, 3, 4, 5, 6, 7 };
  std::vector<int> only2sPowerForEven{ 4, 16, 36 };
  std::vector<int> result;
  stdlike::transformIf(someEvenAndOdd.begin(),
                       someEvenAndOdd.end(),
                       std::back_inserter(result),
                       [](int val) { return val * val; },
                       [](int val) { return val % 2 == 0; });
  ASSERT_EQ(result, only2sPowerForEven);
}