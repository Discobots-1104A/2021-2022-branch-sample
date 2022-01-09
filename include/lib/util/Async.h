//* bad library
//* utility
//* Async - Asynchronous execution

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/misc/Units.h"

//* stl
// #include <atomic>
#include <functional>
#include <queue>
#include <utility>

namespace Lib1104A {
namespace Utility {

using async_func_t = std::pair<std::function<void()>, Misc::ms_t>;

class Async {
public:
  //? ctor & dtor
  Async();
  ~Async();

  //? setters

  // add to queue
  Async &add(std::function<void()> func, Misc::ms_t delay);

  //? getters

  //? methods

private:
  //? members

  // queue
  std::queue<async_func_t> m_queue;
  // thread
  pros::Task m_task;

  //? private methods
  // run the queue
  void runQueue();
};

} // namespace Utility
} // namespace Lib1104A