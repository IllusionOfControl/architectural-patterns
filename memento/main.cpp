#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <array>
#include <vector>


class Memento {
public:
    virtual std::string GetTimestamp() = 0;
    virtual std::string GetState() = 0;
};


class ConcreteMemento : public Memento {
private:
    std::string _timestamp;
    std::string _state;

public:
    ConcreteMemento(std::string state) : _state(state) {
        this->_state = state;
        std::time_t timestamp = std::time(0);
        this->_timestamp = std::ctime(&timestamp);
    }

    std::string GetTimestamp() {
        return this->_timestamp;
    }

    std::string GetState() {
        return this->_state;
    }
};


class Originator {
private:
    std::string _state;

    std::string GenerateRandomString(int length = 10) {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        std::string random_string;
        for (int i = 0; i < length; i++) {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(std::string state) : _state(state) {
        std::cout << "Originator: my initial state is: " << this->_state << std::endl;
    }

    void DoSomething() {
        this->_state = this->GenerateRandomString(30);
        std::cout << "Originator: my state has changed to: " << this->_state << std::endl;
    }

    Memento* Save() {
        return new ConcreteMemento(this->_state);
    }

    void Restore(Memento* memento) {
        this->_state = memento->GetState();
        std::cout << "Originator: My state has restored to: " << this->_state << std::endl;
    }
};


class Caretaker {
private:
    std::vector<Memento*> _mementos;
    Originator* _originator;

public:
    Caretaker(Originator* originator) : _originator(originator) {
        this->_originator = originator;
    }

    void Backup() {
        std::cout << "Caretaker: Saving Originator's state..." << std::endl;
        this->_mementos.push_back(this->_originator->Save());
    }

    void Undo() {
        if (!this->_mementos.size()) {
            return;
        }
        Memento* memento = this->_mementos.back();
        this->_mementos.pop_back();
        std::cout << "Caretaker: Restoring state..." << std::endl;
        
        this->_originator->Restore(memento);
        this->Undo();
    }

    void ShowHistory() const {
        std::cout << "Caretaker: Here's the list of mementos:" << std::endl;
        for (Memento* memento : this->_mementos) {
            std::cout << memento->GetTimestamp();
        }
        std::cout << std::endl;
    }
};


void ClientCode() {
    Originator* originator = new Originator("Waba-waba-dab-dab");
    Caretaker* caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    std::cout << std::endl;
    caretaker->ShowHistory();
    std::cout << "Client: Now, let's rollback!" << std::endl;
    caretaker->Undo();
    std::cout << "Client: Once more!" << std::endl;
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
    return 0;
}