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
			*this = aFixedVector;
		}
		~FixedVector()
		{
			clear();
		}
		FixedVector& operator=(const FixedVector& aFixedVector)
		{
			this->~FixedVector();
			for (SizeType i = 0; i < CAPACITY; i++)
			{
				myStorage[i] = aFixedVector[i];
				mySize++;
			}
			return *this;
		}

		Type& front()
		{
			assert(!empty());
			return myStorage[0];
		}
		const Type& front() const
		{
			assert(!empty());
			return myStorage[0];
		}
		Type& back()
		{
			assert(!empty());
			return myStorage[size() - 1];
		}
		const Type& back() const
		{
			assert(!empty());
			return myStorage[size() - 1];
		}

		Type& at(SizeType aIndex)
		{
			assert(!empty() && aIndex >= 0 && aIndex < mySize);
			return myStorage[aIndex];
		}
		const Type& at(SizeType aIndex) const
		{
			assert(!empty() && aIndex >= 0 && aIndex < mySize);
			return myStorage[aIndex];
		}

		const Type& operator[](SizeType aIndex) const
		{
			return at(aIndex);
		}
		Type& operator[](SizeType aIndex)
		{
			return at(aIndex);
		}

		void push_back(const Type& aObject)
		{
			AddObjectAtEnd(aObject); //double check uppgift
		}
		void insert(iterator aIterator, const Type& aObject)
		{
			assert(mySize < CAPACITY && aIterator >= begin() && aIterator <= end());
			if (empty())
			{
				push_back(aObject);
				return;
			}

			iterator reverseIterator = end();
			while (reverseIterator != aIterator)
			{
				*reverseIterator = *(reverseIterator - 1);
				reverseIterator--;
			}
			*aIterator = aObject;
			mySize++;
		}
		void erase(iterator aIterator)
		{
			assert(mySize > 0 && aIterator >= begin() && aIterator < end());
			const iterator lastPtr = end() - 1;
			while (aIterator != lastPtr)
			{
				*aIterator = *(aIterator + 1);
				aIterator++;
			}
			pop_back();
		}
		void pop_back()
		{
			myStorage[--mySize].~Type();
		}

		iterator begin()
		{
			return &myStorage[0];
		}
		const_iterator begin() const
		{
			return &myStorage[0];
		}
		const_iterator cbegin() const
		{
			return begin();
		}

		iterator end()
		{
			return &myStorage[size()];
		}
		const_iterator end() const
		{
			return &myStorage[size()];
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
		void resize(SizeType newSize)
		{
			assert(newSize < CAPACITY);
			mySize = newSize;
		}
		void resize(SizeType newSize, const Type& value)
		{
			SizeType filledSize = mySize;
			resize(newSize);
			while (filledSize < newSize)
			{
				myStorage[filledSize] = value;
				filledSize++;
			}
		}

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
		void AddObjectAtEnd(const Type& aObject)
		{
			assert(size() < capacity());
			myStorage[size()] = Type(aObject);
			mySize++;
		}
		Type& GetElement(int aIndex)
		{
			return myStorage[aIndex];
		}
	};
}