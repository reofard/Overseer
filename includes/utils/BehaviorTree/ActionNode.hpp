#include <functional>
#include <memory>
#include "utils/BehaviorTree/Node.hpp"

class BTNode;
class ActionNode : public BTNode
{
private:
    std::function<void()> action;

public:
    explicit ActionNode(std::function<void()> action) : action(std::move(action)) { }

    void tick() override;
};