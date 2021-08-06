#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <utility>

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

// benchmark setting
const int kNum = 30000;
const int kCap = 10000;
const int kMultiThreadCount = 7;

void perf_test()
{
	int64_t t1 = 0;
	int64_t t2 = 0;

	// vector
	std::cout << "--- vector ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::vector<int> vec;
	vec.reserve(kCap);
	for (int i = 0; i < kNum; i++)
	{
		vec.emplace_back(i);
		vec.push_back(i * 10);
		int x = vec[i];
		vec.pop_back();
	}
	t2 = NowNanoTimestamp();
	std::cout << "vector perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::vector<int> tvec;
	tvec.reserve(kCap);
	for (int i = 0; i < kNum; i++)
	{
		tvec.emplace_back(i);
		tvec.push_back(i * 10);
		int x = tvec[i];
		tvec.pop_back();
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe vector perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// list
	std::cout << "--- list ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::list<int> lt;
	for (int i = 0; i < kNum; i++)
	{
		lt.emplace_back(i);
		lt.emplace_front(i * 10);
		lt.push_back(i);
		lt.push_front(i * 10);
		int x = lt.back();
		int y = lt.front();
		lt.pop_back();
		lt.pop_front();
	}
	t2 = NowNanoTimestamp();
	std::cout << "list perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::list<int> tlt;
	for (int i = 0; i < kNum; i++)
	{
		tlt.emplace_back(i);
		tlt.emplace_front(i * 10);
		tlt.push_back(i);
		tlt.push_front(i * 10);
		int x = tlt.back();
		int y = tlt.front();
		tlt.pop_back();
		tlt.pop_front();
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe list perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// map
	std::cout << "--- map ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::map<int, std::string> mp;
	for (int i = 0; i < kNum; i++)
	{
		mp.insert(std::make_pair(i, "value"));
		mp[i] = "new value";
		mp[i * 10] = "fresh value";
		bool flag = (mp.find(i) != mp.end());
		std::string value = mp[i];
		mp.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "map perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::map<int, std::string> tmp;
	for (int i = 0; i < kNum; i++)
	{
		tmp.insert(std::make_pair(i, "value"));
		tmp[i] = "new value";
		mp[i * 10] = "fresh value";
		bool flag = (tmp.find(i) != tmp.end());
		std::string value = tmp[i];
		tmp.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe map perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// unordered_map
	std::cout << "--- unordered_map ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::unordered_map<int, std::string> ump;
	ump.reserve(kCap);
	ump.rehash(kCap);
	for (int i = 0; i < kNum; i++)
	{
		ump.insert(std::make_pair(i, "value"));
		ump[i] = "new value";
		ump[i * 10] = "fresh value";
		bool flag = (ump.find(i) != ump.end());
		std::string value = ump[i];
		ump.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "unordered_map perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::unordered_map<int, std::string> tump;
	tump.reserve(kCap);
	tump.rehash(kCap);
	for (int i = 0; i < kNum; i++)
	{
		tump.insert(std::make_pair(i, "value"));
		tump[i] = "new value";
		tump[i * 10] = "fresh value";
		bool flag = (tump.find(i) != tump.end());
		std::string value = tump[i];
		tump.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe unordered_map perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// set
	std::cout << "--- set ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::set<int> st;
	for (int i = 0; i < kNum; i++)
	{
		st.insert(i);
		st.insert(i);
		st.insert(i * 10);
		int x = *st.begin();
		bool flag = (st.find(i) != st.end());
		st.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "set perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::set<int> tst;
	for (int i = 0; i < kNum; i++)
	{
		tst.insert(i);
		tst.insert(i);
		tst.insert(i * 10);
		int x = *tst.begin();
		bool flag = (tst.find(i) != tst.end());
		tst.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe set perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// unordered_set
	std::cout << "--- unordered_set ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::unordered_set<int> ust;
	ust.reserve(kCap);
	ust.rehash(kCap);
	for (int i = 0; i < kNum; i++)
	{
		ust.insert(i);
		ust.insert(i);
		ust.insert(i * 10);
		int x = *ust.begin();
		bool flag = (ust.find(i) != ust.end());
		ust.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "unordered_set perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::unordered_set<int> tust;
	tust.reserve(kCap);
	tust.rehash(kCap);
	for (int i = 0; i < kNum; i++)
	{
		tust.insert(i);
		tust.insert(i);
		tust.insert(i * 10);
		int x = *tust.begin();
		bool flag = (tust.find(i) != tust.end());
		tust.erase(i);
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe unordered_set perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// stack
	std::cout << "--- stack ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::stack<int> stk;
	for (int i = 0; i < kNum; i++)
	{
		stk.push(i);
		stk.push(i * 10);
		int x = stk.top();
		stk.pop();
	}
	t2 = NowNanoTimestamp();
	std::cout << "stack perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::stack<int> tstk;
	for (int i = 0; i < kNum; i++)
	{
		tstk.push(i);
		tstk.push(i * 10);
		int x = tstk.top();
		tstk.pop();
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe stack perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// deque
	std::cout << "--- deque ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::deque<int> dq;
	for (int i = 0; i < kNum; i++)
	{
		dq.emplace_back(i);
		dq.emplace_front(i * 10);
		dq.push_back(i);
		dq.push_front(i * 10);
		int x = dq.back();
		int y = dq.front();
		dq.pop_back();
		dq.pop_front();
	}
	t2 = NowNanoTimestamp();
	std::cout << "deque perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	thread_safe::deque<int> tdq;
	for (int i = 0; i < kNum; i++)
	{
		tdq.emplace_back(i);
		tdq.emplace_front(i * 10);
		tdq.push_back(i);
		tdq.push_front(i * 10);
		int x = tdq.back();
		int y = tdq.front();
		tdq.pop_back();
		tdq.pop_front();
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe deque perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	// priority_queue
	std::cout << "--- priority_queue ---" << std::endl;
	t1 = NowNanoTimestamp();
	std::priority_queue<int, std::vector<int>, std::less<int>> pq;
	for (int i = 0; i < kNum; i++)
	{
		pq.push(i);
		pq.push(i * 10);
		int x = pq.top();
		pq.pop();
	}
	t2 = NowNanoTimestamp();
	std::cout << "priority_queue perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;

	t1 = NowNanoTimestamp();
	thread_safe::priority_queue<int, std::vector<int>, std::less<int>> tpq; // FIXME: the template args should use std
	for (int i = 0; i < kNum; i++)
	{
		tpq.push(i);
		tpq.push(i * 10);
		int x = tpq.top();
		tpq.pop();
	}
	t2 = NowNanoTimestamp();
	std::cout << "thread safe priority_queue perf task cost time: " << t2 - t1 << " ns" << " , current thread: " << std::this_thread::get_id() << std::endl;
}

#define TEST_MULTI_THREAD

int main()
{
#ifndef TEST_MULTI_THREAD
	std::cout << "==== single thread operation ====" << std::endl;
	perf_test();
#else
	std::cout << "==== multi thread operation ====" << std::endl;
	std::thread thread_array[kMultiThreadCount];
	for (auto& t : thread_array)
	{
		t = std::thread(perf_test);
		t.detach();
	}

	getchar(); // wait here

#endif // !TEST_MULTI_THREAD

	return 0;
}