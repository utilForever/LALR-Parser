#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <list>
#include <string>
#include <vector>

int HashFuncAccum(const char* str);

class HashingTab
{
public:
	static const int NUM_LOAD_FACTOR = 17;

	HashingTab() : m_hashTab(NUM_LOAD_FACTOR)
	{
		for (OpenHashing::size_type i = 0; i < m_hashTab.size(); ++i)
		{
			m_hashTab[i] = nullptr;
		}

		m_hashFunc = HashFuncAccum;
	}

	void Build(const char** strArray);

	const char* Match(const char* src);

private:
	using SeparateChain = std::list<std::string>;
	using ChainIter = SeparateChain::iterator;
	using OpenHashing = std::vector<SeparateChain*>;
	using HashFunc = std::function<int(const char*)>;

	OpenHashing m_hashTab;
	HashFunc m_hashFunc;
};

#endif