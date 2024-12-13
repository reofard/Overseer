#ifndef NODE_HPP
#define NODE_HPP

// 노드의 상태를 정의
enum class Status { SUCCESS, FAILURE, RUNNING };

class BTNode
{
public:
    virtual ~BTNode() = default;
    virtual Status tick() = 0;
};

#endif