//* bad library
//* utility
//* Async - Asynchronous execution

//* headers
#include "lib/util/Async.h"

namespace Lib1104A {
namespace Util {
Async::Async() : m_queue{}, m_task{std::bind(&Async::run_queue, this)} {
  // do nothing
}

Async::~Async() {
  m_task.remove();
  std::queue<async_func_t>().swap(m_queue);
}

Async &Async::add(std::function<void()> func, Misc::ms_t delay) {
  m_queue.push(std::make_pair(func, delay));
  m_task.notify();
  return *this;
}

void Async::run_queue() {
  while (!pros::competition::is_disabled() &&
         m_task.notify_take(0, TIMEOUT_MAX)) {
    while (!m_queue.empty()) {
      auto &func = m_queue.front().first;
      auto &delay = m_queue.front().second;
      if (delay > 0) {
        pros::Task::delay(delay);
      }
      func();
      m_queue.pop();
    }
  }
}
} // namespace Util
} // namespace Lib1104A