#pragma once
#include "../core/Data.h"
#include "../core/services/IDocumentSerializer.h"

namespace services {

class JSONDocumentSerializer : public core::services::IDocumentSerializer<core::JSONData> {};

} // namespace services