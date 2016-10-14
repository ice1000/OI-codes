#include <iostream>
#include <type_traits>

template <size_t a, size_t b>
using IsDivisible = std::integral_constant<bool, a % b == 0>;

template <bool value, size_t num, typename Seq>
struct IsPrime;

template <size_t num, size_t... n>
struct IsPrime<true, num, std::index_sequence<n...>>
	: std::false_type
{
};

template <size_t num>
struct IsPrime<false, num, std::index_sequence<>>
	: std::true_type
{
};

template <size_t num, size_t num2, size_t... n>
struct IsPrime<false, num, std::index_sequence<num2, n...>>
	: IsPrime<IsDivisible<num, num2>::value, num, std::index_sequence<n...>>
{
};

template <typename T>
struct Extract;

template <size_t... n>
struct Extract<std::index_sequence<n...>>
{
	typedef std::index_sequence<n...> type;
	static constexpr size_t array[] { n... };
};

template <bool test, typename Seq, size_t current, size_t max>
struct GetPrimeImpl;

template <size_t... n, size_t current, size_t max>
struct GetPrimeImpl<false, std::index_sequence<n...>, current, max>
	: Extract<std::index_sequence<n...>>
{
};

template <size_t... n, size_t current, size_t max>
struct GetPrimeImpl<true, std::index_sequence<n...>, current, max>
	: GetPrimeImpl<current + 2 <= max, std::conditional_t<IsPrime<false, current, std::index_sequence<n...>>::value, std::index_sequence<n..., current>, std::index_sequence<n...>>, current + 2, max>
{
};

template <size_t max>
struct primes;

template <>
struct primes<2>
	: Extract<std::index_sequence<2>>
{
};

template <>
struct primes<3>
	: Extract<std::index_sequence<2, 3>>
{
};

template <size_t max>
struct primes
	: std::enable_if_t<max >= 4, GetPrimeImpl<true, std::index_sequence<2, 3>, 3, max>>
{
};

int main(int argc, const char* const* const argv)
{
	for (auto&& item : primes<120>::array)
	{
		std::cout << item << std::endl;
	}
}
