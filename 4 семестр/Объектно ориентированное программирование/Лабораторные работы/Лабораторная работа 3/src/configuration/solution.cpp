#include "solution.h"

void Solution::registrate(int id, shared_ptr<LoadCreator> creator)
{
    callback.insert(callback_map::value_type(id, creator));
}

shared_ptr<LoadCreator> Solution::get_creator(int id) const
{
    callback_map::const_iterator it = callback.find(id);
    if (it == callback.end())
    {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw file_exception(ctime(&timenow), __FILE__, typeid(Solution).name(), __FUNCTION__);
    }

    return it->second;
}
