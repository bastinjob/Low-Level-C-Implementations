#include <cstddef> // for size_t
#include <iostream>
#include <cstring>

void* memcpy2(void* dst, const void* src, size_t num){

    //covert void* to char* for bytelevel operations

    /*
    char* d = (char*) dst;
    const char* s = (const char*) src;


    //copy byte by byte

    for(size_t i = 0; i < num ; i++){
        d[i] = s[i];
    }

    return dst;
    */

   //optimize by vectorization
    char* d = (char*) dst;
    const char* s = (const char*) src;

    while (num >= 4){
        *(int*)d = *(const int*) s;
        d += 4;
        s+=4;
        num -= 4;
    }

    //remaining characters 1 by 1

    while (num > 0 ){
        *d++ = *s++;
        --num;
    }

    return dst;


}


int main(){

    char src[] = "Hello memcpy!";
    char dst[20];

    memcpy2(dst, src, strlen(src)+1);

    std::cout << "Source: " << src <<  "\n";
    std::cout<<"Destination: "<<dst<<"\n";

    return 0;


}