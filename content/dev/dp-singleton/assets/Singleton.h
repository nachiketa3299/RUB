class Singleton {
public:
  /// @brief 접근 지점을 제공하는 메서드
  static Singleton *Instance();
protected:
  Singleton() {}
private:
  static Singleton *instance;
};