#include <iostream>
#include <iomanip>
#include <limits>
#include <boost/function.hpp>
#include <fstream>

class IDifferentiate
{
    virtual double operator() (
        const double x,
        const boost::function<double(double)> f,
        const double dx) const = 0;
};

class ForwardDifferentiate : public IDifferentiate
{
public:
    double operator() (
        const double x,
        const boost::function<double(double)> f,
        const double dx) const
    {
        return (f(x + dx) - f(x)) / dx;
    }
};

class CenterDifferentiate : public IDifferentiate
{
public:
    double operator() (
        const double x,
        const boost::function<double(double)> f,
        const double dx) const
    {
        return (f(x + dx) - f(x - dx)) / (2.0 * dx);
    }
};

class Function
{
public:
    virtual double Function::operator()(const double x) const = 0;
};

class Sin : public Function
{
public:
    double Sin::operator()(const double x) const
    {
        return std::sin(x);
    }
    
};

int main()
{
    const unsigned N = 20;
    const double x = 0.5;
    double dx = std::numeric_limits<double>::epsilon();
    const Sin function;
    boost::function < double(double)> f(function);
    std::ofstream ofs("sin.txt");
    const double trueValue = std::cos(x);
  
    ForwardDifferentiate fdifferentiate;
    std::cout << "----- Forward Differentiate -----" << std::endl;
    ofs << "----- Forward Differentiate -----" << std::endl;
    for (unsigned i = 1; i < N; ++i)
    {
        std::cout << dx << " " << std::setprecision(8) 
            << trueValue - fdifferentiate(x, function, dx) << std::endl;
        ofs << dx << " " << std::setprecision(8)
            << trueValue - fdifferentiate(x, function, dx) << std::endl;

        dx *= 10;
    }

    CenterDifferentiate cdifferentiate;
    dx = std::numeric_limits<double>::epsilon();
    std::cout << "----- Center Differentiate -----" << std::endl;
    ofs << "----- Center Differentiate -----" << std::endl;
    for (unsigned i = 1; i < N; ++i)
    {
        std::cout << dx << " " << std::setprecision(8)
            << trueValue - cdifferentiate(x, function, dx) << std::endl;
        ofs << dx << " " << std::setprecision(8)
            << trueValue - cdifferentiate(x, function, dx) << std::endl;

        dx *= 10;
    }
    getchar();
}