#ifndef ROOSTATS_Model
#define ROOSTATS_Model

#include <functional>
#include <cmath>
#include "Rtypes.h"

static auto gGaussian = [] (double x, double m, double s) { double r = (x - m) / s; return std::exp(-(r*r)) / s; };
static auto gPoisson = [] (UInt_t x, double m) { return std::exp(-m) * std::pow(m, x); }; 
auto lambdaFunc =  [] (std::tuple<double, UInt_t> obs, std::tuple<double> nuis) {
   return gGaussian(std::get<0>(obs), std::get<0>(nuis), 1.0) *
      gPoisson(std::get<1>(obs), std::get<0>(nuis));
};



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


