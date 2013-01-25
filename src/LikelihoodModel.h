#ifndef ROOSTATS_LikelihoodModel
#define ROOSTATS_LikelihoodModel

#include <array>
#include <iostream>
#include <map>
#include <tuple>
#include <set>
#include "Computable.h"
#include "Value.h"

template <std::size_t N>
class LikelihoodModel
{
private:
   Computable fTopLevelEntity;
   std::set<Computable> fEntities;
   std::set<UInt_t> fIds; 
//   Bool_t fDepend[sizeof...(Types)][sizeof...(Types)];
//   Bool_t fDepends[N][N];
   std::map<UInt_t, std::vector<UInt_t>> fDependencies;
public:
   Double_t ComputeLikelihood() {

   }

   LikelihoodModel(std::set<Computable>&& entities) : fEntities(entities) { }

   void AddDependency(UInt_t parent, std::vector<UInt_t> children) { 
      if (fIds.count(parent) == 0) {
         std::cout << "Dependency parent does not exist in model ";
         return;
      }
      fDependencies.insert(std::pair<UInt_t, std::vector<UInt_t>>(parent, children));
      
//      if (fDepends[child][parent] == kTRUE) {
//         std::cout << "Error: Circular dependency " << std::endl;
//         return;
//      }
//      fDepends[parent][child] = kTRUE; 
   }
   void AddEntity(Computable c) {
      fEntities.insert(c);
   }

   
};

#endif // ROOSTATS_LikelihoodModel


