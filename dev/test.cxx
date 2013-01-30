#include <functional>
#include <cmath>
#include <iostream>

int main()
{
   std::function<double(int)> f;
   f = [&f] (int n)->double { return n > 0 ? n * f(n - 1) : 1.0; };
   auto g = [] (double x, double m, double s) { double r = (x - m) / s; return std::exp(-(r*r)) / (s * 2 * M_PI); };
   auto p = [&f] (int x, double m) { return std::exp(-m) * std::pow(m, x) / f(x); }; 
   auto a = [] (double x, double y) { return x + y; };

   auto ll = [&g, &p] (double x, double y) { return g(x, y, y) * p(x, y); };

   return 0;
}

