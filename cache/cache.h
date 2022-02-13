#include <cstddef>
#include <unordered_map>
#include <memory>

template <typename KeyT, typename ValueT, typename EvictionStrategyT>
class Cached_Key_Value_StorageT {   
public:
    Cached_Key_Value_StorageT(size_t capacity)    
    {
        key_value_data.reserve(capacity);
        eviction_strategy = std::make_unique<EvictionStrategyT>();
    }

    void   Put(KeyT key, ValueT value)
    {   
        if (key_value_data.size() == max_count) {
            auto key = eviction_strategy->FreeElementSpace();
            key_value_data.erase(key);
        }

        if (Contains(key)) {                   
            eviction_strategy->UpdateData(key, value);
        } else {
            eviction_strategy->InsertData(key, value);
        }
        key_value_data[key] = value;
    }

    ValueT Get(KeyT key)
    {
        if (Contains(key)) {
            eviction_strategy->UpdateDataHit(key);
        }        
        return key_value_data.at(key);
    }

    void   Delete(KeyT key)
    {
        if (Contains(key)) {
            eviction_strategy->DeleteElement(key);
            key_value_data.erase(key);
        }
    }

    bool Contains(KeyT key) 
    {
        return (key_value_data.find(key) != std::end(key_value_data));
    }

private:
    std::unordered_map<KeyT, ValueT>   key_value_data;
    unsigned int                       max_count;
    std::unique_ptr<EvictionStrategyT> eviction_strategy;
};
