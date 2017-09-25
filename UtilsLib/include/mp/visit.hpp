#ifndef VISIT_HPP
#define VISIT_HPP

// UtilsLib
#include <mp/get.hpp>
#include <mp/length.hpp>

// Standard
#include <cstddef>
#include <type_traits>
#include <tuple>

// There are two types of visit: call_same and call.
// call_same calls the Visitor's call function with the same argument. This can be void
// call calls the Visitor's call function using the i-th entry of the argument tuple.

namespace psin {
namespace mp {

template<
	typename TypeList,
	template<typename> class Visitor,
	std::size_t RevertedPosition = mp::length<TypeList>::value - 1
>
struct visit
{
	constexpr static std::size_t Pos = mp::length<TypeList>::value - 1 - RevertedPosition;

	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call(Tuple & arg )
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call( std::get<Pos>(arg) );
		visit< TypeList, Visitor, RevertedPosition-1 >::call( arg );
	}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call_same(Args &...args)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call(args...);
		visit< TypeList, Visitor, RevertedPosition-1 >::call_same(args...);
	}


	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call(Tuple & arg )
	{}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call_same(Args &...args)
	{}
};

template<
	typename TypeList,
	template<typename> class Visitor
>
struct visit<TypeList, Visitor, 0>
{
	constexpr static std::size_t Pos = mp::length<TypeList>::value - 1;

	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call(Tuple & arg)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call( std::get<Pos>(arg) );
	}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call_same(Args &...args)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call(args...);
	}


	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call(Tuple & arg )
	{}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call_same(Args &...args)
	{}
};

	
} // mp
} // psin

#endif // VISIT_HPP
