#include <string>

#include "GenericSingleton.h"

class SceneManager: public GenericSingleton<SceneManager> {
private:
  friend class GenericSingleton<SceneManager>;
  SceneManager() {}
public:
  void LoadScene(std::string const &name) {}
private:
  std::string defaultScene = "Start";
};