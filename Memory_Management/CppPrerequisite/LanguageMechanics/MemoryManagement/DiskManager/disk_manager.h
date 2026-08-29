#pragma once

#include <cstddef>
#include <cstdint>

using page_id_t = std::uint32_t;

constexpr std::size_t PAGE_SIZE = 4096;

class DiskManager {
public:
    void ReadPage(page_id_t page_id, char* buffer);
    void WritePage(page_id_t page_id, const char* buffer);

    page_id_t AllocatePage();
    void DeallocatePage(page_id_t page_id);

private:
    std::uint64_t PageOffset(page_id_t page_id);
};