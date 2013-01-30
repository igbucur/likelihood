#ifndef ROOSTATS_Gaussian
#define ROOSTATS_Gaussian

#include "Function.h"
#include <cmath>

class Gaussian : public Function {

private:
   std::function<Double_t(Double_t, Double_t, Double_t)> fFunctor = 
   [] (Double_t x, Double_t m, Double_t s) { Double_t r = (x - m) / s; return exp(-(r*r)) / s; }; 

public:
   Double_t Evaluate(std::initializer_list<Double_t> args) {
      return 0.0;
   }
};

#endif // ROOSTATS_Gaussian

