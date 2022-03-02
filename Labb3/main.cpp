#include <iostream>

template <class myType>
myType GetPOW (myType a, int b) {
 
    if(b>1){
        return a * GetPOW(a, b-1);
    }
    else if(b==1){
        return a;
    }
    else if(b==0){
        return 1;
    }
    else{
        std::cerr << "Bad exponent";
        return 0;
    }
}

int main(){

    std::cout << GetPOW(2.3,5) << std::endl;

    return 0;
}