#include <algorithm>
#include <iostream>
#include <list>
#include <string>


class Device {
protected:
    Device* _parent;
    unsigned int _id;

public:
    Device(unsigned int id) : _id(id) {}
    virtual ~Device() {}

    void SetParent(Device* parent) {
        this->_parent = parent;
    }
    Device* GetParent() const {
        return this->_parent;
    }

    unsigned int GetId() const {
        return this->_id;
    }

    virtual void Add(Device* component) {}
    virtual void Remove(Device* component) {}

    virtual bool IsComposite() const {
        return false;
    }

    virtual std::string GetName() = 0;
    virtual std::string Operation() = 0;
};


class PersonalComputer : public Device {
public:
    PersonalComputer(unsigned int id) : Device(id) {}

    std::string GetName() override {
        return "Personal Computer [" + std::to_string(this->_id) + "]";
    }
    
    std::string Operation() override {
        return GetName();
    }
};


class CompositeDevice : public Device {
protected:
    std::list<Device*> _children_list;

public:
    CompositeDevice(unsigned int id) : Device(id) {}

    void Add(Device* component) override {
        this->_children_list.push_back(component);
        component->SetParent(this);
    }

    void Remove(Device* component) override {
        _children_list.remove(component);
        component->SetParent(nullptr);
    }
    bool IsComposite() const override {
        return true;
    }

    std::string Operation() override {
        std::string result = "Network: \n";
        if (this->GetParent() != nullptr) {
            result += this->GetParent()->GetName() + " -> " + this->GetName() + "\n";
        }
        else {
            result += this->GetName() + "\n";
        }
        
        for (Device* c : _children_list) {
                result += c->Operation() + "\n";
        }
        return result;
    }
};


class NetworkRouter : public CompositeDevice {
public:
    NetworkRouter(unsigned int id) : CompositeDevice(id) {}

    std::string GetName() override {
        return "Network Router [" + std::to_string(this->_id) + "]";
    }

    std::string Operation() override {
        return __super::Operation();
    }
};


void ClientCode(Device* component) {
    std::cout << "RESULT: " << component->Operation();
}


int main() {
    Device* root_tree = new NetworkRouter(1);
    Device* sub_tree = new NetworkRouter(2);

    Device* pc_1 = new PersonalComputer(3);
    Device* pc_2 = new PersonalComputer(4);
    Device* pc_3 = new PersonalComputer(5);
    Device* pc_4 = new PersonalComputer(6);
    Device* pc_5 = new PersonalComputer(7);
    root_tree->Add(pc_1);
    root_tree->Add(pc_2);
    sub_tree->Add(pc_3);
    sub_tree->Add(pc_4);
    sub_tree->Add(pc_5);
    root_tree->Add(sub_tree);
    ClientCode(root_tree);
    std::cout << "\n\n";

    return 0;
}