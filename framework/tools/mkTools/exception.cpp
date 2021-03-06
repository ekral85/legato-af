//--------------------------------------------------------------------------------------------------
/**
 * @file exception.cpp
 *
 * Copyright (C) Sierra Wireless Inc. Use of this work is subject to license.
 */
//--------------------------------------------------------------------------------------------------

#include "mkTools.h"


namespace mk
{

//--------------------------------------------------------------------------------------------------
/**
 * Constructor
 */
//--------------------------------------------------------------------------------------------------
Exception_t::Exception_t
(
    const std::string& message  /// Description of the problem that was encountered.
)
//--------------------------------------------------------------------------------------------------
:   std::runtime_error(message)
//--------------------------------------------------------------------------------------------------
{
}


} // namespace mk
