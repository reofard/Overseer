#include "utils/BehaviorTree/Sequence.hpp"

void Sequence::tick()
{
    for (auto& child : children)
    {
        child->tick();
    }
    return;
}