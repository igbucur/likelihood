#include "Rtypes.h"

#ifndef ROOSTATS_VariableSet
#define ROOSTATS_VariableSet

class VariableSet {

//   enum Type { Continuous, Categorical };
private:
   static UInt_t fgIdCounter;
   const UInt_t fSize;
   std::vector<UInt_t> fVariables;
public:
   VariableSet(Int_t size) : fSize(size), fVariables(fSize) {
      for (UInt_t i = 0; i < fSize; ++i, ++fgIdCounter) {
         fVariables[i] = fgIdCounter;
      }
   }
   std::vector<UInt_t> IdList() { return fVariables; }
   
};




#endif // ROOSTATS_VariableSet


