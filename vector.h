#pragma once
#ifndef __VECTOR_H
#define __VECTOR_H

#include <iostream>
#include <memory>
#include "construct.h"
using namespace std;

template<class T>
class vector
{
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef value_type* const const_pointer;
	typedef value_type* const const_iterator;
	typedef value_type& const const_reference;
	typedef size_t size_type;

	void __allocate_and_fill(size_type n, const T& value)
	{
		iterator res = (iterator)malloc(n*sizeof(T));
		if (res != 0)
		{
			start = res;
			finish = start + n;
			end_of_storage = finish;

			while (n--)
			{
				construct(res, value);
				res++;
			}
		}
		else
		{
			cout << "ÄÚ´æ²»×ã£¬·ÖÅäÊ§°Ü£¡£¡£¡" << endl;
		}
	}

	iterator __allocate_and_copy(iterator first, iterator last, size_type n)
	{
		iterator res = (iterator)malloc(n * sizeof(T));
		iterator _start = res;
		if (res != 0)
		{
			while (first<last)
			{
				construct(res, *first);
				res++;
				first++;
			}
		}
		else
		{
			cout << "ÄÚ´æ²»×ã£¬·ÖÅäÊ§°Ü£¡£¡£¡" << endl;
		}
		return _start;
	}

	iterator __copy(iterator first, iterator last, iterator _start)
	{
		while (first<last)
		{
			*_start++ = *first++;
		}
		return _start;
	}
public:
	vector():start(0),finish(0),end_of_storage(0){}
	vector(size_type n, const T& value)
	{
		__allocate_and_fill(n, value);
	}
	vector(vector<T>&vec) 
	{
		start = __allocate_and_copy(vec.begin(), vec.end(), vec.end() - vec.begin());
		finish = start + (vec.end() - vec.begin());
		end_of_storage = finish;
	}
	vector(iterator first, iterator last)
	{
		start = __allocate_and_copy(first, last, last - first);
		finish = start + (last - first);
		end_of_storage = finish;	
	}
	vector(size_type n)
	{
		__allocate_and_fill(n, T());
	}
	~vector()
	{
		destory(start, finish);
		free(start);
	}

	iterator begin() { return start; }
	const iterator begin() const { return start; }
	iterator end() { return finish; }
	const iterator end() const{ return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const { return size_type(end_of_storage - begin()); }
	bool empty() { return begin() == end(); }
	T& front() { return *begin(); }
	T& back() { return *(end() - 1); }


	void push_back(const T& x)
	{
		if (finish != end_of_storage)
		{
			construct(finish, x);
			finish++;
		}
		else
		{
			const size_type old_size = size();
			const size_type len = old_size != 0 ? 2 * old_size : 1;
			iterator new_start = (iterator)malloc(len * sizeof(T));
			iterator new_finish = new_start;
			try {
				new_finish = __copy(start, finish, new_start);
				construct(new_finish, x);
				++new_finish;
			}
			catch (...)
			{
				destory(new_start, new_finish);
				free(new_start);
				new_start = new_finish = NULL;
				throw;
			}
			destory(begin(), end());
			free(start);
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}
	}
	void pop_back()
	{
		if (finish > start)
		{
			--finish;
			destory(finish);
		}
		else
			throw;
	}
	iterator erase(iterator position)
	{
		if (position>begin()&&position<end())
		{
			__copy(position + 1, finish, position);
		}
		--finish;
		destory(finish);
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		iterator q = __copy(last, finish, first);
		destory(q, finish);
		finish = finish - (last - first);
		return first;
	}
	void resize(size_type new_size, const T& x)
	{
		if (new_size < size())
			erase(begin() + new_size, finish);
		else
			insert(end(), new_size - size(), x);
	}
	void resize(size_type new_size) 
	{
		resize(new_size, T());
	}
	void insert(iterator position, const T& value)
	{
		insert(position, 1, value);
	}
	void insert(iterator position, size_type n, const T& value)
	{
		if (finish + n < end_of_storage)
		{
			for (int i = 0; i < n; ++i)
			{
				iterator temp = finish;
				while (finish != position)
				{
					*finish = *finish - 1;
				}
				*position = value;
				finish++;
			}
		}
		else
		{
			const size_type old_size = size();
			const size_type new_size = old_size != 0 ? 2 * old_size : 1;
			iterator new_start = (iterator)malloc(new_size * sizeof(T));
			iterator new_finish = new_start;
			try
			{
				new_finish = __copy(start, position, new_start);
				while (n--)
				{
					construct(new_finish, value);
					new_finish++;
				}
				new_finish = __copy(position, finish, new_finish);

			}
			catch (...)
			{
				destory(new_start, new_finish);
				free(new_start);
				new_start = new_finish = NULL;
				throw;
			}
			destory(begin(), end());
			free(start);
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + new_size;
		}
	}
	void clear()
	{
		erase(begin(), end());
	}

	T& operator[](int n) { return *(begin() + n); }

	bool operator==(vector &vec)
	{
		if (vec.size() != size())
			return false;
		for (iterator it = vec.begin(); it != vec.end(); ++it)
		{
			if (*it != (begin() + (it - vec.begin())))
				return false;
		}
		return true;
	}
	bool operator!=(vector vec)
	{
		return !opeartor == (vec);
	}
private:
	iterator start;
	iterator finish;
	iterator end_of_storage;
};

#endif // !VECTOR_H

