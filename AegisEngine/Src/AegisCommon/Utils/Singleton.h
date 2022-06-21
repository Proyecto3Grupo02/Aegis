#pragma once
#ifndef SINGLETON_H 
#define SINGLETON_H

template<typename T>
class Singleton
{
public:
	static T* getInstance();
	static bool tryDeleteInstance();
	/// <summary>
	/// Intenta crear una nueva instancia del singleton de tipo T, si no existe se crea y se devuelve true
	/// Si ya existía se devuelve false. Para acceder a la instancia hay que usar Singleton<T>::getInstance
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename ...Ts>
	static bool tryCreateInstance(Ts... args)
	{
		if (Singleton<T>::mInstance_ == nullptr) {
			Singleton<T>::mInstance_ = new T(args...);
			return true;
		}

		return false;
	};

protected:
	static T* mInstance_;
	Singleton();
	virtual ~Singleton();

private:
	//    //if it's called here is because there are multiple instances so we have to delete
	Singleton(Singleton const&) = delete; //copy
	Singleton& operator=(Singleton const&) = delete; //operator =
};

template<typename T>
typename T* Singleton<T>::mInstance_ = nullptr;

template<typename T>
Singleton<T>::Singleton() {
	Singleton::mInstance_ = static_cast<T*>(this);
}

template<typename T>
inline Singleton<T>::~Singleton() {

}

/// <summary>
/// Si hay una instancia creada, la borra y devuelve true, en caso contrario
/// no hace nada y devuelve false
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
inline bool Singleton<T>::tryDeleteInstance() {
	if (Singleton<T>::mInstance_ == nullptr)
		return false;
	delete Singleton<T>::mInstance_;
	Singleton<T>::mInstance_ = nullptr;
	return true;
}

/// <summary>
/// Devuelve la instancia del Singleton, esta puede ser nullptr si no se ha creado previamente
/// </summary>
/// <typeparam name="T">Tipo de instancia</typeparam>
/// <returns></returns>
template<typename T>
T* Singleton<T>::getInstance() {
	return Singleton<T>::mInstance_;
}

#endif //