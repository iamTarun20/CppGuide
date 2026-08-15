//
// Created by Tarun kumar on 15-08-2026.
//

#pragma once //USING IT FOR TELLING COMPILER THAT IF THIS IS IMPORTED IN MULTIPLE FILES THEN CONSIDER IT SAME
#include <iostream>
#include <unordered_map>
#include<list>
#include "Disk_Management.h"

using namespace std;

class CacheManager {
private:
    int total_frames;
    MemoryBlock* ram_blocks_array;
    list<int> free_slots_list;
    unordered_map<int  , int> disk_to_ram_map;
    list<int> lru_tracking_list;

    Disk_Management* disk_manager;

public:
    CacheManager(int size , Disk_Management* dm);
    ~CacheManager();

    MemoryBlock* FetchBlock(int target_block_id);
    void ReleaseBlock(int block_id , bool is_modified);
    MemoryBlock* CreateNewBlock(int& out_new_block_id);
};