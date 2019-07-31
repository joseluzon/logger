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

#include "filelogpolicy.h"

jluzoncpp::logger::FileLogPolicy::FileLogPolicy() :
    m_outStream( new std::ofstream )
{

}

jluzoncpp::logger::FileLogPolicy::~FileLogPolicy()
{
    if (m_outStream)
        close();
}

void jluzoncpp::logger::FileLogPolicy::open(const std::string& name)
{
    std::string fileName(name + ".log");
    m_outStream->open(fileName.c_str(), std::ios_base::binary|std::ios_base::out);
    if (!m_outStream->is_open())
    {
        throw(std::runtime_error("LOGGER: Unable to open an output stream"));
    }
}

void jluzoncpp::logger::FileLogPolicy::close()
{
    if (m_outStream)
        m_outStream->close();
}

void jluzoncpp::logger::FileLogPolicy::write(const std::string& msg)
{
    (*m_outStream) << msg << std::endl;
}
