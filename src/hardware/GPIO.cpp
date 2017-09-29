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
#include "exception/ModelException.hpp"

namespace Leosac
{
namespace Hardware
{

GPIO::GPIO()
    : Device(DeviceClass::GPIO)
    , number_(0)
    , direction_(Direction::In)
    , default_value_(false)
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

uint16_t GPIO::number() const
{
    return number_;
}

void GPIO::number(uint16_t number)
{
    number_ = number;
}

GPIO::Direction GPIO::direction() const
{
    return direction_;
}

void GPIO::direction(GPIO::Direction direction)
{
    direction_ = direction;
}

bool GPIO::default_value() const
{
    return default_value_;
}

void GPIO::default_value(bool default_value)
{
    default_value_ = default_value;
}

void GPIO::validation_callback(odb::callback_event e, odb::database &) const
{
    if (e == odb::callback_event::post_persist ||
        e == odb::callback_event::post_update)
    {
        if (name().empty())
        {
            throw ModelException("data/attributes/name",
                                 "GPIO name must be non empty");
        }
    }
}
}
}
