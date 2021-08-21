#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <map>


class Subsystem1 {
public:
    std::string Operation_1() {
        return "Subsystem1: Ready!";
    }

    std::string Operation_X() {
        return "Subsystem1: Go!";
    }
};


class Subsystem2 {
public:
    std::string Operation_1() const {
        return "Subsystem2: Get ready!";
    }

    std::string Operation_Y() const {
        return "Subsystem2: Fire!";
    }
};


class Facade {
protected:
    Subsystem1* _subsystem1;
    Subsystem2* _subsystem2;
public:
    Facade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr) {
        this->_subsystem1 = subsystem1 ? subsystem1 : new Subsystem1;
        this->_subsystem2 = subsystem2 ? subsystem2 : new Subsystem2;
    }
    
    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->_subsystem1->Operation_1() + "\n";
        result += this->_subsystem2->Operation_1() + "\n";
        result += this->_subsystem1->Operation_X() + "\n";
        result += this->_subsystem2->Operation_Y() + "\n";
        return result;
    }
};

void ClientCode(Facade* facade) {
    std::cout << facade->Operation();
}

int main() {
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;
    Facade* facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    return 0;
}