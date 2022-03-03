#include <iostream>

template <int exp, class Enable = void>
struct POW
{
    double operator()(double bas){
        POW<exp - 1> nextExp;
        return nextExp(bas) * bas;
    }
};

template <int exp>
struct POW<exp, typename std::enable_if_t<exp < 0> >
{
    double operator()(double bas){
        POW<-exp> nextExp;
        //return 1/nextExp(bas);
        return 3;
    }
};

template <>
struct POW<0, bool>
{
    double operator()(double bas){
        return 1;
    }
};

int main(){

    double bas = 20;

    POW<2> c;
    std::cout << "20^5 = " << c(bas) << std::endl;

    return 0;
}