#include "System/RpiSystemContext.h"

namespace System
{
Utils::FdOps *RpiSystemContext::GetFdOps()
{
		return m_basicFdOps;	
}
} // namespace System
