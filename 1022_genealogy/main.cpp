#include <iostream>
#include <vector>
#include <memory>

class Martian {
public:
    int id;
    bool hasSpoken = false;
    std::vector<std::weak_ptr<Martian>> parents;
    std::vector<std::shared_ptr<Martian>> children;

    Martian(int id) : id(id) {}

    void speak() {
        hasSpoken = true;
        std::cout << id << " ";
    }

    void makeParentsSpeak() {
        for (const auto &parent : parents) {
            if (parent.lock()->hasSpoken) {
                continue;
            }
            parent.lock()->makeParentsSpeak();
            parent.lock()->speak();
        }
    }
};

int main() {
    // region prepare graph
    std::vector<std::shared_ptr<Martian>> martians;

    int councilSize;
    std::cin >> councilSize;
    martians.reserve(councilSize);

    for (int i = 1; i <= councilSize; i++) {
        martians.push_back(std::make_shared<Martian>(i));
    }
    // endregion

    // region fill graph
    for (int i = 1; i <= councilSize; i++) {
        int child;
        while (true) {
            std::cin >> child;
            if (child == 0) {
                break;
            }
            martians.at(i - 1)->children.push_back(martians.at(child - 1));
            martians.at(child - 1)->parents.push_back(martians.at(i - 1));
        }
    }
    // endregion

    // since there might be unrelated martians we have to check each one,
    // not just go by the single tree
    for (const auto &martian : martians) {
        if (martian->hasSpoken) {
            continue;
        }
        martian->makeParentsSpeak();
        martian->speak();
    }

    return 0;
}
