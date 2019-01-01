#include <gtest/gtest.h>
#include <vector>
#include <iterator>
#include <list>

namespace stdlike
{

template<typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator find_all(InputIterator first, InputIterator last, OutputIterator dest, Predicate &&p)
{
    while(first != last) {
        if(p(*first)) {
            *dest = first;
            ++dest;
        }
        ++first;
    }
    return dest;
}

} // namespace stdlike

TEST(TestFindAll, findsNothingIfRangeIsEmpty)
{
  std::vector<int> empty{};
  std::vector<std::vector<int>::iterator> matches{};
  auto end { stdlike::find_all(empty.begin(), empty.end(), std::back_inserter(matches), [](auto elem) { return true; }) };

  ASSERT_TRUE(matches.size() == 0);
}

TEST(TestFindAll, findsOneElementWhenItsPresentInTheRange)
{
  std::vector<int> oneElement{ 1 };
  std::list<std::vector<int>::iterator> matches{};
  auto res{ stdlike::find_all(oneElement.begin(), oneElement.end(), std::inserter(matches, matches.end()), [](auto elem) { return true; }) };

  ASSERT_EQ(*matches.front(), 1);
}

TEST(TestFindAll, findsMultipleElementsThatAreAcceptedByThePredicate)
{
  std::vector<int> evenAndOddElements{ 1, 2, 3, 4, 5, 6 };
  std::vector<int> onlyEven { 2, 4, 6 };
  std::list<std::vector<int>::iterator> matches{};
  auto res{ stdlike::find_all(evenAndOddElements.begin(), evenAndOddElements.end(), std::inserter(matches, matches.end()), [](auto elem) { return true; }) };

  ASSERT_EQ(*matches.front(), 1);
}