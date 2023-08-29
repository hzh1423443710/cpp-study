

# -- 单例
add_executable(Singleton1 Singleton/Singleton1.cpp)
add_executable(Singleton2 Singleton/Singleton2.cpp)
add_executable(Singleton2_multhread Singleton/Singleton2_multhread.cpp)
add_executable(producer_consumer Singleton/main.cpp)

# -- 简单工厂
add_executable(simpleFactory ./SimpleFactory/SimpleFactory.cpp)
# -- 工厂模式
add_executable(FactoryMethod ./FactoryMethod/FactoryMethod.cpp)
# -- 抽象工厂
add_executable(AbstractFactory ./AbstractFactory/AbstractFactory.cpp)

# -- 原型模式
add_executable(Prototype ./Prototype/prototype.cpp)