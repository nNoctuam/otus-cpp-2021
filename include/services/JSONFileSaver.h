#pragma once
#include "../core/Data.h"
#include "../core/services/IDataSaver.h"

namespace services {

class JSONFileSaver : public core::services::IDataSaver<core::JSONData> {};

} // namespace services