#pragma once
template<class T>				//调用类的析构函数将指针所指的对象析构
inline void destory(T* pointer)
{
	pointer->~T();
}

template <class T1,class T2>		//在p所指对象上创建一个对象，并用value初始化。
inline void construct(T1* p, const T2& value)
{
	new (p) T1(value);
}

template<class ForwardIterator>			//destory的泛型，接受两个ForwardIterator类型
inline void destory(ForwardIterator first, ForwardIterator last)
{
	for (; first < last; ++first)
	{
		destory(&*first);
	}
}