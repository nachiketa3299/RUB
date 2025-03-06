class Singleton {
public:
  // 접근 지점을 제공하는 메서드
  static Singleton *Instance() {
    if (instance == nullptr) 
      instance = new Singleton();
    return instance;
  }
protected:
  Singleton() {}
private:
  static Singleton *instance;
};