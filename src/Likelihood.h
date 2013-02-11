#ifndef ROOSTATS_Likelihood
#define ROOSTATS_Likelihood

#include <array>
#include <iostream>
#include <map>
#include <tuple>
#include <set>
#include "Model.h"

template <typename FuncType>
class Likelihood;
/*
template <typename... Obs, typename... Nuis>
class Likelihood < <lambda(std::tuple<Obs...>, std::tuple<Nuis...>)> >
{
   Likelihood(<lambda(std::tuple<Obs...>, std::tuple<Nuis...>)> model) {}
};
*/
template <typename R, typename TO, std::size_t NO, typename TP, std::size_t NP>
class Likelihood <std::function<R(std::array<TO, NO>, std::array<TP, NP>)>>
{
   
private:
   std::function<R(std::array<TO, NO>, std::array<TP, NP>)> fModel;
   std::vector<std::array<TO, NO>>& fData;
   std::array<TP, NP> fParamValues;
//   std::array<TO, NO> fValues;



public:
/*   Likelihood(std::function<R(std::tuple<Obs...>, std::tuple<Nuis...>)> model, std::tuple<Nuis...> nuisValues) : 
      fModel(model),
      fData(0),
      fParamValues(nuisValues) 
   { }
*/
   Likelihood(std::function<R(std::array<TO, NO>, std::array<TP, NP>)>& model, std::vector<std::array<TO, NO>>& data) :
      fModel(model),
      fData(data),
      fParamValues()
   { }

   R Evaluate(std::array<TO, NO>& values) {
      return fModel(values, fParamValues);
   }

   R Evaluate(std::array<TP, NP>& paramValues) {
      Double_t result = 0.0;
      for (std::size_t i = 0; i < fData.size(); ++i) {
         result += fModel(fData[i], paramValues);
      }
      return result; 
   }
  
   R Evaluate(const TP* paramValues) {
      for (std::size_t i = 0; i < NP; ++i) fParamValues[i] = paramValues[i];
      return Evaluate(fParamValues);
   }
  
   R Evaluate(std::vector<std::array<TO, NO>> data) {
      Double_t result = 0.0;
      for (std::size_t i =0; i < data.size(); ++i) {
         result += fModel(data[i], fParamValues);   
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


