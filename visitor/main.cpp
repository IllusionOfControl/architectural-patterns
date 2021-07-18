#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <array>


class Bank;
class Factory;
class Townhouse;


class Visitor {
public:
    virtual void VisitBank(Bank* element) = 0;
    virtual void VisitFactory(Factory* element) = 0;
    virtual void VisitTownhouse(Townhouse* element) = 0;
};


class Building {
public:
    virtual void Accept(Visitor* visitor) = 0;
};


class Bank : public Building {
public:
    void Accept(Visitor* visitor) {
        visitor->VisitBank(this);
    }

    std::string SpecificMethodOfFactory() {
        return "Bank";
    }
};


class Factory : public Building {
public:
    void Accept(Visitor* visitor) {
        visitor->VisitFactory(this);
    }

    std::string ExclusiveMethodOfFactory() {
        return "Factory";
    }
};


class Townhouse : public Building {
public:
    void Accept(Visitor* visitor) {
        visitor->VisitTownhouse(this);
    }

    std::string SpecialMethodOfTownhouse() {
        return "Townhouse";
    }
};


class InsuranceAgent : public Visitor {
public:
    void VisitBank(Bank* bank) {
        std::cout << "InsuranceAgent: nothing for Bank" << std::endl;
    }
    void VisitFactory(Factory* factory) {
        std::cout << "InsuranceAgent: " << factory->ExclusiveMethodOfFactory() << std::endl;
    }
    void VisitTownhouse(Townhouse* townhouse) {
        std::cout << "InsuranceAgent: " << townhouse->SpecialMethodOfTownhouse() << std::endl;
    }
};


class Citizen : public Visitor {
public:
    void VisitBank(Bank* bank) {
        std::cout << "Citizen: " << bank->SpecificMethodOfFactory() << std::endl;
    }
    void VisitFactory(Factory* factory) {
        std::cout << "Citizen: nothing for Factory" << std::endl;
    }
    void VisitTownhouse(Townhouse* townhouse) {
        std::cout << "Citizen: " << townhouse->SpecialMethodOfTownhouse() << std::endl;
    }
};


void ClientCode(std::array<Building*, 3> buildings, Visitor* visitor) {
    for (auto comp : buildings) {
        comp->Accept(visitor);
    }
}

int main() {
    std::array<Building*, 3> buildings = { new Bank, new Factory, new Townhouse };
    InsuranceAgent* agent = new InsuranceAgent;
    ClientCode(buildings, agent);
    std::cout << std::endl;
    Citizen* citizen = new Citizen;
    ClientCode(buildings, citizen);

    return 0;
}