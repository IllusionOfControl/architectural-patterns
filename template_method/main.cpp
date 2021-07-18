#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class AbstractClass {
public:
    void TemplateMethod() {
        // Порядок вызовов не важен, только для конкретной предметной области
        BaseOperation1();
        BaseOperation2();
        RequiredOperation1();
        RequiredOperation2();
        Hook1();
        Hook2();
    }

protected:
    void BaseOperation1() const {
        std::cout << "AbstractClass: BaseOperation1()" << std::endl;
    }
    void BaseOperation2() const {
        std::cout << "AbstractClass: BaseOperation1()" << std::endl;
    }

    virtual void RequiredOperation1() const = 0;
    virtual void RequiredOperation2() const = 0;

    virtual void Hook1() const {}
    virtual void Hook2() const {}
};


class ConcreteClassA : public AbstractClass {
protected:
    void RequiredOperation1() const {
        std::cout << "ConcreteClassA: Operation1()" << std::endl;
    }
    void RequiredOperation2() const {
        std::cout << "ConcreteClassA: Operation2()" << std::endl;
    }
};


class ConcreteClassB : public AbstractClass {
protected:
    void RequiredOperation1() const {
        std::cout << "ConcreteClassB: Operation1()" << std::endl;
    }
    void RequiredOperation2() const {
        std::cout << "ConcreteClassB: Operation2()" << std::endl;
    }
    void Hook1() const {
        std::cout << "ConcreteClassB: Hook1()" << std::endl;
    }
};


void ClientCode(AbstractClass* object) {
    object->TemplateMethod();
}

int main() {
    ConcreteClassA* concreteClassA = new ConcreteClassA;
    ClientCode(concreteClassA);
    std::cout << std::endl;
    ConcreteClassB* concreteClassB = new ConcreteClassB;
    ClientCode(concreteClassB);
    return 0;
}