#include <memory>

#include "utils/BehaviorTree/CompositeNode.hpp"

void CompositeNode::addChild(std::shared_ptr<BTNode> child)
{
    children.push_back(child);
}