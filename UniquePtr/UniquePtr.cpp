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
class UniquePtr
{
  public:
    UniquePtr(T* ptr = NULL):_ptr(ptr)
    {}

    T& operator*()
    {
      return *_ptr;
    }

    T* operator->()
    {
      return _ptr;
    }

    ~UniquePtr()
    {
      if(_ptr)
      {
        delete _ptr;  
      }
    }
  private:
    UniquePtr(UniquePtr<T> const&);
    UniquePtr & operator=(UniquePtr<T> const&);

    //C++11
    //UniquePtr(UniquePtr<T> const&) = delete;
    //UniquePtr & operator=(UniquePtr<T> const&) = delete;

  private:
    T* _ptr;
};

int main()
{
  UniquePtr<Person> up(new Person);
  up->_age = 18;
  up->_name = "djh";
  cout << (*up)._name << ":" << (*up)._age << endl;
  return 0;
}
