#include <iostream>
#include <string>

// original stl header
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <bitset>
#include <queue>
#include <deque>
#include <stack>

// thread safe stl header
#include "thread_safe_vector.h"
#include "thread_safe_list.h"
#include "thread_safe_map.h"
#include "thread_safe_unordered_map.h"
#include "thread_safe_set.h"
#include "thread_safe_unordered_set.h"
#include "thread_safe_bitset.h"
#include "thread_safe_queue.h"
#include "thread_safe_deque.h"
#include "thread_safe_stack.h"

int main()
{
	std::vector<int> v1;
	v1.reserve(10);
	v1.emplace_back(1);
	v1.push_back(2);
	v1.push_back(5);
	v1.pop_back();

	for (auto& e : v1)
		std::cout << e << std::endl;

	std::cout << "-----" << std::endl;

	thread_safe::vector<int> t_v1;
	t_v1.reserve(10);
	t_v1.emplace_back(3);
	t_v1.push_back(4);
	t_v1.push_back(8);
	t_v1.pop_back();

	for (auto& iter = t_v1.begin(); iter != t_v1.end(); ++iter)
		std::cout << *iter << std::endl;

	//for (auto& e : t_v1)
	//	std::cout << e << std::endl;

	std::list<int> l1;

	std::map<int, std::string> m1;
	
	std::unordered_map<int, std::string> m2;
	m2.reserve(10);

	std::unordered_multimap<int, std::string> mm2;
	mm2.reserve(10);

	std::set<int> s1;
	
	std::unordered_set<int> s2;
	s2.reserve(10);

	std::unordered_multiset<int> s3;
	s3.reserve(10);

	std::bitset<8> s4;

	std::deque<int> dq1;

	std::queue<int> q1;
	
	std::priority_queue<int> pq1;

	std::stack<int> st1;
	

	

	return 0;
}