#ifndef ROOSTATS_Likelihood
#define ROOSTATS_Likelihood

#include <array>
#include <iostream>
#include <map>
#include <tuple>
#include <set>
#include "Model.h"

template <typename R, typename Pack>
class Likelihood;

template <typename R, typename... Args>
class Likelihood <R, std::tuple<Args...>>
{
private:
   std::function<R(Args...)> fModel;

public:
   Likelihood(std::function<R(Args...)> model) : fModel(model) { }



   R Evaluate(Args... args) {
      return fModel(args...);
   }
  
   void Print() {
      std::cout << "LL: " << Evaluate() << std::endl;
   }
};

//template <typename Func>
//struct LikelihoodFunc {
//   typedef Likelihood<function_traits<decltype(Func)>::result_type, function_traits<decltype(Func)::args_type> type;
//};

#endif // ROOSTATS_Likelihood


