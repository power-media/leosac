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

#pragma once

#include "modules/BaseModule.hpp"
#include <tools/db/db_fwd.hpp>

namespace Leosac
{
namespace Module
{
namespace WebSockAPI
{

/**
 * Those are general status code that apply to all outgoing
 * message.
 */
enum class StatusCode
{
    /**
     * Indicate that the request's processing went well.
     */
    SUCCESS = 0x00,

    /**
     * A failure for an unknown reason.
     */
    GENERAL_FAILURE = 0x01,

    /**
     * The websocket connection is not allowed to make the
     * requested API call.
     */
    PERMISSION_DENIED = 0x02,

    /**
     * The websocket connection is rate limited, and it already
     * sent too many packets.
     */
    RATE_LIMITED = 0x03,

    /**
     * The source packet was malformed.
     */
    MALFORMED = 0x04,

    /**
     * The API method (ie, message's type) does not exist.
     */
    INVALID_CALL = 0x05,
};

class MalformedMessage : public LEOSACException
{
  public:
    MalformedMessage()
        : LEOSACException("Message is malformed."){};
};

class PermissionDenied : public LEOSACException
{
  public:
    PermissionDenied()
        : LEOSACException("Permission denied."){};
};

class InvalidCall : public LEOSACException
{
  public:
    InvalidCall()
        : LEOSACException("Unknown message type."){};
};

class WebSockAPIModule : public BaseModule
{
  public:
    WebSockAPIModule(zmqpp::context &ctx, zmqpp::socket *pipe,
                     const boost::property_tree::ptree &cfg, CoreUtilsPtr utils);

    ~WebSockAPIModule() = default;

    virtual void run() override;

    /**
     * This module explicity expose CoreUtils to other
     * object in the module.
     */
    CoreUtilsPtr core_utils();

  private:
    /**
     * Port to bind the websocket endpoint.
     */
    uint16_t port_;
};
}
}
}