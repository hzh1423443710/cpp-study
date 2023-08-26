#include <iostream>
#include <fstream>
#include <string>

void test_string();

int main()
{
    test_string();

    return 0;
}

void test_string()
{
    using namespace::std;
    // ������utf8��ռ3�ֽ�, ��utf16, utf32��ռ2�ֽ�
    // strlen, std::string.size()��ȡ�����ֽ���
    // std::wstring, std::u16string, std::u32string��ȡ�����ַ���

    std::wstring s1 = L"ABC123���";
    std::cout << "s1 size = " << s1.size() * sizeof(std::wstring::value_type) << "\n";

    std::u16string s2 = u"ABC123���";
    std::cout << "s2 size = " << s2.size() * sizeof(std::u16string::value_type) << "\n";

    std::u32string s3 = U"ABC123���";
    std::cout << "s3 size = " << s3.size() * sizeof(std::u32string::value_type) << "\n";

    std::string s4 = u8"ABC123���";
    std::cout << "s4 size = " << s4.size() * sizeof(std::string::value_type) << "\n";

    printf("%#llx\n", (uintptr_t)s1.data());
    printf("%#llx\n", (uintptr_t)s2.data());
    printf("%#llx\n", (uintptr_t)s3.data());
    printf("%#llx\n", (uintptr_t)s4.data());

    std::ofstream ofs("./text", ios_base::out | ios_base::binary);
    if (!ofs) {
        cout << "file open failed\n"; return;
    }

    ofs.write(s4.data(), s4.length());
    int num = 65;
    ofs.write((const char*) & num, sizeof num);

    ofs.close();
}
