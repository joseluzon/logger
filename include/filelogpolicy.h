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

#ifndef FILELOGPOLICY_H
#define FILELOGPOLICY_H

#include <fstream>
#include <memory>

#include "logpolicy.h"

namespace jluzoncpp {
namespace logger {

class FileLogPolicy : public LogPolicy
{
public:
    FileLogPolicy();

    virtual ~FileLogPolicy() override;

    void open(const std::string& name) noexcept(false) override;

    void close() override;

    void write(const std::string& msg) override;

private:
    // Hidden:
    FileLogPolicy(const FileLogPolicy& other);
    FileLogPolicy& operator = (const FileLogPolicy& other);
    //

    std::unique_ptr<std::ofstream> m_outStream;
};

} // logger
} // jluzoncpp

#endif // FILELOGPOLICY_H
