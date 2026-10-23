#pragma once
#include <cassert>

namespace CommonUtilities
{
	/// <summary>
	/// Implements a class with similar interface to std::vector, but stores data inlined in the class with a fixed storage capacity.
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <typeparam name="SizeType"></typeparam>
	/// <typeparam name="CAPACITY"></typeparam>
	template <typename Type, unsigned int CAPACITY, typename SizeType = unsigned int>
	class FixedVector
	{
	public:
		typedef Type* iterator;
		typedef const Type* const_iterator;
		FixedVector();
		FixedVector(const FixedVector& aFixedVector);
		~FixedVector();
		FixedVector& operator=(const FixedVector& aFixedVector);
		Type& front();
		const Type& front() const;
		Type& back();
		const Type& back() const;
		Type& at(SizeType aIndex);
		const Type& at(SizeType aIndex) const;
		const Type& operator[](SizeType aIndex) const;
		Type& operator[](SizeType aIndex);
		void push_back(const Type& aObject);
		void insert(iterator aIterator, const Type& aObject);
		void erase(iterator aIterator);
		void pop_back();
		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;
		void clear();
		void resize(SizeType newSize);
		void resize(SizeType newSize, const Type& value);
		bool empty() const;
		SizeType size() const;
		SizeType capacity() const;
	private:
		SizeType mySize = 0;
		Type myStorage[CAPACITY]; //<- for G
		//alignas(Type) char myStorage[sizeof(Type) * CAPACITY]; // <- needed for VG
	};
}