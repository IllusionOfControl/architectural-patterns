#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


class Strategy
{
public:
    virtual ~Strategy() {}
    virtual std::string DoAlgorithm(const std::vector<std::string>& data) const = 0;
};


class Context
{
private:
    Strategy* _algorithm;
public:
    Context(Strategy* algorithm = nullptr) : _algorithm(algorithm) {}
    
    void set_strategy(Strategy* algorithm)
    {
        this->_algorithm = algorithm;
    }

    void DoSomething() const
    {
        std::string result = this->_algorithm->DoAlgorithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
        std::cout << result << "\n";
    }
};


class AlgorithmA : public Strategy
{
public:
    std::string DoAlgorithm(const std::vector<std::string>& data) const override
    {
        std::string result;
        for (auto letter : data) {
            result += letter;
        }
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};
class AlgorithmB : public Strategy
{
    std::string DoAlgorithm(const std::vector<std::string>& data) const override
    {
        std::string result;
        for (auto letter : data) {
            result += letter;
        }
        std::sort(std::begin(result), std::end(result));
        for (int i = 0; i < result.size() / 2; i++)
        {
            std::swap(result[i], result[result.size() - i - 1]);
        }

        return result;
    }
};


void ClientCode()
{
    Context* context = new Context(new AlgorithmA);
    std::cout << "Client: Sort algorithm is set to normal mode." << std::endl;
    context->DoSomething();
    std::cout << std::endl;
    std::cout << "Client: Sort algorithm is set to reverse mode." << std::endl;
    context->set_strategy(new AlgorithmB);
    context->DoSomething();
    delete context;
}

int main()
{
    ClientCode();
    return 0;
}