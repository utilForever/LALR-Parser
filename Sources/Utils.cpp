#include "Utils.h"

#include <cstring>

int HashFuncAccum(const char* str)
{
	int nAccum = 0;
	int i = 0;

	for (; str[i] != '\0'; ++i)
	{
		nAccum += (str[i] - 'a');
	}

	nAccum = 3 * str[0] + 1 * str[i - 1] + 2 * str[(i - 1) >> 2];

	return abs(nAccum) % HashingTab::NUM_LOAD_FACTOR;
}

void HashingTab::Build(const char** strArray)
{
	int i = 0;

	for (; strArray[i] != nullptr; ++i)
	{
		const int nAccum = m_hashFunc(strArray[i]);
		const int nKey = nAccum % NUM_LOAD_FACTOR;

		if (m_hashTab[nKey] == nullptr)
		{
			m_hashTab[nKey] = new SeparateChain;
		}

		m_hashTab[nKey]->emplace_back(std::move(strArray[i]));
	}
}

const char* HashingTab::Match(const char* src)
{
	const int nPattern = HashFuncAccum(src);

	SeparateChain* chain = m_hashTab[nPattern % NUM_LOAD_FACTOR];

	if (chain == nullptr)
	{
		return nullptr;
	}

	ChainIter iter = chain->begin();
	for (; iter != chain->end(); ++iter)
	{
		if (_stricmp(src, (*iter).c_str()) == 0)
		{
			break;
		}
	}

	if (iter == chain->end())
	{
		return nullptr;
	}

	return (*iter).c_str();
}