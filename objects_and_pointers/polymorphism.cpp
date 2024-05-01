#include <iostream>

class MusInstruments {
public:
    MusInstruments() {
        std::cout << "MusInstruments ctor() start \n";
    }
    virtual ~MusInstruments() {
        std::cout << "~MusInstruments DESTRUCTOR() \n";
    }

    virtual void makeSound() {
        std::cout << "MusInstruments makeSound() \n";
    }
};

class StringsInstruments: public MusInstruments {
public:
    StringsInstruments() : MusInstruments() {
        std::cout << "StringsInstruments ctor() start \n";
    }
    virtual ~StringsInstruments() {
        std::cout << "~StringsInstruments DESTRUCTOR() \n";
    }

    void makeSound() override {
        std::cout << "StringsInstruments makeSound() \n";
    }
};

class Violin : public StringsInstruments {
public:
    Violin() : StringsInstruments() {
        std::cout << "Violin ctor() start \n";
    }
    virtual ~Violin() {
        std::cout << "~Violin DESTRUCTOR() \n";
    }

    void makeSound() override {
        std::cout << "Violin makeSound() \n";
    }
};


int main(int, char**){
    std::cout << "Hello, from objects_and_pointers!\n";

    {
        std::cout << " --- Polymorphism *NO* pointers scope ------ \n";
        MusInstruments mi1;
        std::cout << "This is mi1 sound: ";
        mi1.makeSound();
        Violin v1;
        std::cout << "This is v1 sound: ";
        v1.makeSound();
        mi1 = v1;
        std::cout << "This is mi1 (polymorph) sound: ";
        mi1.makeSound();
    }

    {
        std::cout << " --- Polymorphism pointers scope ------ \n";
        MusInstruments *mi1 = new MusInstruments;
        std::cout << "This is *mi1 sound: ";
        mi1->makeSound();
        Violin *v1 = new Violin;
        std::cout << "This is *v1 sound: ";
        v1->makeSound();
        mi1 = v1;
        std::cout << "This is *mi1 (polymorph) sound: ";
        mi1->makeSound();
    }

    {
        std::cout << " --- Polymorphism references scope ------ \n";
        MusInstruments mi1;
        MusInstruments &mi2 = mi1;
        std::cout << "This is &mi2 sound: ";
        mi2.makeSound();
        Violin v1;
        Violin &v2 = v1;
        std::cout << "This is &v2 sound: ";
        v2.makeSound();
        mi2 = v2;
        std::cout << "This is &mi2 (polymorph) sound: ";
        mi2.makeSound();
    }

    std::cout << " ----- thats all folks ----- \n";
}
