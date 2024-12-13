#ifndef COMPOSITE_NODE_HPP
#define COMPOSITE_NODE_HPP

#include <vector>
#include "utils/BehaviorTree/Node.hpp"

class CompositeNode : public BTNode
{
protected:
    std::vector<std::shared_ptr<BTNode>> children;

public:
    void addChild(std::shared_ptr<BTNode> child);
};

#endif
