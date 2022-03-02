
template<typename T>
class Singleton{

protected:
    static T* mInstance_;
    Singleton();
    ~Singleton();
public:
    inline static T* getInstance(){return mInstance_;}
    void deleteInstance();
private:
    //if it's called here is because there are multiple instances so we have to delete
     Singleton(Singleton const&)=delete; //copy
     Singleton& operator=(Singleton const&)=delete //operator =

   
};

template<typename T>
Singleton<T>::Singleton()
{
	Singleton::mInstance_ = static_cast<T*>(this);
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
