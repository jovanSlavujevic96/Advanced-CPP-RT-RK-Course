project (Vezbanje3)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD 20)

#zadatak 1
add_library(MyBigInt
	zadatak1/MyBigInt.h
	zadatak1/MyBigInt.cpp
)

add_executable(zadatak1 zadatak1/zadatak1.cpp)
target_link_libraries(zadatak1 MyBigInt)

#zadatak 2

add_executable(zadatak2
	zadatak2/BigData.h
	zadatak2/zadatak2.cpp
)

#zadatak 3

add_executable(zadatak3
	zadatak3/type_name.hpp
	zadatak3/zadatak3.cpp
)

#zadatak 4

add_executable(zadatak4
	zadatak4/MyUniquePtr.h
	zadatak4/zadatak4.cpp
)
