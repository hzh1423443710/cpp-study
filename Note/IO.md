##### 虚函数表

[(3条消息) 虚函数表详解_彭蔚喆的博客-CSDN博客_虚函数表](https://blog.csdn.net/Primeprime/article/details/80776625)

# IO

## Input number

```c++
int num{};
while (std::cout << "Please a number:", std::cin >> num, !std::cin.eof()) {
    if (std::cin.bad()) {
        throw std::runtime_error("Exception:cin bad");
    }
    if (std::cin.fail()) {//格式化或提取错误
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Incorrect data format, Please input again\n";
        continue;
    }
    std::cout << "num = " << num << std::endl;
}
std::cout << "Input Completion\n";
```

## Input string

```c++
std::string str;
while (std::cout << "Please a string:", std::getline(std::cin, str), !std::cin.eof()) {
    if (std::cin.bad()) {
        throw std::runtime_error("cin is corrupted");
    }
    std::cout << "str = " << str << std::endl;
}
std::cout << "Input Completion\n";
```

## read file

```c++
std::string fileName;
std::string fileContent;

while (std::cout << "Please fileName:", std::cin >> fileName, !std::cin.eof()) {
	if (std::cin.bad()) {
		throw std::runtime_error("cin is corrupted");
	}
	std::ifstream inf(fileName);
	if (inf) {
		while (std::getline(inf, fileContent)) {//读文件
			if (inf.bad()) {
				throw std::runtime_error("inf is corrupted");
			}
			std::cout << "fileContent: " << fileContent << std::endl;
		}
		inf.close();
	}
	else {
		inf.clear();
		inf.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "file open failed\n";
		continue;
	}
}
```

## stringstream

### string -> integer

```c++
//string -> integer
std::stringstream ss("123");
//ss.str("hello");
int num{};
ss >> num;
if (ss.bad()) {
    throw std::runtime_error("stringstream is corrputed");
}
else if (ss.fail()) {
    std::cout << "faile state: " << ss.rdstate() << std::endl;
    ss.clear();
    ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
else {
    std::cout << "num = " << num << std::endl;
}
```

### integer -> string

```c++
//interger -> string
int num = 1234;
std::stringstream ss;
ss << num << std::endl;
if (ss.bad()) {
    throw std::runtime_error("stringstream is corrputed");
}
else {
    std::cout << ss.str() << std::endl;
}
```

### split

```c++
std::stringstream sstr("hello,world,123!,1423443710,");
std::cout << sstr.str() << std::endl;

std::string temp;
long long num{};
while (std::getline(sstr, temp, ',')) {
    if(sstr.bad()) {
        throw std::runtime_error("istringstream bad");
    }
    std::stringstream ss(temp);
    if (ss >> num) {
        std::cout << "num = " << num << std::endl;
    }
    if (ss.bad()) {
        throw std::runtime_error("stringstream bad");
    }
    if (ss.fail()) {
        ss.clear();
        ss.ignore(std::numeric_limits<std::streamsize>::max());
    }
}
```

