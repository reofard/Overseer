#include <memory>
#include <functional>
#include "utils/BehaviorTree/Node.hpp"

// Decorator 노드

class DecoratorNode : public BTNode
{
protected:
    std::shared_ptr<BTNode> child;

public:
    explicit DecoratorNode(std::shared_ptr<BTNode> childNode)
        : child(std::move(childNode)) { }

    virtual Status tick() override;
};

// ConditionDecorator: 조건에 따라 자식 노드 실행
class ConditionDecorator : public DecoratorNode
{
private:
    std::function<bool()> condition;

public:
    ConditionDecorator(std::shared_ptr<BTNode> childNode, std::function<bool()> cond)
        : DecoratorNode(std::move(childNode)), condition(std::move(cond)) {}

    Status tick() override;
};