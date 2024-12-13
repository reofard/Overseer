#include "utils/BehaviorTree/ActionNode.hpp"

Status ActionNode::tick()
{
    return action();
}