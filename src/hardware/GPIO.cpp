/*
    Copyright (C) 2014-2017 Leosac

    This file is part of Leosac.

    Leosac is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leosac is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "hardware/GPIO.hpp"

namespace Leosac
{
namespace Hardware
{

GPIO::GPIO()
    : id_(0)
    , version_(0)
{
}

const std::string &GPIO::name() const
{
    return name_;
}

void GPIO::name(const std::string &name)
{
    name_ = name;
}

GPIOId GPIO::id() const
{
    return id_;
}

uint64_t GPIO::version() const
{
    return version_;
}
}
}