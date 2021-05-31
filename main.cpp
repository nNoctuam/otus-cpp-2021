#include "include/app.h"
#include "include/controller.h"
#include "include/core/document.h"
#include "include/core/graphics.h"
#include "include/core/gui.h"
#include "include/service/service.h"
#include <memory>

void buildMenu(Application& app) {
  auto menu = std::make_shared<Menu>();

  std::shared_ptr<MenuEntry> saveMenuEntry = std::make_shared<SaveMenuEntry>(app);
  menu->AddEntry(saveMenuEntry);

  app.AddElement(menu);
}

int main(int, char **) {
  auto canvas = new Canvas();
  auto document = new Document(*canvas);
  auto app = new Application(*document);
  buildMenu(*app);

  return 0;
}
