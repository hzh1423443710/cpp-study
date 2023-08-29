#include <iostream>
#include <memory>

// AbstractProduct
class AbstractCalc
{
public:
    enum class CALC_TYPE : char
    {
        ADD,
        SUB,
        MUL,
        DIV
    };
public:
    virtual int calc() = 0;
    void setLeftRight(int left, int right)
    {
        this->left = left;
        this->right = right;
    }
    virtual ~AbstractCalc() = default;
protected:
    int left;
    int right;
};

// Concrete Product
class AddCalc : public AbstractCalc
{
public:
    int calc() override
    {
        return left + right;
    }
};
class SubCalc : public AbstractCalc
{
public:
    int calc() override
    {
        return left - right;
    }
};
class MulCalc : public AbstractCalc
{
public:
    int calc() override
    {
        return left * right;
    }
};
class DivCalc : public AbstractCalc
{
public:
    int calc() override
    {
        return left / right;
    }
};

// Abstract Factory
class AbstractFactory
{
public:
    virtual std::unique_ptr<AbstractCalc> createCalc() = 0;
    virtual ~AbstractFactory() = default;

};

// Concrete Factory
class AddFactory : public AbstractFactory
{
public:
    std::unique_ptr<AbstractCalc> createCalc() override {
        return std::make_unique<AddCalc>();
    }
};

class SubFactory : public AbstractFactory
{
public:
    std::unique_ptr<AbstractCalc> createCalc() override {
        return std::make_unique<SubCalc>();
    }
};

class MulFactory : public AbstractFactory
{
public:
    std::unique_ptr<AbstractCalc> createCalc() override {
        return std::make_unique<MulCalc>();
    }
};

class DivFactory : public AbstractFactory
{
public:
    std::unique_ptr<AbstractCalc> createCalc() override {
        return std::make_unique<DivCalc>();
    }
};

int main(int argc, char* argv[])
{
    using namespace std;
    unique_ptr<AbstractFactory> calcFactory = make_unique<AddFactory>();
    auto addCalc = calcFactory->createCalc();
    int a = 100;
    int b = 200;
    addCalc->setLeftRight(a, b);
    printf("%d + %d = %d\n", a, b, addCalc->calc());

    return 0;
}