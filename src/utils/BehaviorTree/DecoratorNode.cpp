#include <memory>
#include <functional>
#include "utils/BehaviorTree/DecoratorNode.hpp"

Status DecoratorNode::tick()
{
    return child ? child->tick() : Status::FAILURE;
}

Status ConditionDecorator::tick()
{
    if (condition())
    {
        return DecoratorNode::tick(); // 자식 노드 실행
    }
    return Status::FAILURE; // 조건이 충족되지 않으면 실패
}