/*
    Copyright (C) 2014-2016 Islog

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

#include "api/MethodHandler.hpp"

using namespace Leosac;
using namespace Leosac::Module;
using namespace Leosac::Module::WebSockAPI;

json MethodHandler::process(const json &req)
{
    for (const auto &condition_group : conditions_)
    {
        bool success = false;
        for (const auto &condition : condition_group.first)
            success |= condition(req);

        if (!success)
            condition_group.second();
    }
    return process_impl(req);
}