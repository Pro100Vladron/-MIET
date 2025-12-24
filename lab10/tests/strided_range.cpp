#include <vector>

#include <boost/range/irange.hpp>

#include <catch2/catch_all.hpp>

#include <strided_range.hpp>

TEST_CASE("strided_range::stride_bigger_width")
{
    auto a = boost::irange(0, 8);
    auto result = make_strided_range(a, 3, 4);
    std::vector<int> expected{0, 1, 2, 4, 5, 6};
    CHECK(std::vector<int>(result.begin(), result.end()) == expected);
}

TEST_CASE("strided_range::width_bigger_stride")
{
    std::vector<int> a{0, 1, 5, 10, 11, 12, 53};
    auto result = make_strided_range(a, 3, 2);
    std::vector<int> expected{0, 1, 5, 10, 11, 12, 53};
    CHECK(std::vector<int>(result.begin(), result.end()) == expected);
}

TEST_CASE("strided_range::stride_equal_width")
{
    std::vector<int> a{1, 2, 3, 4, 5, 6};
    auto result = make_strided_range(a, 2, 2);
    std::vector<int> expected{1, 2, 3, 4, 5, 6};
    CHECK(std::vector<int>(result.begin(), result.end()) == expected);
}

TEST_CASE("strided_range::distance")
{
    auto a = boost::irange(0, 12);
    auto rng = make_strided_range(a, 2, 3);
    std::vector<int> result(rng.begin(), rng.end());
    std::vector<int> expected{0, 1, 3, 4, 6, 7, 9, 10};
    CHECK(result == expected);
}

TEST_CASE("strided_range::corner_case1::zero_width")
{
    std::vector<int> a{1, 2, 3, 4, 5};
    auto rng = make_strided_range(a, 0, 2);
    CHECK(std::vector<int>(rng.begin(), rng.end()).empty());
}

TEST_CASE("strided_range::corner_case2::zero_stride")
{
    std::vector<int> a{1, 2, 3, 4, 5};
    CHECK_THROWS_AS(make_strided_range(a, 2, 0), std::invalid_argument);
}
