#include <iostream>
#include <string>
using namespace std;

class FileError : public exception {
public:
    FileError() {}
    FileError(const string& error,int line) : m_error(error),m_line(line) {
        cout << "construction FileError : " << m_error << endl;
    }

    const char* what() const noexcept {             //重写标准异常类的what方法 
        cout << "line:" << m_line << " FileError:" + m_error << endl;
        return "FileError";
    }
    ~FileError() {
        cout << "destruction FileError " << m_error << endl;
    }
private:
    string m_error;
    int m_line = 0;
};

void test() {
    FileError s;
    cout << "enter test()" << endl;
    throw FileError(string("this is a small error"),__LINE__);
    cout << "leave test()" << endl;
}

int main()
{
    try
    {
        test();
    }
    catch(const FileError& e)
    {
        e.what();
    }
    
    cout << ">------>main End" << endl;
    return 0;
}