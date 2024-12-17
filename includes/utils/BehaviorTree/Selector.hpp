#include <memory>
#include "utils/BehaviorTree/CompositeNode.hpp"

class Selector : public CompositeNode
{
public:
    void tick() override;
};