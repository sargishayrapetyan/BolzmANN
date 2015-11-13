#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>

template<typename Type>
struct Vector : std::vector<Type>
{
    using My = Vector;

    bool contains(const Type& value)
    {
        return (std::find(My::begin(), My::end(), value) != My::end());
    }
};

template<typename Type>
struct List : std::list<Type>
{
    using My = List;

    bool contains(const Type& value)
    {
        return (std::find(My::begin(), My::end(), value) != My::end());
    }
};

template<typename Type>
struct Map : std::map<Type>
{
    using My = Map;

    bool contains(const Type& value)
    {
        return (std::find(My::begin(), My::end(), value) != My::end());
    }
};

template<typename Type>
struct Set : std::set<Type>
{
    using My = Set;

    bool contains(const Type& value)
    {
        return (std::find(My::begin(), My::end(), value) != My::end());
    }
};

template<typename Type>
struct Stack : std::stack<Type>
{
    using My = Stack;

    bool contains(const Type& value)
    {
        return (std::find(My::begin(), My::end(), value) != My::end());
    }
};

template<typename Type>
struct Queue : std::queue<Type>
{
    using My = Queue;

    bool contains(const Type& value)
    {
        return (std::find(My::begin(), My::end(), value) != My::end());
    }
};


#endif // LIBRARY_H

