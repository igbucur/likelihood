#ifndef ROOSTATS_Likelihood
#define ROOSTATS_Likelihood

#include <array>
#include <iostream>
#include <map>
#include <tuple>
#include <set>
#include "Model.h"

template <typename... VarArgs>
class Likelihood;

template <typename R, typename... Obs, typename... Nuis>
class Likelihood <std::function<R(std::tuple<Obs...>, std::tuple<Nuis...>)>>
{
   
private:
   std::function<R(std::tuple<Obs...>, std::tuple<Nuis...>)> fModel;
   std::tuple<Nuis...> fParamValues;

public:
   Likelihood(std::function<R(std::tuple<Obs...>, std::tuple<Nuis...>)> model, std::tuple<Nuis...> nuisValues) : 
      fModel(model),
      fParamValues(nuisValues) 
   { }

   R Evaluate(Obs... obs, Nuis... nuis) {
      return fModel(std::tuple<Obs...>(obs...), std::tuple<Nuis...>(nuis...));
   }
   R Evaluate(Obs... obs) {
      return fModel(std::tuple<Obs...>(obs...), fParamValues);
   }
   R Evaluate(std::tuple<std::vector<Obs>...> obsVec) {
      std::size_t nPar = std::tuple_size<decltype(obsVec)>::value;
      Int_t nObs = std::get<0>(obsVec).size();
      for (Int_t i = 0; i < nObs; ++i) {
         std::cout << i << std::endl; 
      }
      return 0.0;
   }
   R Evaluate(std::vector<std::tuple<Obs...>> tupVec) {
      Double_t result = 0.0;
      for (std::size_t i =0; i < tupVec.size(); ++i) {
         result += fModel(tupVec[i], fParamValues);   
      }
      return result;
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


