#include "utils/BehaviorTree/Selector.hpp"

void Selector::tick()
{
    for (auto& child : children)
    {
        child->tick();
    }
    return;
}