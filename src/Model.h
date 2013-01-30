#ifndef ROOSTATS_Model
#define ROOSTATS_Model

#include <functional>
#include <cmath>
#include "Rtypes.h"

static auto gGaussian = [] (double x, double m, double s) { double r = (x - m) / s; return std::exp(-(r*r)) / s; };
static auto gPoisson = [] (int x, double m) { return std::exp(-m) * std::pow(m, x); }; 


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


auto ll = [] (double x, double y)->double { return gGaussian(x, y, y) * gPoisson(x, y); };
static std::function<double(double, double)> func = ll;



#endif // ROOSTATS_Model


