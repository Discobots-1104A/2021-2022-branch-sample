//* bad library
//* utility
//* logger - for logging things

//? is this a bad way of logging things? yeah
//? do i particularly care? no
//? why? it's a dumb robotics competition that's why
//? should work to debug code and stuff
//? ~ Marco

//* headers
#include "lib/util/Logger.h"

namespace Lib1104A {
    namespace Utility {
        Logger::Logger(bool p_PrintToStdout) : 
            m_PrintToStdout {p_PrintToStdout},
            m_LogTask {pros::Task(std::bind(&Logger::PrintTask, this))},
            m_BufferMutex {pros::Mutex()},
            m_FileOutputStream {std::ofstream(
                //? less terribleness to make the file name
                []()->std::string {
                    auto v_Time = std::time(nullptr);
                    auto v_GMTime = *std::gmtime(&v_Time);
                    std::ostringstream v_Out;
                    v_Out << "/usd/Log_" << std::put_time(&v_GMTime, "%Y-%b-%d_%H-%M-%S") << ".txt";
                    return v_Out.str();
                }().c_str()
            )}
            {}

        void Logger::Log(std::string p_LogData) {
            //? mutex lock and push onto queue
            m_BufferMutex.take(TIMEOUT_MAX);
            m_Buffer.push(p_LogData);
            m_LogTask.notify();
            m_BufferMutex.give();
        }

        void Logger::PrintTask(void) {
            //? kinda infinite task loop to print logs to file and stdout
            while (!pros::competition::is_disabled() && m_LogTask.notify_take(0, TIMEOUT_MAX)) {
                if (m_FileOutputStream.is_open())
                    m_FileOutputStream << m_Buffer.front();
                if (m_PrintToStdout)
                    std::cout << m_Buffer.front();
                m_Buffer.pop();

                m_LogTask.delay(500);
            }
        }
    }
}