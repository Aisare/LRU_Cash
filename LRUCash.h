#ifndef LRUCASHH
#define LRUCASHH

#include <unordered_map>
#include <list>

/// <summary>
/// A template class that implements the operation of the LRU cache
/// </summary>
template<typename KeyType, typename ValueType>
class LRU_Cash
{
    /// <summary>
    /// aliases
    /// </summary>
    using Pair = std::pair<KeyType, ValueType>;
    using List = std::list<Pair>;
    using ListIterator = typename List::iterator;
    /// <summary>
    /// Cache size
    /// </summary>
    int capacity;
    /// <summary>
    /// Cache list data
    /// </summary>
    List cacheList;
    /// <summary>
    /// Cache map
    /// </summary>
    std::unordered_map<KeyType, ListIterator> cacheMap; 

    /// <summary>
    /// Move the requested or added item to the top of the list
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    void moveToFront(KeyType key, ValueType value)
    {
        cacheList.erase(cacheMap[key]); 
        cacheList.push_front({ key, value }); 
        cacheMap[key] = cacheList.begin(); 
    }

public:
    /// <summary>
    /// constructor of the class that sets the cache size
    /// </summary>
    /// <param name="cap">cache size</param>
    LRU_Cash(int cap) : capacity(cap) {}
    /// <summary>
    /// Get the value by key
    /// </summary>
    /// <param name="key">the key to the data</param>
    /// <returns>data or an empty constructor, if there is no data </returns>
    ValueType get(KeyType key)
    {
        const auto& findedItem = cacheMap.find(key);
        if (findedItem == cacheMap.end())
            return ValueType();
        ValueType value = (findedItem)->second->second;
        moveToFront(key, value);
        return value;
    }
    /// <summary>
    /// Add data with the specified key and the specified value
    /// </summary>
    /// <param name="key">specified key</param>
    /// <param name="value">specified value</param>
    void put(KeyType key, ValueType value)
    {
        if (cacheMap.find(key) != cacheMap.end())
        {
            moveToFront(key, value);
            return;
        }

        if (cacheList.size() == capacity)
        {
            KeyType lastKey = cacheList.back().first;
            cacheList.pop_back();
            cacheMap.erase(lastKey);
        }

        cacheList.push_front({ key, value });
        cacheMap[key] = cacheList.begin();
    }

};


#endif // !LRUCASHH

