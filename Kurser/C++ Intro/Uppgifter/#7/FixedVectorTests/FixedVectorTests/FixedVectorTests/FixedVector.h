#pragma once
#include <cassert>

namespace CommonUtilities
{
	template <typename Type, typename unsigned int CAPACITY, typename SizeType = unsigned int>
	class FixedVector
	{
	public:
		typedef Type* iterator;
		typedef const Type* const_iterator;

		FixedVector()
		{

		}
		FixedVector(const FixedVector& aFixedVector)
		{
			this = aFixedVector;
		}
		~FixedVector()
		{

		}
		FixedVector& operator=(const FixedVector& aFixedVector)
		{
			for (SizeType i = 0; i < CAPACITY; i++)
			{
				myStorage[i] = aFixedVector[i];
			}
			return this;
		}

		Type& front()
		{
			return myStorage[0];
		}
		const Type& front() const
		{
			return front();
		}
		Type& back()
		{
			return myStorage[size() - 1];
		}
		const Type& back() const
		{
			return back();
		}

		Type& at(SizeType aIndex)
		{
			return myStorage[aIndex];
		}
		const Type& at(SizeType aIndex) const
		{
			return at(aIndex);
		}

		const Type& operator[](SizeType aIndex) const
		{
			return GetElement(aIndex);
		}
		Type& operator[](SizeType aIndex)
		{
			return GetElement(aIndex);
		}

		void push_back(const Type& aObject)
		{
			AddObject(aObject);
		}
		void insert(iterator aIterator, const Type& aObject)
		{
			(*aIterator) = aObject;
		}
		void erase(iterator aIterator)
		{
			(*aIterator) = NULL;
		}
		void pop_back()
		{
			erase(*back());
		}

		iterator begin()
		{
			return *myStorage[0];
		}
		const_iterator begin() const
		{
			return begin();
		}
		const_iterator cbegin() const
		{
			return begin();
		}

		iterator end()
		{
			return (*back()) + 1;
		}
		const_iterator end() const
		{
			return end();
		}
		const_iterator cend() const
		{
			return end();
		}

		void clear()
		{
			while (!empty())
			{
				pop_back();
			}
		}
		void resize(SizeType newSize);
		void resize(SizeType newSize, const Type& value);

		bool empty() const
		{
			return size() <= 0;
		}
		SizeType size() const
		{
			return mySize;
		}
		SizeType capacity() const
		{
			return CAPACITY;
		}

	private:
		SizeType mySize = 0;
		Type myStorage[CAPACITY]; //<- for G
		//alignas(Type) char myStorage[sizeof(Type) * CAPACITY]; // <- needed for VG 





	private:
		void AddObject(Type& aObject)
		{
			assert(size() < capacity());
			myStorage[size()] = aObject;
			mySize++;
		}
		Type& GetElement(int aIndex)
		{
			return myStorage[aIndex];
		}
	};
}