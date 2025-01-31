/* Implementing a smart pointer like unique_ptr*/
#include <iostream>
template <typename T>

class uniquePtr{
private:
    T* ptr;

public:
    explicit uniquePtr(T* p = nullptr){
        ptr = p;
    }

    ~uniquePtr(){
        delete ptr;
    }

    uniquePtr(const uniquePtr&) = delete;
    uniquePtr& operator=(const uniquePtr&) = delete;

    uniquePtr& operator=(uniquePtr&& other) noexcept {
        if(this != other){
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    //overload dereference
    T& operator*() const{
        return *ptr;
    }

    T* operator->() const{
        return ptr;
    }

    T* release(){
        T* temp = ptr;
        ptr= nullptr;
        return temp;
    }
    T* get() const{
        return ptr;
    }
};


struct Test{
    int  x;
    void show(){std::cout<<"Value: "<<x<<std::endl;}
};

int main(){

   uniquePtr<Test> up1(new Test{10});
   up1->show();

   /*uniquePtr<Test> up2 = std::move(up1);

   if(!up1.get()) {
    std::cout<<"up1 is now empty!"<<std::endl;
   }

   up2->show();
    */
    return 0;
}