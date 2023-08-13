#include <iostream>
#include <list>
#include <array>
#include <algorithm>
#include <iterator>
#include <sstream>

void testContainerManipulators();
void testStreamIterators();

int main(int argc, char *argv[])
{
	testStreamIterators();

}

/* Special Iterator[https://hackingcpp.com/cpp/std/special_iterators.html]
 * Input Iterators/OutputIterators
 *
 * Container Manipulators:
 *      std::insert_iterator<Container>
 *      std::back_insert_iterator<Container>
 *      std::front_insert_iterator<Container>
 *
 * I/O Stream Iterators:
 *      std::ostream_iterator<ValueType>
 *      std::istream_iterator<ValueType>
 */

void testContainerManipulators()
{
	std::vector<int> v {4, 8, 2};
	std::list<int> l(v.begin(), v.end());
	std::array<int,2> a {5, 6};

	// 1.std::inserter(container,pos) -> std::insert_iterator<ContainerType>{container,pos}
	// *it = value calls .insert(position, value) on a container
//	std::insert_iterator<std::vector<int>> it(v, v.begin());
//	*it = 5;
//	*it = 6;
//	std::copy(a.begin(), a.end(), std::inserter(v, v.begin())); // 等价

	// 2.std::back_inserter(container) -> std::back_insert_iterator<ContainerType>{container}
	// *it = value calls .push_back(value) on a container
//	std::back_insert_iterator<std::vector<int>> it(v);
//	*it = 5;
//	*it = 6;
//	std::copy(a.begin(), a.end(), std::back_inserter(v)); // 等价

	// 3.std::front_inserter(container) -> std::front_insert_iterator<ContainerType>{container}
	// *it = value calls .push_front(value) on a container
	std::front_insert_iterator<std::list<int>> it(l);
	*it = 5;
	*it = 6;

//	std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout,  ", "});
	std::copy(l.begin(), l.end(), std::ostream_iterator<int>{std::cout,  ", "});
}


void testStreamIterators()
{
	// std::ifstream ...
	std::istringstream istr("1 2 3 4 5");
	std::vector<int> arr;
	std::copy(std::istream_iterator<int>{istr}, std::istream_iterator<int>{}, std::back_inserter(arr));


	std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, ","});
}
