#include "Likelihood.h"
#include "LikelihoodWrapper.h"
#include "Computable.h"
#include "Math/Functor.h"
#include "Minuit2/Minuit2Minimizer.h"

template <typename F>
void probe_result_of (F f)
{
   typedef typename std::result_of<F()>::type res_type;
   std::cout << "result type is " << typeid(res_type).name() << std::endl;
}

template <typename F>
struct ToFunc
{
};

Double_t RawFunc(const Double_t* x) {
   return gGaussian(2.0, x[0], 1.0) * gPoisson(1, x[0]) +
          gGaussian(0.0, x[0], 1.0) * gPoisson(3, x[0]) +
         gGaussian(-1.0, x[0], 1.0) * gPoisson(0, x[0]);
}

int main()
{
   

   auto t1 = std::make_tuple(2.0, 1);
   auto t2 = std::make_tuple(0.0, 3);
   auto t3 = std::make_tuple(-1.0, 0);

   std::vector<std::tuple<double, UInt_t>> data = {t1, t2, t3};
/*   
   Likelihood<decltype(newFunc)> ll(newFunc, data); 
   std::cout << ll.Evaluate(0.1) << std::endl;

   LikelihoodWrapper<decltype(newFunc)> lw(ll);

   Double_t param[1] = {0.1};
   Double_t step[1] = {1e-9};
   std::cout << lw(param) << std::endl;

   ROOT::Minuit2::Minuit2Minimizer m1, m2;

   m2.SetFunction(lw);
   m2.SetVariable(0, "x", param[0], step[0]); 

   m2.Minimize();
   
   const double* xs = m2.X();

   std::cout << "Minimum: f(" << xs[0] << "): " << m2.MinValue() << std::endl;

   ROOT::Math::Functor rf(&RawFunc, 1);
   m1.SetFunction(rf);
   m1.SetVariable(0, "x", param[0], step[0]);

   m1.Minimize();

   xs = m1.X();
   std::cout << "Minimum: f(" << xs[0] << "): " << m1.MinValue() << std::endl;
*/
/*   
   std::vector<double> v1 = {2.0, 5.0, 3.0};
   std::vector<double> v2 = {1.0, 4.0, 6.0};
   
   auto tup = std::make_tuple(v1, v2);

//   std::cout << ll.Evaluate(tup) << std::endl;

   std::vector<std::tuple<double, double>> v = {
      std::make_tuple(2.0, 1.0),
      std::make_tuple(1.0, 3.0),
      std::make_tuple(4.0, 5.0),
   };

   std::cout << ll.Evaluate(v) << std::endl;

   ROOT::Minuit2::Minuit2Minimizer m2("minimizer");
*/   

//   Likelihood<decltype(func)> like(func);
//   Likelihood<decltype(func)> like(func);

//   std::cout << like.Evaluate(1.0, 1.0) << std::endl; 
//   Likelihood<decltype(ll), decltype(fLL)::result_type, decltype(fLL)::argument_type> like(fLL); 
//   Likelihood<decltype(ll), decltype(ll)::result_type, decltype(ll)::argument_type> l(ll); 
//   LikelihoodModel<4> ll(entities);
//   l.Print();
}


