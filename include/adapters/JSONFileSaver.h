#pragma once
#include "../core/Data.h"
#include "../services/IDataSaver.h"

namespace services {

class JSONFileSaver : public services::IDataSaver<core::JSONData> {};

} // namespace services