#pragma once

#include <tvm/chain_tuple.hpp>

namespace tvm {

// Printing of format elements, splitted into cell-fit sub-tuples

template<unsigned val>
auto make_uint() {
  return to_string<10>(hana::integral_c<unsigned, val>);
}
template<unsigned val>
auto make_hex() {
  return to_string<16>(hana::integral_c<unsigned, val>);
}

template<class T>
class chain_tuple_printer {};

template<class Elem, class... Elems>
class chain_tuple_printer<std::tuple<Elem, Elems...>> {
  static constexpr auto value = element_printer<Elem>::value + ","_s + chain_tuple_printer<Elems...>::value;
};
template<>
class chain_tuple_printer<std::tuple<>> {
  static constexpr auto value = ""_s;
};

template<class T>
struct element_printer {
  static constexpr auto value = chain_tuple_printer<to_std_tuple_t<T>>::value;
};

// "int"_s + to_string<10>(hana::integral_c<unsigned, _bitlen>);
// 3b_x1
template<unsigned _bitlen, unsigned _code>
struct element_printer<bitconst<_bitlen, _code>> {
  static constexpr auto value = make_uint<_bitlen>() + "b_x"_s + make_hex<_code>();
};

// 3b
template<unsigned _bitlen>
struct element_printer<bitfield<_bitlen>> {
  static constexpr auto value = make_uint<_bitlen>() + "b"_s;
};

// dynfield
template<auto _Field>
struct element_printer<dynamic_bitfield<_Field>> {
  static constexpr auto value = "dynfield"_s;
};

// dynamic_uint
template<auto _Field>
struct element_printer<dynamic_uint<_Field>> {
  static constexpr auto value = "dynuint"_s;
};

// dynamic_int
template<auto _Field>
struct element_printer<dynamic_int<_Field>> {
  static constexpr auto value = "dynint"_s;
};

// uint256
template<unsigned _bitlen>
struct element_printer<uint_t<_bitlen>> {
  static constexpr auto value = "uint"_s + make_uint<_bitlen>();
};

// int256
template<unsigned _bitlen>
struct element_printer<int_t<_bitlen>> {
  static constexpr auto value = "int"_s + make_uint<_bitlen>();
};

// varuint16
template<unsigned _bitlen>
struct element_printer<varuint<_bitlen>> {
  static constexpr auto value = "varuint"_s + make_uint<_bitlen>();
};

// varint16
template<unsigned _bitlen>
struct element_printer<varint<_bitlen>> {
  static constexpr auto value = "varint"_s + make_uint<_bitlen>();
};

// hashmap<32,elem>
template<unsigned _keylen, class _element_type>
struct element_printer<HashmapE<_keylen, _element_type>> {
  static constexpr auto value = "hashmap<"_s + make_uint<_keylen>() + ","_s +
    element_printer<_element_type>::value + ">"_s;
};

// anydict
template<>
struct element_printer<anydict> {
  static constexpr auto value = "anydict"_s;
};

// ref<_Tp>
template<class _Tp>
struct element_printer<ref<_Tp>> {
  static constexpr auto value = "ref<"_s + element_printer<_Tp>::value + ">"_s;
};

// cell
template<>
struct element_printer<cell> {
  static constexpr auto value = "cell"_s;
};

// anyval
template<>
struct element_printer<anyval> {
  static constexpr auto value = "anyval"_s;
};

// address
template<>
struct element_printer<MsgAddressSlice> {
  static constexpr auto value = "address"_s;
};

// lazy<Elem> ==> Elem
template<class _Tp>
struct element_printer<lazy<_Tp>> {
  static constexpr auto value = element_printer<_Tp>::value;
};

// empty
template<>
struct element_printer<empty> {
  static constexpr auto value = "empty"_s;
};

// optional<_Tp>
template<class _Tp>
struct element_printer<optional<_Tp>> {
  static constexpr auto value = "optional<"_s + element_printer<_Tp>::value + ">"_s;
};

// std::variant<Types...>
template<class... Types>
struct element_printer<std::variant<Types...>> {
  static constexpr auto value = "variant<"_s + chain_tuple_printer<std::tuple<Types...>>::value + ">"_s;
};

} // namespace tvm

