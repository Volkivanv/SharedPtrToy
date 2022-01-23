#include <iostream>
#include <string>

class Toy{
private:
    std::string name;
public:
    Toy(std::string inName):name(inName){};
    Toy(): Toy("SomeToy"){};
    Toy(const Toy& other){
        name = other.name;
    }
};

class SharedPtrToy{
private:
    Toy* toy;
    int* numPtr;
public:
    SharedPtrToy(std::string inToyName){
        toy = new Toy(inToyName);
        numPtr= new int ;
        *numPtr = 1;
    }
    SharedPtrToy(): SharedPtrToy("someToy"){};

    SharedPtrToy(Toy& inToy){
        toy = new Toy(inToy);
        numPtr= new int ;
        *numPtr = 1;
    }
    SharedPtrToy(const SharedPtrToy& other){
        toy = other.toy;
        numPtr = other.numPtr;
        ++*numPtr;

    }

    SharedPtrToy& operator = (const SharedPtrToy& other){
        if (this == &other)
            return *this;
        if(toy != nullptr){
            --*numPtr;
            //std::cout<<*numPtr<<std::endl;
            if(*numPtr == 0){
                delete numPtr;
                delete toy;
            }

        }

        toy = other.toy;
        numPtr = other.numPtr;
        ++*numPtr;


        return *this;
    }

    ~SharedPtrToy(){
        if(toy != nullptr){
            --*numPtr;
            if(*numPtr == 0){
                delete numPtr;
                delete toy;
            }
        }
    }
};

Toy makeSharedToy(std::string inName){
    return Toy(inName);
}

Toy makeSharedToy(Toy& inToy){
    return Toy(inToy);

}



int main() {
    Toy a = makeSharedToy("Ball");
    Toy b = makeSharedToy(a);


    auto sA = new SharedPtrToy("Bone");
    auto sB = new SharedPtrToy(*sA);
    auto sC = new SharedPtrToy(a);
    auto sD = new SharedPtrToy(*sB);
     *sD = *sC;
    SharedPtrToy sE(*sC);

    delete sA;
    delete sB;
    delete sC;
    delete sD;
  //  delete sD;

  //  SharedPtrToy sC = *sB;
  //  SharedPtrToy sD(sC);





    return 0;
}
