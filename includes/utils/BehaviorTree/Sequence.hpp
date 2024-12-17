#include <memory>
#include "utils/BehaviorTree/CompositeNode.hpp"

class Sequence : public CompositeNode
{
public:
    void tick() override;
};