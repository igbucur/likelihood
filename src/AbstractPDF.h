#ifndef ROOSTATS_AbstractPDF
#define ROOSTATS_AbstractPDF

#include "Model.h"
#include "TRandom.h"

template <typename Functor>
class AbstractPDF;

template <typename R, typename... Args>
class AbstractPDF <std::function<R(Args...)>> {
public:
   virtual ~AbstractPDF() {};


   AbstractPDF(std::function<R(Args...)>& PDF, std::function<R(Double_t)>& invCDF) :
      fPDF(PDF), fInvCDF(invCDF), fRandom(1234)
   {}

   Double_t EvaluatePDF(Args... args) const { return fPDF(args...); }
   Double_t RandomEvent() const { return fInvCDF(this->fRandom.Uniform(1)); } 
   //   virtual Double_t EvaluateCDF() const = 0;
   //virtual Double_t Integrate() const = 0; // need to pass integration variable somehow
//   virtual Double_t GenerateEvent() = 0;

private:
   std::function<R(Args...)>& fPDF;
   std::function<R(Args...)>& fInvCDF;
   const TRandom fRandom;
};



#endif // ROOSTATS_AbstractPDF


