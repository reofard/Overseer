#ifndef NODE_HPP
#define NODE_HPP

class BTNode
{
public:
    virtual ~BTNode() = default;
    virtual void tick() = 0;
};

#endif