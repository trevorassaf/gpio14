#pragma once

#include <bitset>
#include <cstdlib>
#include <utility>

namespace Utils
{
namespace Detail
{

template <size_t...IndexSeq, class BoolTuple>
std::bitset<sizeof...(IndexSeq)> to_bitset_impl(std::index_sequence<IndexSeq...>, BoolTuple&& boolTuple)
{
		constexpr size_t size = sizeof...(IndexSeq);
		auto charArray = std::string{(std::get<IndexSeq>(boolTuple) ? '1' : '0')...};
		return std::bitset<size>(charArray);
}

} // namespace Detail

template <class...Bools> std::bitset<sizeof...(Bools)> to_bitset(Bools&&...bools)
{
		constexpr size_t size = sizeof...(bools);
		return Detail::to_bitset_impl(
				std::make_index_sequence<size>(),
				std::make_tuple(bool(bools)...));
}

} // namespace Utils
