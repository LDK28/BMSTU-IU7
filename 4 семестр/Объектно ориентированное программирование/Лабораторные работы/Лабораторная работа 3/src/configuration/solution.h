#ifndef SOLUTION_H
#define SOLUTION_H

#include "load/loadcreator.h"
#include <map>


class Solution
{
public:
    Solution() = default;
    ~Solution() = default;

    void registrate(int id, shared_ptr<LoadCreator> creator);
    shared_ptr<LoadCreator> get_creator(int id) const;

private:
    using callback_map = map<size_t, std::shared_ptr<LoadCreator>>;
    callback_map callback;
};

#endif // SOLUTION_H
