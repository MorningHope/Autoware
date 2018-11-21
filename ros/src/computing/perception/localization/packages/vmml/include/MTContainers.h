/*
 * MTContainers.h
 *
 *  Created on: Nov 9, 2018
 *      Author: sujiwo
 */

#ifndef _MTCONTAINERS_H_
#define _MTCONTAINERS_H_


/*
 * XXX : Stub for thread-safe containers
 */



#include <vector>
#include <map>
#include <set>
#include <thread>
#include <mutex>


namespace Mt {

template<typename T>
class vector : public std::vector<T>
{
public:

	typedef std::vector<T> MtVecBase;

	vector () : MtVecBase()
	{}

	// Copy constructor
	vector (const MtVecBase &vc) noexcept:
		MtVecBase(vc)
	{}

	// Move constructor
	vector (MtVecBase &&vm) noexcept:
		MtVecBase (vm)
	{}

	void push_back (const T& val)
	{
		ngelock.lock();
		std::vector<T>::push_back(val);
		ngelock.unlock();
	}


protected:
	std::mutex ngelock;
};


template<typename K, typename V>
class map : public std::map<K,V>
{
public:

	typedef std::map<K,V> MtMapBase;

	// insert
	std::pair<typename MtMapBase::iterator, bool>
	insert(const typename MtMapBase::value_type &val)
	{
		ngelock.lock();
		auto rt = MtMapBase::insert(val);
		ngelock.unlock();
		return rt;
	}

	// delete
	typename MtMapBase::size_type
	erase(const typename MtMapBase::key_type &k)
	{
		ngelock.lock();
		auto sz = MtMapBase::erase(k);
		ngelock.unlock();
		return sz;
	}

	// key access

	// at

protected:

	std::mutex ngelock;
};


}	// namespace Mt


#endif /* _MTCONTAINERS_H_ */
