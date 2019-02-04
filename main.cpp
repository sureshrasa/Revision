/*
 * main.cpp
 *
 *  Created on: 7 Jan 2019
 *      Author: suresh
 */

#include <cstddef>
#include <type_traits>
#include "utility.h"
#include <iostream>
#include <stdexcept>
#include <string>

template <size_t N>
class FixStr
{
public:
    template <size_t M, typename = typename std::enable_if<M <= N+1>::type>
    constexpr explicit FixStr(const char (&s)[M]) : FixStr(s, makeIntSeq<M>())
    {
    }

    constexpr char operator[](size_t const i) const
    {
        return i <= size_ ? data_[i] : (throw std::out_of_range(std::to_string(i)), 0);
    }

    constexpr size_t length() const { return size_; }

private:
    template <int ...Is>
    constexpr FixStr(char const * s, IntSeq<Is...> const &) :
        data_{(Is < sizeof...(Is) ? s[Is] : char(0))...},
        size_{sizeof...(Is) - 1}
    {
    }

    char data_[N+1];
    size_t size_;
};

template <size_t M>
constexpr auto makeFixStr(const char (&s)[M])
{
    return FixStr<M>{s};
}

template <typename T, T ...Cs>
constexpr FixStr<sizeof...(Cs)+1> operator"" _fs() noexcept
{
    return makeFixStr({Cs..., T(0)});
}

void testUtility();

int main()
{
    testUtility();

    auto fs = makeFixStr("ABCDEF");
    std::cout << fs[fs.length()-1] << ", length = " << fs.length() << std::endl;

    auto fs2 = "ABC"_fs;
    std::cout << fs2[fs2.length()-1] << ", length = " << fs2.length() << std::endl;

    fs2[5];
    return 0;
}
