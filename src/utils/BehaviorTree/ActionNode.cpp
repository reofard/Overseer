#include "utils/BehaviorTree/ActionNode.hpp"

void ActionNode::tick()
{
    return action();
}