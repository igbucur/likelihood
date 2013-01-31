#include "Likelihood.h"
#include "Computable.h"


int main()
{
//   Computable<double, double, double> c(2.0, 3.0);
//   LikelihoodModel<
//      std::function<double(
//         std::function<double(double, double)>, 
//         std::function<double(double, double)>
//      )>
//   > l;
/*
   Computable c1, c2, c3;

   std::vector<Computable> entities;
   entities.push_back(c1);   
   entities.push_back(c2);   
   entities.push_back(c3);   
*/
   Likelihood<decltype(newFunc)> ll(newFunc, std::tuple<double>(2.0)); 
   std::cout << ll.Evaluate(2.0, 1.0, 2.0) + ll.Evaluate(1.0, 3.0) +  ll.Evaluate(4.0, 5.0) << std::endl;   
   
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

//   Likelihood<decltype(func)> like(func);
//   Likelihood<decltype(func)> like(func);

//   std::cout << like.Evaluate(1.0, 1.0) << std::endl; 
//   Likelihood<decltype(ll), decltype(fLL)::result_type, decltype(fLL)::argument_type> like(fLL); 
//   Likelihood<decltype(ll), decltype(ll)::result_type, decltype(ll)::argument_type> l(ll); 
//   LikelihoodModel<4> ll(entities);
//   l.Print();
}


