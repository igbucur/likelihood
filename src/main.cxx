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

   Computable c1, c2, c3;

   std::vector<Computable> entities;
   entities.push_back(c1);   
   entities.push_back(c2);   
   entities.push_back(c3);   

   Likelihood<function_traits<decltype(func)>::result_type, function_traits<decltype(func)>::args_type> like(func);

   std::cout << like.Evaluate(1.0, 1.0) << std::endl; 
//   Likelihood<decltype(ll), decltype(fLL)::result_type, decltype(fLL)::argument_type> like(fLL); 
//   Likelihood<decltype(ll), decltype(ll)::result_type, decltype(ll)::argument_type> l(ll); 
//   LikelihoodModel<4> ll(entities);
//   l.Print();
}


