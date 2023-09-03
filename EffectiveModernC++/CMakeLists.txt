
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(test-EffectiveModernC++)

add_executable(typeDeduction ./typeDeduction/typeDeduction.cpp)
add_executable(decayToPointer ./typeDeduction/decayToPointer.cpp)
