#ifndef ROOSTATS_Model
#define ROOSTATS_Model

#include <functional>
#include <cmath>
#include <array>
#include "Rtypes.h"
#include "Math/Math.h"

static std::size_t quickFactorial(std::size_t n) {
   std::size_t result = 1;
   for (std::size_t i = 1; i < n; ++i) result *= i;
   return result;
}

static auto gGaussian = [] (double x, double m, double s) { 
   double r = (x - m) / s; 
   return std::exp(-(r*r*0.5)) / (s * std::sqrt(2 * ROOT::Math::Pi())); 
};

static auto gPoisson = [] (UInt_t x, double m) { 
   Double_t result = -m;
   for (UInt_t i = 1; i < x; ++i) result += std::log(m) - std::log(i);

   return std::exp(result);
}; 
static auto gExponential = [] (Double_t x, Double_t c) { 
   return std::exp(x * c) * (-c); 
}; // like RooFit for now

static auto lambdaFunc = [] (std::array<Double_t, 2> obs, std::array<Double_t, 1> nuis) {
   return gGaussian(obs[0], nuis[0], 1.0) * gPoisson(obs[1], nuis[0]);
};


// nuisance parameters are: tau (exponential), nsig, nbkg
static auto modelFunc = [] (std::array<Double_t, 1> obs, std::array<Double_t, 3> nuis) {
   return /*gPoisson(30, nuis[1]) */ gGaussian(obs[0], 2.0, 0.5) + /*gPoisson(1000, nuis[2]) */ gExponential(obs[0], nuis[0]);
};

template <typename T> struct remove_class;
template <typename R, typename C, typename... A>
struct remove_class<R (C::*)(A...)> { using type = R(A...); };
template <typename R, typename C, typename... A>
struct remove_class<R (C::*)(A...) const > { using type = R(A...); };
template <typename R, typename C, typename... A>
struct remove_class<R (C::*)(A...) volatile> { using type = R(A...); };
template <typename R, typename C, typename... A>
struct remove_class<R (C::*)(A...) const volatile> { using type = R(A...); };

template <typename T>
struct get_signature { using type = typename remove_class<decltype(&std::remove_reference<T>::type::operator())>::type; };
template <typename R, typename... A>
struct get_signature<R(A...)> { using type = R(A...); };
template <typename R, typename... A>
struct get_signature<R(&)(A...)> { using type = R(A...); };
template <typename R, typename... A>
struct get_signature<R(*)(A...)> { using type = R(A...); };

template <typename F> using make_function_type = std::function<typename get_signature<F>::type>;
template <typename F> make_function_type<F> make_function(F &&f) {
	return make_function_type<F>(std::forward<F>(f));
}



/*template <typename... Args> struct variadic_typedef {};

/template <typename... Args>
struct convert_in_tuple
{
   typedef std::tuple<Args...> type;
};

template <typename... Args>
struct convert_in_tuple<variadic_typedef<Args...>>
{
   typedef typename convert_in_tuple<Args...>::type type;
};

template <typename R, typename PackA>
struct function_signature;

template <typename R, typename... Args>
struct function_signature<R, std::tuple<Args...>>
{
   typedef std::function<R(Args...)> type;
};


template <std::size_t N, typename... Args, typename Func>
typename std::enable_if<N >= 1>::type iterate(std::tuple<Args...> t, Func& f)
{
   f(std::get<N - 1>(t));
   iterate<N - 1>(t, f);
}

template <std::size_t N, typename... Args, typename Func>
typename std::enable_if<N == 0>::type iterate(std::tuple<Args...> t, Func& f)
{
   // nothing to do
}
*/

template <typename T>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<std::function<R(Args...)>>
{
   static const size_t nargs = sizeof...(Args);

   typedef R result_type;

   typedef std::tuple<Args...> args_type;
};


template <typename...> struct join;
template <typename... Args1, typename... Args2>
struct join<std::tuple<Args1...>, std::tuple<Args2...>>
{
   typedef std::tuple<Args1..., Args2...> type;
};

auto mm = [] (double x, double y)->double { return gGaussian(x, y, y) * gPoisson(x, y); };



#endif // ROOSTATS_Model


