#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


class Handler {
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};


class BaseHandler : public Handler {
private:
    Handler* _next_handler;

public:
    Handler* SetNext(Handler* handler) {
        this->_next_handler = handler;

        // Для цепочного связывыния возвращаем обработчик
        return handler;
    }

    std::string Handle(std::string request) override {
        if (this->_next_handler) {
            return this->_next_handler->Handle(request);
        }
        return {};
    }
};


class TeaHandler : public BaseHandler {
    std::string Handle(std::string request) {
        if (request == "TEA") {
            return "the " + request + " was brewed in a teapot";
        }
        else {
            return __super::Handle(request);
        }
    }
};


class JuiceHandler : public BaseHandler {
    std::string Handle(std::string request) {
        if (request == "JUICE") {
            return "The " + request + " was made in a juicer";
        }
        else {
            return __super::Handle(request);
        }
    }
};


class CoffeeHandler : public BaseHandler {
    std::string Handle(std::string request) {
        if (request == "COFFEE") {
            return "The " + request + "was made in a coffee maker";
        }
        else {
            return __super::Handle(request);
        }
    }
};


void ClientCode(Handler& handler) {
    std::vector<std::string> drinks = { "COFFEE", "TEA", "MILK", "JUICE"};

    for (std::string d : drinks) {
        std::cout << "Client: Order for " << d << std::endl;
        std::string result = handler.Handle(d);
        if (!result.empty()) {
            std::cout << result << std::endl;
        }
        else {
            std::cout << "! It isn`t known how to process the " + d << std::endl;
        }

    }
}


int main() {
    TeaHandler* tea = new TeaHandler;
    JuiceHandler* juice = new JuiceHandler;
    CoffeeHandler* coffee = new CoffeeHandler;
    
    tea->SetNext(juice)->SetNext(coffee);

    ClientCode(*tea);

    return 0;
}