//* bad library
//* utility
//* logger - for logging things

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/util/LoggerConst.h"

//* stl
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace Lib1104A
{
    namespace Utility {
        class Logger {
            public:
                explicit Logger(bool p_PrintToStdout = true);
                Logger(const Logger&) = delete; // delete copy constr.
                Logger& operator=(const Logger&) = delete;  // delete assign. constr.

                void Log(std::string p_LogData);
                void PrintTask(void);


            private:
                pros::Task m_LogTask;
                pros::Mutex m_BufferMutex;

                std::queue<std::string> m_Buffer;
                std::ofstream m_FileOutputStream;
                bool m_PrintToStdout;

        };
    }
}