

#include "Singleton.h"


template<typename T>
T* Singleton<T>::getInstance()
{
	if (Singleton<T>::mInstance_ == nullptr)
	{
		Singleton<T>::mInstance_ = new T();
	}

	return Singleton<T>::instance;
}


