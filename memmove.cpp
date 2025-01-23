#include <iostream>
#include <cstddef>
#include <cstring>


void* memmove2(void* dst, void* src, size_t num){

    char* d = (char*) dst;
    const char* s = (const char*) src;


     if((d+num < s) || (d > s + num)){

        for(size_t i = 0; i < num; ++i){
            d[i] = s[i];
        }
     }
     else {

        for(size_t i = num; i > 0; i--){
            d[i-1] = s[i-1];
        }
     }

     return dst;
}

int main(){

    char src[] = "Hello memcpy!";
    char dst[20];

    memmove2(dst, src, strlen(src)+1);

    std::cout << "Source: " << src <<  "\n";
    std::cout<<"Destination: "<<dst<<"\n";

    char data[] = "Hello, memmove!";
    memmove2(data + 7, data, 5); // Move "Hello" to "memmove"
    std::cout << "Overlapping Test: " << data << "\n";

    return 0;


}