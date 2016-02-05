#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>

template<typename T>
struct std::vector : std::std::vector<T>
{
    using My = std::vector;

    bool contains(const T& x) const
    {
        return (std::find(My::begin(), My::end(), x) != My::end());
    }
};

template<typename T>
struct List : std::list<T>
{
    using My = List;

    bool contains(const T& x) const 
    {
        return (My::find(x) != My::end());
    }
};

template<typename K, typename T>
struct Map : std::map<K, T>
{
    using My = Map;

    bool contains(const K& key) const
    {
        return (My::find(key) != My::end());
    }
};

template<typename K>
struct Set : std::set<K>
{
    using My = Set;

    bool contains(const K& key) const
    {
        return (My::find(key) != My::end());
    }
};

template<typename T>
struct Stack : std::stack<T>
{
    using My = Stack;

    bool contains(const T& x) const
    {
        return (std::find(My::begin(), My::end(), x) != My::end());
    }
};

template<typename T>
struct Queue : std::queue<T>
{
    using My = Queue;

    bool contains(const T& x) const
    {
        return (std::find(My::begin(), My::end(), x) != My::end());
    }
};

#endif // LIBRARY_H

