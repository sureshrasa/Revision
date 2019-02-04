/*
 * TestUtility.cpp
 *
 *  Created on: 9 Jan 2019
 *      Author: suresh
 */

#include <iostream>
#include <tuple>
#include "utility.h"

template <int ...Ts>
constexpr void outputChars(char const * s, IntSeq<Ts...> const &)
{
    auto const dummy = {(std::cout << s[Ts], 0)...};

    std::cout << std::endl;
}

template <typename ...Es, int ...Ts>
constexpr void outputTuple1(std::tuple<Es...> const & t, IntSeq<Ts...> const &)
{
    auto const dummy = {(std::cout << std::get<Ts>(t) << ",", 0)...};

    std::cout << std::endl;
}

template <typename ...Es>
constexpr void outputTuple2(std::tuple<Es...> const & t, IntSeq<> const &)
{
    std::cout << std::endl;
}

template <typename ...Es, int ...Ts, int N>
constexpr void outputTuple2(std::tuple<Es...> const & t, IntSeq<N, Ts...> const &)
{
    std::cout << std::get<N>(t) << ",";

    outputTuple2(t, IntSeq<Ts...>{});
}

template <typename T>
constexpr void outputTuple(T const & t)
{
    outputTuple1(t, makeIntSeq<TupleElems<T>::count>());
    outputTuple2(t, makeIntSeq<TupleElems<T>::count>());
}

void testUtility()
{
    std::cout << "IntSeqOf<4>::size()=" << IntSeqOf<4>::type::size() << std::endl;

    outputChars("01234567", makeIntSeq<3>());

    std::cout << "std::tuple<int, char, long> has " << TupleElems<std::tuple<int, char, long>>::count << " elems\n";
    std::cout << "std::pair<int, char> has " << TupleElems<std::pair<int, char>>::count << " elems\n";

    outputTuple(std::make_tuple(-1, 'A', 24567));
    outputTuple(std::make_tuple("Hello", 0x123, "world", 'A', 24567));
}



