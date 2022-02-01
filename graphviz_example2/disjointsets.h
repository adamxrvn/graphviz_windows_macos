// DISJOINT SETS

#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

template<typename T>
class DisjointSets
{

public:

    void makeSet(T& x)
    {
        _parentVector[x] = x;
        _rankVector[x] = 0;
    }

    T& find(T& x)
    {
        return _parentVector[x] != x ? find(_parentVector[x]) : x;
    }

    void unionSet(T& x, T& y)
    {
        link(find(x),find(y));
    }

private:

    void link(T& x, T& y)
    {
        if(_rankVector[x] > _rankVector[y])
        {
            _parentVector[x] = y;
        }else
        {
            _parentVector[y] = x;
            if(_rankVector[x] == _rankVector[y])
                _rankVector[y]++;
        }
    }

    std::map<T,T> 	_parentVector;
    std::map<T,int> _rankVector;

};

#endif