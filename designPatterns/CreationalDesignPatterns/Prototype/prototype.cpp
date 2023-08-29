#include <iostream>
#include <string>
#include <memory>

class TerminatorProtoType
{
public:
    virtual TerminatorProtoType* clone() = 0;
    virtual std::string model() = 0;
};

class T_800 : public TerminatorProtoType
{
public:
    TerminatorProtoType* clone () override {
        return new T_800(*this);
    }
    std::string model() override {
        return "T-800";
    }
};

class T_1000 : public TerminatorProtoType
{
public:
    TerminatorProtoType* clone () override {
        return new T_1000(*this);
    }
    std::string model() override {
        return "T-1000";
    }
};

int main(int argc, char* argv[])
{
    using namespace std;
    unique_ptr<TerminatorProtoType> pT(new T_800);
    cout << pT->model() << "\n";

    unique_ptr<TerminatorProtoType> pT2(pT->clone());
    cout << pT2->model() << "\n";

    pT.reset(new T_1000);
    cout << pT->model() << "\n";


    return 0;
}