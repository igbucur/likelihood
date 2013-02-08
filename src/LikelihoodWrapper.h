#ifndef ROOSTATS_LikelihoodWrapper
#define ROOSTATS_LikelihoodWrapper

#include "Likelihood.h"
#include "Math/IFunction.h"

template <std::size_t I>
struct CArray;

template <>
struct CArray<0>
{
   template <typename... Ts>
   static void toTuple(std::tuple<Ts...>& t, const Double_t* a) {}
};

template <std::size_t I>
struct CArray
{
   template <typename... Ts>
   static void toTuple(std::tuple<Ts...>& t, const Double_t* a)
   {
      std::get<I-1>(t) = a[I-1];
      CArray<I-1>::toTuple(t, a);
   }
};


template <typename Head, typename... Tail>
struct MakeTuple;

template <typename Head>
struct MakeTuple<Head>
{
   static std::tuple<Head> fromArray(const Double_t* a) {
      std::tuple<Head> h(a[0]);
      return h;
   }
};

template <typename Head, typename... Tail>
struct MakeTuple
{
   static std::tuple<Head, Tail...> fromArray(const Double_t* a)
   {
      std::tuple<Head> h(a[0]);
      return std::tuple_cat(h, MakeTuple<Tail...>::fromArray(a + 1));
   }
};

template <typename FuncType>
class LikelihoodWrapper;

template <typename R, typename... Obs, typename... Nuis>
class LikelihoodWrapper<std::function<R(std::tuple<Obs...>, std::tuple<Nuis...>)>> : public ROOT::Math::IBaseFunctionMultiDim {
public:
   
   // TODO constness
   LikelihoodWrapper(Likelihood<std::function<R(std::tuple<Obs...>, std::tuple<Nuis...>)>> &l) : fLikelihood(l) {}
   UInt_t NDim() const { return sizeof...(Nuis); }
   LikelihoodWrapper* Clone() const { return NULL; };

private: 
   
   Double_t DoEval(const Double_t* x) const {
      return fLikelihood.Evaluate(MakeTuple<Nuis...>::fromArray(x));
   }

   
   Likelihood<std::function<R(std::tuple<Obs...>, std::tuple<Nuis...>)>> &fLikelihood;


};


#endif


