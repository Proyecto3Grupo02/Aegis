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
