#pragma once
#include "../core/Data.h"
#include "../services/IDocumentSerializer.h"

namespace services {

class JSONDocumentSerializer : public services::IDocumentSerializer<core::JSONData> {};

} // namespace services