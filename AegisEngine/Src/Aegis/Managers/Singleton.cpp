
#include "Singleton.h"


template<typename T>
Singleton<T>::Singleton()
{
	Singleton::mInstance_ = static_cast<T*>(this);
}

template<typename T>
inline Singleton<T>::~Singleton()
{
}

template<typename T>
T* Singleton<T>::getInstance()
{
	if (Singleton<T>::mInstance_ == nullptr)
	{
		Singleton<T>::mInstance_ = new T();
	}

	return Singleton<T>::instance;
}

template<typename T>
void Singleton<T>::deleteInstance(){
    delete Singleton<T>::mInstance_;
    Singleton<T>::mInstance_=nullptr;
    
}

