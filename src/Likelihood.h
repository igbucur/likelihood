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
   Likelihood(std::function<R(std::array<TO, NO>, std::array<TP, NP>)>& model, std::vector<std::array<TO, NO>>& data) :
      fModel(model),
      fData(data),
      fParamValues()
   { }

   Likelihood(const Likelihood<std::function<R(std::array<TO, NO>, std::array<TP, NP>)>>& rhs):
      fModel(rhs.fModel),
      fData(rhs.fData),
      fParamValues(rhs.fParamValues)
   { }

   R Evaluate(std::array<TO, NO>& values) const {
      return fModel(values, fParamValues);
   }

   R Evaluate(std::array<TP, NP>& paramValues) {
      Double_t result = 0.0;
      for (std::size_t i = 0; i < fData.size(); ++i) {
         result += fModel(fData[i], paramValues);
      }
      return result; 
   }

   R Evaluate(const std::array<TO, NO>& values, const std::array<TP, NP>& paramValues) const {
      return fModel(values, paramValues);
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


