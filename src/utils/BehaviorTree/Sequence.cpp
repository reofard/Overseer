#include "utils/BehaviorTree/Sequence.hpp"

Status Sequence::tick()
{
    for (auto& child : children)
    {
        Status status = child->tick();
        if (status != Status::SUCCESS)
        {
            return status; // FAILURE나 RUNNING 반환
        }
    }
    return Status::SUCCESS;
}