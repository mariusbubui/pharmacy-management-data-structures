#include "RBNode.h"
#include <string>
#include <sstream>

using std::string;
using std::ostringstream;

RBNode* RBNode::Nil = nullptr;

RBNode::~RBNode()
{
    if (this != Nil)
    {
        if (left != Nil)
            delete left;
        if (right != Nil)
            delete right;
    }
}
