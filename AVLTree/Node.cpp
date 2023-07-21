#include "Node.h"

Node:: Node(string data){
    this-> data = data;
    count = 1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
