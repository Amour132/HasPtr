#include <iostream>
#include <string>

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
class AutoPtr
{
  public:
    AutoPtr(T* ptr = NULL):_ptr(ptr)
    {}

    AutoPtr(AutoPtr<T>& ap):_ptr(ap._ptr)
    {
      ap._ptr = NULL;
    }

    AutoPtr<T>& operator=(AutoPtr<T>& ap)
    {
      if(this != &ap)
      {
        if(_ptr)
        {
          delete _ptr;
        }
        _ptr = ap._ptr;
        ap._ptr = NULL;
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

    ~AutoPtr()
    {
      delete _ptr;
    }

  private:
    T* _ptr;
};

int main()
{
  AutoPtr<Person> ap(new Person);
  ap->_age = 18;
  ap->_name = "djh";
  cout << (*ap)._name << ":" << (*ap)._age << endl;
  return 0;
}
