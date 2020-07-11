#include "SystemInfo.h"

DxFeatures::Command::CmdSystemInfo DxFeatures::Command::CmdSystemInfo::s_instance = DxFeatures::Command::CmdSystemInfo();

std::stringstream DxFeatures::Command::CmdSystemInfo::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return empty stream if already called
    if (m_bCalled)
        return ss;

    // Print header
    ss << "[SYSINFO]" << std::endl;

    // === Windows Processor Info ===
    // Create buffer vars
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* procInfoBuffer = NULL;
    DWORD bufferLength = 0;
   
    // Query buffer length
    if (GetLogicalProcessorInformation(procInfoBuffer, &bufferLength) == TRUE) {
        // Log error and return
        ss << "Unexpected return of TRUE from system call GetLogicalProcessorInformation(...) with null parameter" << std::endl << std::endl;
        return ss;
    }

    // Allocate buffer
    procInfoBuffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)malloc(bufferLength);

    // Fill buffer
    if (GetLogicalProcessorInformation(procInfoBuffer, &bufferLength) == FALSE) {
        // Log error and return
        ss << "Unexpected return of FALSE from system call GetLogicalProcessorInformation(...) with sufficient buffer" << std::endl << std::endl;
        free(procInfoBuffer);
        return ss;
    }

    // Data to read
    DWORD logicalProcessorCount = 0;
    UINT numaNodeCount = 0;
    UINT processorCoreCount = 0;
    UINT processorL1CacheCount = 0;
    UINT processorL2CacheCount = 0;
    UINT processorL3CacheCount = 0;
    UINT processorPackageCount = 0;
    CACHE_DESCRIPTOR* ptrCache = NULL;

    // Itterate through query
    DWORD byteOffset = 0; 
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* curentInfo = procInfoBuffer;
    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= bufferLength) {
        // Switch for relationship
        switch (curentInfo->Relationship) {
            case RelationNumaNode:
                // ON non NUMA system this will only be called once
                numaNodeCount++;
                break;

            case RelationProcessorCore:
                // Increment core count
                processorCoreCount++;
                // Read logical processors
                logicalProcessorCount += CountSetBits(curentInfo->ProcessorMask);
                break;

            case RelationCache:
                // Extract info from info
                ptrCache = &curentInfo->Cache;
                {
                    // Bad practice switch case in switch case
                    switch (ptrCache->Level) {
                        case 1:
                            processorL1CacheCount++;
                            break;
                        case 2:
                            processorL2CacheCount++;
                            break;
                        case 3:
                            processorL3CacheCount++;
                            break;
                    }
                }
                break;

            case RelationProcessorPackage:
                processorPackageCount++;
                break;

            // No default case required (will only increase potential to fail on certian systmes)
        }

        // Move forward
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        curentInfo++;
    }

    // Output computed Information
    ss << "Number of NUMA nodes: " << numaNodeCount << std::endl;
    ss << "Number of physical processor packages: " << processorPackageCount << std::endl;
    ss << "Number of processor cores: " << processorCoreCount << std::endl;
    ss << "Number of logical processors: " << logicalProcessorCount << std::endl;
    ss << "Number of processor L1/L2/L3 caches: " << processorL1CacheCount << "/" << processorL2CacheCount << "/" << processorL3CacheCount << std::endl;

    // Free Buffer
    free(procInfoBuffer);


    // === Windows Memory Info ===
    // Get memory info via system call
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memoryStatus) == FALSE) {
        ss << "Unexpected return of FALSE from system call GlobalMemoryStatusEx(...)" << std::endl << std::endl;
        return ss;
    }

    // Translate memory to readable values
    FLOAT phyMemInGiB = (FLOAT)memoryStatus.ullTotalPhys / 1024.0F / 1024.0F / 1024.0F;
    FLOAT vtlMemInGiB = (FLOAT)memoryStatus.ullTotalVirtual / 1024.0F / 1024.0F / 1024.0F;

    // Print memory info
    ss << "Physical memory: " << phyMemInGiB << " GiB" << std::endl;
    ss << "Virtual memory: " << vtlMemInGiB << " GiB" << std::endl << std::endl;

    // Set as called and return stream
    m_bCalled = true;
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdSystemInfo::getInstance(){
    // Return referencs
    return s_instance;
}

DWORD  DxFeatures::Command::CmdSystemInfo::CountSetBits(ULONG_PTR bitMask){
    DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD bitSetCount = 0;

    for (DWORD i = 0; i <= LSHIFT; i++){
        bitSetCount += ((bitMask & bitTest) ? 1 : 0);
        bitTest /= 2;
    }

    return bitSetCount;
}
