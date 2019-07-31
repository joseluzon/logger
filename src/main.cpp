// code-licenser auto-generated license header

// Copyright (C) 2019 Jose Luzón Martín
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>

#include "logger.h"
#include "stdoutlogpolicy.h"
#include "filelogpolicy.h"

static jluzoncpp::logger::Logger< jluzoncpp::logger::StdOutLogPolicy > log_stdout( "stdout", jluzoncpp::logger::LoggerLevel::Debug );
static jluzoncpp::logger::Logger< jluzoncpp::logger::FileLogPolicy > log_file( "file", jluzoncpp::logger::LoggerLevel::Info );

int main()
{
    for (int i=0; i<10000; ++i)
    {
        LOG_FATAL(log_stdout, "Log Fatal", "Log Fatal 2");
        LOG_ERROR(log_stdout, "Log Error");
        LOG_WARNING(log_stdout, "Log Warning");
        LOG_INFO(log_stdout, "Log info");
        LOG_TRACE(log_stdout, "Log Trace");
        LOG_DEBUG(log_stdout, "Log Debug");

        LOG_FATAL(log_file, "Log Fatal", "Log Fatal 2");
        LOG_ERROR(log_file, "Log Error");
        LOG_WARNING(log_file, "Log Warning");
        LOG_INFO(log_file, "Log info");
        LOG_TRACE(log_file, "Log Trace");
        LOG_DEBUG(log_file, "Log Debug");
    }

    return 0;
}
