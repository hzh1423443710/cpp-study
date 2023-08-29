#include <iostream>
#include <string>
#include <memory>

class Button
{
public:
    virtual void paint() = 0;
    virtual ~Button() = default;
};

class MacButton : public Button
{
public:
    void paint() override {
        std::cout << "-- painting MacButton\n";
    }
};

class WinButton : public Button
{
public:
    void paint() override {
        std::cout << "-- painting WinButton\n";
    }
};

class LineEdit
{
public:
    std::string getText() {
        return text_;
    }
    void setText(const std::string& text) {
        text_ = text;
    }
    virtual void paint() = 0;
    virtual ~LineEdit() = default;

protected:
    std::string text_;
};

class MacLineEdit : public LineEdit
{
public:
    void paint() override {
        std::cout << "-- painting MacLineEdit\n";
    }
};

class WinLineEdit : public LineEdit
{
public:
    void paint() override {
        std::cout << "-- painting WinLineEdit\n";
    }
};

class GUIFactory
{
public:
    virtual Button* createButton() = 0;
    virtual LineEdit* createLineEdit() = 0;
    virtual ~GUIFactory() = default;
};

class MacFactory : public GUIFactory
{
public:
    Button* createButton() override {
        return new MacButton();
    }
    LineEdit* createLineEdit() override {
        return new MacLineEdit();
    }
};

class WinFactory : public GUIFactory
{
public:
    Button* createButton() override {
        return new WinButton();
    }
    LineEdit* createLineEdit() override {
        return new WinLineEdit();
    }
};

int main(int argc, char* argv[])
{
    using namespace std;
    unique_ptr<GUIFactory> factory = make_unique<MacFactory>();
    // unique_ptr<GUIFactory> factory = make_unique<WinFactory>();
    unique_ptr<Button> btn(factory->createButton());
    unique_ptr<LineEdit> lineEdit(factory->createLineEdit());

    lineEdit->setText("This is Abstract Factory Pattern");
    btn->paint();
    lineEdit->paint();
    cout << lineEdit->getText() << "\n";
    
    return 0;
}