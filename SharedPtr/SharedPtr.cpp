#include <iostream>
#include <string>
#include <mutex>
#include <thread>

using std::cout;
using std::endl;

class Person
{
  public:
    Person()
    {
      cout << "Person" << endl;
    }

    ~Person()
    {
      cout << "~Person" << endl;
    }

    std::string _name;
    int _age; 
};

template<class T>
class SharedPtr
{
  public:
    SharedPtr(T* ptr = NULL):_ptr(ptr),_pRefCount(new int(1)),_pMutex(new std::mutex)
    {
      if(_ptr == NULL)
      {
        _pRefCount = 0;
      }
    }

    SharedPtr(SharedPtr<T>& sp):_ptr(sp._ptr),_pRefCount(sp._pRefCount),_pMutex(sp._pMutex)
    {
      if(_ptr)
      {
        AddRefCount();
      }
    }

    SharedPtr<T>& operator=(SharedPtr<T>& sp)
    {
      if(_ptr != sp._ptr)
      {
        Release();
        _ptr = sp._ptr;
        _pRefCount = sp._pRefCount;
        _pMutex = sp._pMutex;
        if(_ptr)
        {
          AddRefCount();
        }
      }
      return *this;
    }

    T& operator*()
    {
      return *_ptr;
    }

    T* operator->()
    {
      return _ptr;
    }

    int UseCount()
    {
      return *_pRefCount;
    }

    T* Get()
    {
      return _ptr;
    }

    int AddRefCount()
    {
      _pMutex->lock();
      (*_pRefCount)++;
      _pMutex->unlock();
      return *_pRefCount;
    }

    int SubRefCount()
    {
      _pMutex->lock();
      (*_pRefCount)--;
      _pMutex->unlock();                                                     
      return *_pRefCount;  
    }

    ~SharedPtr()
    {
      Release();
    }
  private:
    void Release()
    {
      if(_ptr && SubRefCount() == 0)
      {
        delete _ptr;
        delete _pRefCount;
      }
    }

  private:
    T* _ptr;
    int* _pRefCount;
    std::mutex*  _pMutex;

};

int main()
{
  SharedPtr<Person> sp(new Person);
  sp->_age = 18;
  sp->_name = "djh";
  cout << (*sp)._name << ":" << (*sp)._age << endl;
  return 0;
}
