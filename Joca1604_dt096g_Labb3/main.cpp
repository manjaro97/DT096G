#include <iostream>

//cd "c:\Users\j_c_k\Desktop\DT096G\Labb3\" ; if ($?) { g++ main.cpp -o main } ; if ($?) { .\main }

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
        return 1/nextExp(bas);
    }
};

template <>
struct POW<0>
{
    double operator()(double bas){
        return 1;
    }
};

int main(){

    double bas = 2;

    POW<-5> c;
    std::cout << "Result = " << c(bas) << std::endl;

    return 0;
}