#include <iostream>
#include <string>
#include <chrono>

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

static inline uint64_t NowNanoTimestamp()
{
	auto now = std::chrono::system_clock::now(); // system_clock can get the current timestamp, (accuracy is 100 ns win, 1 ns in linux)
	long long timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

	return timestamp;
}

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
	
	int n = 30000;
	int kCap = 5000;

	int64_t t1 = NowNanoTimestamp();
	std::unordered_map<int, std::string> m2;
	m2.reserve(kCap);
	for (int i = 0; i < n; i++)
		m2[i] = std::to_string(i);
	int64_t t2 = NowNanoTimestamp();
	std::cout << "origin time cost: " << t2 - t1 << " ns" << std::endl;

	int64_t tt1 = NowNanoTimestamp();
	thread_safe::unordered_map<int, std::string> t_m2;
	t_m2.reserve(kCap);
	for (int i = 0; i < n; i++)
		t_m2[i] = std::to_string(i);
	int64_t tt2 = NowNanoTimestamp();
	std::cout << "thread safe time cost: " << tt2 - tt1 << " ns" << std::endl;

	std::unordered_multimap<int, std::string> mm2;
	mm2.reserve(10);

	thread_safe::unordered_multimap<int, std::string> t_mm2;

	std::set<int> s1;

	std::cout << "-----" << std::endl;
	
	t1 = NowNanoTimestamp();
	std::unordered_set<int> s2;
	s2.reserve(kCap);
	for (int i = 0; i < n; i++)
		s2.insert(i);
	t2 = NowNanoTimestamp();
	std::cout << "origin time cost: " << t2 - t1 << " ns" << std::endl;

	tt1 = NowNanoTimestamp();
	thread_safe::unordered_set<int> t_s2;
	t_s2.reserve(kCap);
	for (int i = 0; i < n; i++)
		t_s2.insert(i);
	tt2 = NowNanoTimestamp();
	std::cout << "thread safe time cost: " << tt2 - tt1 << " ns" << std::endl;

	std::unordered_multiset<int> s3;
	s3.reserve(10);

	thread_safe::unordered_multiset<int> t_3;

	std::bitset<8> s4;

	std::deque<int> dq1;

	std::queue<int> q1;
	
	std::priority_queue<int> pq1;

	std::stack<int> st1;
	

	

	return 0;
}