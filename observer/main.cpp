#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <list>


class IObserver {
public:
    virtual void Update() = 0;
};


class ISubject {
public:
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};


class Store : public ISubject {
public:
    void Attach(IObserver* observer) override {
        _observers.push_back(observer);
    }
    void Detach(IObserver* observer) override {
        _observers.remove(observer);
    }
    void Notify() override {
        for (IObserver* observer : _observers) {
            observer->Update();
        }
    }

    void PriceUpdate() {        
        Notify();
    }

private:
    std::list<IObserver*> _observers;
};


class �ustomer : public IObserver {
public:
    �ustomer(ISubject* subject) : _subject(subject) {
        this->_subject->Attach(this);
    }

    void Update() override {
        std::cout << "Customer received a price update.\n";
    }

private:
    ISubject* _subject;
};

void ClientCode() {
    Store* store = new Store;
    �ustomer* customer1 = new �ustomer(store);
    �ustomer* customer2 = new �ustomer(store);
    �ustomer* customer3;

    store->PriceUpdate();
    std::cout << std::endl;

    store->Detach(customer2);
    store->PriceUpdate();
    std::cout << std::endl;

    customer3 = new �ustomer(store);
    store->Attach(customer2);
    store->PriceUpdate();
    std::cout << std::endl;
}

int main() {
    ClientCode();
    return 0;
}