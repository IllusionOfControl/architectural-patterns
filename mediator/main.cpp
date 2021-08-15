#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <array>
#include <vector>


class BaseElementUI;

class BaseUIMediator {
public:
    virtual void Notify(BaseElementUI* sender, std::string event) = 0;
};


class BaseElementUI {
protected:
    BaseUIMediator* _inputManager;

public:
    BaseElementUI(BaseUIMediator* manager = nullptr) : _inputManager(manager) {}

    void set_mediator(BaseUIMediator* manager) {
        this->_inputManager = manager;
    }
};


class ButtonUI : public BaseElementUI {
public:
    void Click() {
        std::cout << "ButtonUI does click." << std::endl;;
        this->_inputManager->Notify(this, "click");
    }
};


class SliderUI : public BaseElementUI {
public:
    void Slide() {
        std::cout << "SliderUI does slide." << std::endl;;
        this->_inputManager->Notify(this, "slide");
    }

    void Hide() {
        std::cout << "SliderUI does hide." << std::endl;;
        this->_inputManager->Notify(this, "hide");
    }
};


class CustomUIMediator : BaseUIMediator {
private:
    ButtonUI* _button;
    SliderUI* _slider;
public:
    CustomUIMediator(ButtonUI* button, SliderUI* slider) : _button(button), _slider(slider) {
        this->_button->set_mediator(this);
        this->_slider->set_mediator(this);
    }


    void Notify(BaseElementUI* sender, std::string event) {
        if (event == "click") {
            std::cout << "Mediator reacts on Click()." << std::endl;;
        }
        if (event == "slide") {
            std::cout << "Mediator reacts on Slide()." << std::endl;
            std::cout << "Mediator performs Hide()." << std::endl;
        }
    }
};


void ClientCode() {
    auto button = new ButtonUI;
    auto slider = new SliderUI;
    auto mediator = new CustomUIMediator(button, slider);
    std::cout << "Client triggers operation Click()." << std::endl;
    button->Click();
    std::cout << std::endl;
    std::cout << "Client triggers operation Slide()." << std::endl;
    slider->Slide();

    std::cout << std::endl;
    std::cout << "Client triggers operation Hide()." << std::endl;
    slider->Hide();
}

int main() {
    ClientCode();
    return 0;
}