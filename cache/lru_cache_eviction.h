#include "../helper/doubly_linked_list.h"

template<typename KeyT, typename ValueT>
class LRU_Key_Value_Cache_Eviction {
public:
    void InsertData(KeyT key, ValueT value) 
    {
        key_list.insertBack(key);
    }

    void UpdateData(KeyT key, ValueT value)
    {
        key_list.deleteVal(key);
        key_list.insertBack(key);
    }

    void UpdateDataHit(KeyT key)
    {
        key_list.deleteVal(key);
        key_list.insertBack(key);
    }

    void DeleteElement(KeyT key)
    {
        key_list.deleteVal(key);
    }

    KeyT FreeElementSpace()
    {
        try {
            auto key = key_list.peakFront();
            key_list.deleteVal(key);
            return key;
        }
        catch(std::runtime_error& e) {
            throw e;
        }
    }

private:
    DoublyLinkedList<KeyT> key_list;
};