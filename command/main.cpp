#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <list>


class Command {
public:
    ~Command() {
    }
    virtual void Execute() const = 0;
};


class OpenCommand : public Command {
public:
    void Execute() const {
        std::cout << "OpenCommand: \t Openned" << std::endl;
    }
};


class CloseCommand : public Command {
    void Execute() const {
        std::cout << "CloseCommand: \t Closed" << std::endl;
    }
};


class SomeCommand : public Command {
    void Execute() const {
        std::cout << "SomeCommand: \t Some actions have been performed" << std::endl;
    }
};


class PrintCommand : public Command {
private:
    std::string _text;
public:
    PrintCommand(std::string text) : _text(text) {}

    void Execute() const {
        std::cout << "PrintCommand: \t " << _text << std::endl;
    }
};


class MacroCommand : public Command {
private:
    std::list<Command* > _commands;
public:
    void Add(Command* command) {
        _commands.push_back(command);
    }

    void Remove(Command* command) {
        _commands.remove(command);
    }

    void Execute() const {
        std::cout << "MacroCommand: \t Start executing the command chain" << std::endl;
        for (Command* command : _commands) {
            command->Execute();
        }
    }
};


class ClientCode {
private:
    Command* _on_open;
    Command* _on_close;
public:
    void SetOnOpen(Command* command) {
        _on_open = command;
    }

    void SetOnClose(Command* command) {
        _on_close = command;
    }

    void DoSomething() {
        std::cout << "ClientCode: \t Start of execution" << std::endl;
        if (this->_on_open) {
            this->_on_open->Execute();
        }
        std::cout << "ClientCode: \t End of execution" << std::endl;
        if (this->_on_close) {
            this->_on_close->Execute();
        }
    }
};


int main() {
    auto client = new ClientCode;
    client->SetOnOpen(new OpenCommand);
    client->SetOnClose(new CloseCommand);
    client->DoSomething();

    std::cout << std::endl;

    client = new ClientCode;
    auto macro = new MacroCommand;
    macro->Add(new OpenCommand);
    macro->Add(new PrintCommand("Print this text"));
    macro->Add(new SomeCommand);
    client->SetOnOpen(macro);
    client->SetOnClose(new CloseCommand);
    client->DoSomething();

    return 0;
}