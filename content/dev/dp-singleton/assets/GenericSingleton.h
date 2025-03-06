template <class T>
class GenericSingleton  {
public:
  static T *Instance() {
    if (instance == nullptr)
      instance = new T;
    return instance;
  }
  static void Delete() {
    delete instance;
    instance = nullptr;
  }
protected:
  GenericSingleton() {}
private:
  static T *instance;
};

template<class T>
T *GenericSingleton<T>::instance = nullptr;