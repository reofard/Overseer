#include <functional>
#include <memory>
#include "utils/BehaviorTree/Node.hpp"

class BTNode;
class ActionNode : public BTNode
{
private:
    std::function<Status()> action;

public:
    explicit ActionNode(std::function<Status()> action) : action(std::move(action)) { }

    Status tick() override;
};