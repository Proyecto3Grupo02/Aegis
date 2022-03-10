
#pragma once

template<typename T>
class Singleton
{

public:
    static T* getInstance();
   static void deleteInstance();
protected:
    static T* mInstance_;
    Singleton();
    ~Singleton();
private:
    //    //if it's called here is because there are multiple instances so we have to delete
    Singleton(Singleton const&) = delete; //copy
    Singleton& operator=(Singleton const&) = delete; //operator =



};

template<typename T>
typename T* Singleton<T>::mInstance_ = nullptr;

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
inline void Singleton<T>::deleteInstance() {
    delete Singleton<T>::mInstance_;
    Singleton<T>::mInstance_ = nullptr;

}

template<typename T>
T* Singleton<T>::getInstance()
{
    if (Singleton<T>::mInstance_ == nullptr)
    {
        Singleton<T>::mInstance_ = new T();
    }

    return Singleton<T>::mInstance_;
}
