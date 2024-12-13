#include "utils/BehaviorTree/Selector.hpp"

Status Selector::tick()
{
    for (auto& child : children)
    {
        Status status = child->tick();
        if(status != Status::FAILURE)
        {
            return status;
        }
    }
    return Status::FAILURE;
}