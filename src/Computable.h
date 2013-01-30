#include <functional>

#include "Rtypes.h"

#ifndef ROOSTATS_Computable
#define ROOSTATS_Computable

// Basic computable entity (variable, function, PDF, etc...)
//template <typename R, typename... Args>
class Computable {

   enum Type { Functor, Variable };
private:
   static UInt_t fgIdCounter;
   UInt_t fId;
   Type fType;
   Double_t fValue;
   Computable *fParent;

//   std::vector<Computable<R, Args...>> fChildren;
//   std::function<R(Args...)> fCompute;
public:
   Computable() {
      fId = fgIdCounter++;
   }

   UInt_t GetId() { return fId; }
   Type GetType() { return fType; }

   Double_t Evaluate() {
      return 1.0;
   }
//
//   R Evaluate(Args&&... args) {
//      return fCompute(args...);
//   }
};


//template <typename R, typename... Args>

#endif // ROOSTATS_Computable


