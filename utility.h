/*
 * utility.h
 *
 *  Created on: 9 Jan 2019
 *      Author: suresh
 */

#ifndef UTILITY_H_
#define UTILITY_H_


template <int ...Ts>
struct IntSeq
{
    constexpr static int size() { return sizeof...(Ts); }
};

template <int N, typename T>
struct IntSeqCat
{
};

template <int N, int ...Ts>
struct IntSeqCat<N, IntSeq<Ts...>>
{
    using type = IntSeq<Ts..., N>;
};


template <int N>
struct IntSeqOf
{
    using type = typename IntSeqCat<N-1, typename IntSeqOf<N-1>::type>::type;
};

template<>
struct IntSeqOf<0>
{
    using type = IntSeq<>;
};

template <int N> auto makeIntSeq() { return typename IntSeqOf<N>::type{}; }

template <typename T>
struct TupleElems{};

template <template <typename ...> class Tuple, typename ...Ts>
struct TupleElems<Tuple<Ts...>>
{
    static const int count = sizeof...(Ts);
};

#endif /* UTILITY_H_ */
