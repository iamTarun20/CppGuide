#include "cache_manager.h"
#include <iostream>

using namespace std;

// =========================================================
// CONSTRUCTOR: Setting up the Library Table (RAM)
// =========================================================
CacheManager::CacheManager(int size, FileStorageManager* dm) {
    total_frames = size;
    disk_manager = dm;

    // RAM me physical slots (baltiyan) banayi
    ram_blocks_array = new MemoryBlock[total_frames];

    // Shuru me saare slots khali hain, toh free list me daal do
    for (int i = 0; i < total_frames; i++) {
        free_slots_list.push_back(i);
    }
}

CacheManager::~CacheManager() {
    delete[] ram_blocks_array;
}

// =========================================================
// FUNCTION 1: FETCH BLOCK (Disk se RAM me data laana)
// =========================================================
MemoryBlock* CacheManager::FetchBlock(int target_block_id) {

    // STEP 1: Cache Hit (Agar RAM me pehle se hai)
    if (disk_to_ram_map.find(target_block_id) != disk_to_ram_map.end()) {
        int slot = disk_to_ram_map[target_block_id];

        // LRU update: Sabse aage le aao
        lru_tracking_list.remove(slot);
        lru_tracking_list.push_front(slot);

        // Lock lagao (Thread reference badhao)
        ram_blocks_array[slot].IncrementThreadReference();
        return &ram_blocks_array[slot];
    }

    // STEP 2 & 3: Cache Miss & LRU Eviction
    int target_slot = -1;

    if (!free_slots_list.empty()) {
        target_slot = free_slots_list.front();
        free_slots_list.pop_front();
    } else {
        // RAM full hai, peeche se "bakra" (victim) dhundho
        for (auto it = lru_tracking_list.rbegin(); it != lru_tracking_list.rend(); ++it) {
            int candidate = *it;
            // Sirf wahi evict hoga jise abhi koi aur query read na kar rahi ho
            if (ram_blocks_array[candidate].GetActiveThreadReferences() == 0) {
                target_slot = candidate;

                int old_id = ram_blocks_array[target_slot].GetBlockIdentifier();

                // Agar data modify hua tha, toh disk par save karo
                if (ram_blocks_array[target_slot].HasUnsavedChanges()) {
                    disk_manager->WriteBlockToDisk(old_id, ram_blocks_array[target_slot].GetRaw_Data());
                }

                // Purane records delete karo
                disk_to_ram_map.erase(old_id);
                lru_tracking_list.remove(target_slot);
                break;
            }
        }

        // Agar saare slots busy hain toh RAM crash hone se bachane ke liye NULL bhej do
        if (target_slot == -1) return nullptr;
    }

    // STEP 4 & 5: Load new data & Update records
    ram_blocks_array[target_slot].ResetBlock();
    disk_manager->ReadBlockFromDisk(target_block_id, ram_blocks_array[target_slot].GetRaw_Data());

    ram_blocks_array[target_slot].SetBlockIdentifier(target_block_id);
    ram_blocks_array[target_slot].IncrementThreadReference(); // Naya lock lagao

    disk_to_ram_map[target_block_id] = target_slot;
    lru_tracking_list.push_front(target_slot);

    return &ram_blocks_array[target_slot];
}


// =========================================================
// FUNCTION 2: RELEASE BLOCK (Mera kaam ho gaya, lock hatao)
// =========================================================
void CacheManager::ReleaseBlock(int block_id, bool is_modified) {
    // Check karo ki block actual me RAM me hai ya nahi
    if (disk_to_ram_map.find(block_id) != disk_to_ram_map.end()) {
        int slot = disk_to_ram_map[block_id];

        // Lock hata do (Thread count -1)
        ram_blocks_array[slot].DecrementThreadReference();

        // Agar user ne data change kiya tha, toh mark as dirty
        if (is_modified) {
            ram_blocks_array[slot].MarkAsUnsaved(true);
        }
    }
}


// =========================================================
// FUNCTION 3: CREATE NEW BLOCK (Naya data dalne ke liye)
// =========================================================
MemoryBlock* CacheManager::CreateNewBlock(int& out_new_block_id) {
    // 1. Ek naya fresh ID socho (Real DB me disk manager batata hai next ID)
    static int next_available_id = 1000;
    out_new_block_id = next_available_id++;

    // 2. RAM me jagah banao (Exact same LRU eviction logic as FetchBlock)
    int target_slot = -1;

    if (!free_slots_list.empty()) {
        target_slot = free_slots_list.front();
        free_slots_list.pop_front();
    } else {
        for (auto it = lru_tracking_list.rbegin(); it != lru_tracking_list.rend(); ++it) {
            int candidate = *it;
            if (ram_blocks_array[candidate].GetActiveThreadReferences() == 0) {
                target_slot = candidate;
                int old_id = ram_blocks_array[target_slot].GetBlockIdentifier();
                if (ram_blocks_array[target_slot].HasUnsavedChanges()) {
                    disk_manager->WriteBlockToDisk(old_id, ram_blocks_array[target_slot].GetRaw_Data());
                }
                disk_to_ram_map.erase(old_id);
                lru_tracking_list.remove(target_slot);
                break;
            }
        }
        if (target_slot == -1) return nullptr;
    }

    // 3. Khali balti me naya sticker lagao (Disk se kuch read nahi karna, kyuki data naya hai)
    ram_blocks_array[target_slot].ResetBlock();
    ram_blocks_array[target_slot].SetBlockIdentifier(out_new_block_id);
    ram_blocks_array[target_slot].IncrementThreadReference(); // Lock it

    // 4. Update trackers
    disk_to_ram_map[out_new_block_id] = target_slot;
    lru_tracking_list.push_front(target_slot);

    return &ram_blocks_array[target_slot];
}