#pragma once
template<class T>				//�����������������ָ����ָ�Ķ�������
inline void destory(T* pointer)
{
	pointer->~T();
}

template <class T1,class T2>		//��p��ָ�����ϴ���һ�����󣬲���value��ʼ����
inline void construct(T1* p, const T2& value)
{
	new (p) T1(value);
}

template<class ForwardIterator>			//destory�ķ��ͣ���������ForwardIterator����
inline void destory(ForwardIterator first, ForwardIterator last)
{
	for (; first < last; ++first)
	{
		destory(&*first);
	}
}