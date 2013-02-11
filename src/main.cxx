#include "Likelihood.h"
#include "LikelihoodWrapper.h"
#include "Computable.h"
#include "Math/Functor.h"
#include "Fit/Fitter.h"
#include "Fit/UnBinData.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "TVirtualFitter.h"

#include "RooAbsPdf.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooRandom.h"
#include "RooRealVar.h"

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
   const std::size_t ENTRIES = 3;


   RooWorkspace w("w");

   w.factory("Exponential:bkg_pdf(x[0,10], a[-0.5, -1000, 0])");
   w.factory("Gaussian:sig_pdf(x, mass[2], sigma[0.4])");
   w.factory("SUM:model(nsig[30, 0, 1000] * sig_pdf, nbkg[1000, 0, 10000000] * bkg_pdf)"); // for extended model
   RooRandom::randomGenerator()->SetSeed(111);
   RooDataSet* rooData = w.pdf("model")->generate(*w.var("x"), ENTRIES);
   w.import(*rooData);

   std::vector<std::array<Double_t, 1>> data;
   ROOT::Fit::UnBinData fitData(ENTRIES, 1, kFALSE);
   for (std::size_t i = 0; i < ENTRIES; ++i) {
      const RooArgSet* set = rooData->get(i);
      data.push_back({{set->getRealValue("x")}});
      fitData.Add(set->getRealValue("x"));
   }
   

   Double_t x[3] = { 2.0, 5.0, 1.0 };

//   std::array<Double_t, 3> a = make<Double_t, ENTRIES>(x);
//   std::cout << typeid(a).name() << std::endl;
//   test<double> t;  
//   CArray<Double_t, 3>::genArray(a, x);
//   make<Int_t, 3, 2.0>(x);

   auto stdFunc = make_function(modelFunc);

//   LikelihoodWrapper<decltype(stdFunc)> lw(stdFunc, data);

//   ROOT::Fit::Fitter fitter;
//   fitter.LikelihoodFit<ROOT::Fit::UnBinData, ROOT::Math::IBaseFunctionMultiDim>(fitData, lw, kFALSE);

/*
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


