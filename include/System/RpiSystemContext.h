#pragma once

#include <memory>
#include <utility>

#include "Utils/BasicFdOps.h"

namespace System
{
class RpiSystemContext
{
public:
	Utils::FdOps *GetFdOps();

private:
	Utils::BasicFdOps m_basicFdOps;
};
} // namespace System
