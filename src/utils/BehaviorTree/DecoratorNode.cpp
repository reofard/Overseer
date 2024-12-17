#include <memory>
#include <functional>
#include "utils/BehaviorTree/DecoratorNode.hpp"

void DecoratorNode::tick()
{
    if(child)
    {
        child->tick();
    }
    return;
}

void ConditionDecorator::tick()
{
    if (condition())
    {
        DecoratorNode::tick();
    }
    return;
}