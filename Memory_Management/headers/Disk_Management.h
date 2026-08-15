#include<iostream>
#include<cstring>
using namespace std;

const int BlockSize = 4096;

class MemoryBlock { // Changed name for clarity
private: // DATA IS NOW SAFE
    char Raw_Data[BlockSize]; // Changed name from Raw_Size to Raw_Data
    bool unsavedChanges;
    int InterferenceThread;
    int blockIdentifier;

public: // FUNCTIONS TO ACCESS DATA
    MemoryBlock() {
        resetBlocks();
    }
    ~MemoryBlock() {}

    bool GetunsavedChanges() {
        return unsavedChanges;
    }
    int GetInterferenceThread() {
        return InterferenceThread;
    }
    int GetblockIdentifier() {
        return blockIdentifier;
    }
    char* GetRaw_Data() {
        return Raw_Data;
    }

    void SetBlockIdentifier(int i) {
        blockIdentifier = i; // Fixed variable scoping
    }

    void setUnsavedChanges(bool b) {
        unsavedChanges = b;
    }
    void ThreadIncrement() {
        InterferenceThread++;
    }
    void ThreadDecrement() {
        InterferenceThread--;
    }

    void resetBlocks() { // Added 'void'
        memset(Raw_Data, 0, BlockSize);
        unsavedChanges = false;
        InterferenceThread = 0;
        blockIdentifier = -1;
    }
};