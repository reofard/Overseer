#include <memory>
#include "utils/BehaviorTree/CompositeNode.hpp"

class Sequence : public CompositeNode
{
public:
    Status tick() override;
};