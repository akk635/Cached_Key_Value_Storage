#include <iostream>
#include <string>

#include "../cache/cache.h"
#include "../cache/lru_cache_eviction.h"

using namespace std;

int main() {
    Cached_Key_Value_StorageT<string,string,LRU_Key_Value_Cache_Eviction<string,string>>
        cached_key_values(5);

    cached_key_values.Put("Hello","World");
    cached_key_values.Put("Enjoy the process", "Involvement and committment");

    std::cout << cached_key_values.Get("Hello") << std::endl;
    std::cout << cached_key_values.Get("Enjoy the process") << std::endl;

    cached_key_values.Delete("Hello");    

    return 0;
}