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

// Simple Factory
class Factory
{
public:
    static std::unique_ptr<AbstractCalc> createCalc(AbstractCalc::CALC_TYPE type)
    {
        using namespace std;
        unique_ptr<AbstractCalc> calc; 
        switch (type) {
        case AbstractCalc::CALC_TYPE::ADD:
            calc = make_unique<AddCalc>();
            break;
        case AbstractCalc::CALC_TYPE::SUB:
            calc = make_unique<SubCalc>();
            break;
        case AbstractCalc::CALC_TYPE::MUL:
            calc = make_unique<MulCalc>();
            break;
        case AbstractCalc::CALC_TYPE::DIV:
            calc =  make_unique<DivCalc>();
            break;
        default:
            break;
        }
        return calc;
    }
};

int main(int argc, char* argv[])
{
    using namespace std;
    auto pCalc = Factory::createCalc(AbstractCalc::CALC_TYPE::SUB);
    if (pCalc) {
        int a = 100;
        int b = 200;
        pCalc->setLeftRight(a, b);
        cout << a << " - " << b << " = "<< pCalc->calc() << "\n";
    }

    return 0;
}