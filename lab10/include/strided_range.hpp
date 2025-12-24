#ifndef STRIDED_RANGE_HPP
#define STRIDED_RANGE_HPP

#include <boost/range/iterator_range.hpp>

#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

template<class It>
class strided_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = typename std::iterator_traits<It>::value_type;
    using difference_type   = typename std::iterator_traits<It>::difference_type;
    using pointer           = typename std::iterator_traits<It>::pointer;
    using reference         = typename std::iterator_traits<It>::reference;

    strided_iterator() = default;

    strided_iterator(It cur, It end, std::size_t width, std::size_t stride, std::size_t pos = 0)
        : cur_(cur), end_(end), width_(width), stride_(stride), pos_(pos) {}

    reference operator*() const { return *cur_; }
    pointer operator->() const { return std::addressof(*cur_); }

    strided_iterator& operator++()
    {
        if (cur_ == end_) return *this;

        ++cur_;
        ++pos_;

        if (width_ == 0) {
            cur_ = end_;
            return *this;
        }

        if (pos_ >= width_) {
            const std::size_t skip = (stride_ > width_) ? (stride_ - width_) : 0u;
            for (std::size_t i = 0; i < skip && cur_ != end_; ++i) ++cur_;
            pos_ = 0;
        }
        return *this;
    }

    strided_iterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }

    friend bool operator==(const strided_iterator& a, const strided_iterator& b) { return a.cur_ == b.cur_; }
    friend bool operator!=(const strided_iterator& a, const strided_iterator& b) { return !(a == b); }

private:
    It cur_{};
    It end_{};
    std::size_t width_{0};
    std::size_t stride_{1};
    std::size_t pos_{0};
};

template<class Range>
auto make_strided_range(Range&& r, std::size_t width, std::size_t stride)
{
    if (stride == 0) throw std::invalid_argument("stride must be > 0");

    using std::begin;
    using std::end;

    auto b = begin(r);
    auto e = end(r);

    using It = decltype(b);

    if (width == 0) {
        return boost::make_iterator_range(
            strided_iterator<It>(e, e, width, stride),
            strided_iterator<It>(e, e, width, stride)
        );
    }

    return boost::make_iterator_range(
        strided_iterator<It>(b, e, width, stride),
        strided_iterator<It>(e, e, width, stride)
    );
}

#endif // STRIDED_RANGE_HPP
