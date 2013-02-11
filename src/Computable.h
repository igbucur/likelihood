#include <functional>

#include "Rtypes.h"

#ifndef ROOSTATS_Computable
#define ROOSTATS_Computable

// Basic computable entity (variable, function, PDF, etc...)
//template <typename R, typename... Args>
template <typename T>
class Computable {

   enum Type { Functor, Variable };
private:
   static UInt_t fgIdCounter;
   UInt_t fId;
   Type fType;
   T fValue;
   Computable *fParent;

//   std::vector<Computable<R, Args...>> fChildren;
//   std::function<R(Args...)> fCompute;
public:
   Computable(T min, T max, T value) :
      fMin(min),
      fMax(max),
      fValue(value) 
      // must solve checks
   {
      fId = fgIdCounter++;
   }

   UInt_t GetId() { return fId; }
   Type GetType() { return fType; }

   Double_t Evaluate() {
      return fValue;
   }
//
//   R Evaluate(Args&&... args) {
//      return fCompute(args...);
//   }
   const T fMin;
   const T fMax;
};


//template <typename R, typename... Args>

#endif // ROOSTATS_Computable


