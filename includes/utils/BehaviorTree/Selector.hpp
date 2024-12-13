#include <memory>
#include "utils/BehaviorTree/CompositeNode.hpp"

class Selector : public CompositeNode
{
public:
    Status tick() override;
};