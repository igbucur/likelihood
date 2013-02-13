#ifndef ROOSTATS_LikelihoodWrapper
#define ROOSTATS_LikelihoodWrapper

#include "Likelihood.h"
#include "Math/IParamFunction.h"

template <typename CType, std::size_t I>
struct CArray;

template <typename CType>
struct CArray<CType, 0>
{
   template <typename... Ts>
   static void genTuple(std::tuple<Ts...>& t, const CType* cArr) {}

   template <std::size_t J>
   static void genArray(std::array<CType, J> a, const CType* cArr) {}
};

template <typename CType, std::size_t I>
struct CArray
{
   template <typename... Ts>
   static void genTuple(std::tuple<Ts...>& t, const CType* cArr)
   {
      std::get<I-1>(t) = cArr[I-1];
      CArray<CType, I-1>::genTuple(t, cArr);
   }

   template <std::size_t J>
   static void genArray(std::array<CType, J>& a, const CType* cArr) 
   {
      a[I-1] = cArr[I-1];
      CArray<CType, I-1>::genArray(a, cArr);
   }
/*
   static const std::array<CType, I>&& toArray(const CType* cArr)
   {
      std::array<CType, I> a;
      CArray<CType, I>::genArray<I>(a, cArr);
      return a;
   }*/
};

/*
// Compile-time C array to std::array (only works for integers)
template <typename U>
constexpr U get(std::size_t i, U* cArr) { return cArr[i]; }

template <typename T, std::size_t N, T... Vals>
constexpr 
typename std::enable_if<N == sizeof...(Vals), std::array<T, N>>::type
make(T* cArr) { return std::array<T, N>{{Vals...}}; };
template <typename T, std::size_t N, T... Vals>
constexpr
typename std::enable_if<N != sizeof...(Vals), std::array<T, N>>::type
make(T* cArr) { return make<T, N, Vals..., get<T>(sizeof...(Vals), cArr)>(cArr); }
*/

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

template <typename R, typename TO, std::size_t NO, typename TP, std::size_t NP>
class LikelihoodWrapper<std::function<R(std::array<TO, NO>, std::array<TP, NP>)>> : public Likelihood<std::function<R(std::array<TO, NO>, std::array<TP, NP>)>>, public ROOT::Math::IBaseFunctionMultiDim {
public:
   
   LikelihoodWrapper(std::function<R(std::array<TO, NO>, std::array<TP, NP>)>& model, std::vector<std::array<TO, NO>>& data) : Likelihood<std::function<R(std::array<TO, NO>, std::array<TP, NP>)>>(model, data) {}

   LikelihoodWrapper(const LikelihoodWrapper<std::function<R(std::array<TO, NO>, std::array<TP, NP>)>>& rhs) : 
      Likelihood<std::function<R(std::array<TO, NO>, std::array<TP, NP>)>>(rhs)
   { }

   UInt_t NDim() const { return NP; }
   LikelihoodWrapper* Clone() const { return new LikelihoodWrapper<std::function<R(std::array<TO, NO>, std::array<TP, NP>)>>(*this); };

private:
   Double_t DoEval(const Double_t* x) const {
      //SetValues(x);
      std::array<TP, NP> nuisanceParameters;
      std::copy(x, x + NP, nuisanceParameters.begin());
      return -this->Evaluate(nuisanceParameters); 
   }
};


#endif


