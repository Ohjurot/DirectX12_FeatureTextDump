#include "CPUIDQuery.h"

DxFeatures::Command::CmdCPUID DxFeatures::Command::CmdCPUID::s_instance = DxFeatures::Command::CmdCPUID();

std::stringstream DxFeatures::Command::CmdCPUID::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return empty stream if already called
    if (m_bCalled)
        return ss;

    // Print header
    ss << "[CPUID]" << std::endl;

    // Query CPUID
    DxFeatures::Data::CPUID_RESULT cpuid;
    ZeroMemory(&cpuid, sizeof(DxFeatures::Data::CPUID_RESULT));

    // Query and check if failed
    if (!DxFeatures::Data::CPUID_Factory::queryCpu(&cpuid)) {
        // Write failed message and return stream
        ss << "Failed to query cpuid" << std::endl << std::endl;
        return ss;
    }

    // Print CPU Vendor
    ss << "CPU-Vendor: " << cpuid.vendorString << " (";
    switch (cpuid.vendor) {
        case DxFeatures::Data::CPU_VENDOR::AMD:
            ss << "AMD";
            break;
        case DxFeatures::Data::CPU_VENDOR::INTEL:
            ss << "INTEL";
            break;
        case DxFeatures::Data::CPU_VENDOR::VM_OR_UNKNOWN:
            ss << "VM_OR_UNKNOWN";
            break;
    }
    ss << ")" << std::endl;

    // Print CPU Brand
    ss << "CPU-Brand: " << cpuid.brandString << std::endl;

    // Print instructions
    ss << "Supported Instructions: ";
    SSTREAM_OUT(cpuid.ABM(),         ss,   "ABM");
    SSTREAM_OUT(cpuid.ADX(),         ss, ", ADX");
    SSTREAM_OUT(cpuid.AES(),         ss, ", AES");
    SSTREAM_OUT(cpuid.AVX(),         ss, ", AVX");
    SSTREAM_OUT(cpuid.AVX2(),        ss, ", AVX2");
    SSTREAM_OUT(cpuid.AVX512CD(),    ss, ", AVX512CD");
    SSTREAM_OUT(cpuid.AVX512ER(),    ss, ", AVX512ER");
    SSTREAM_OUT(cpuid.AVX512F(),     ss, ", AVX512F");
    SSTREAM_OUT(cpuid.AVX512PF(),    ss, ", AVX512PF");
    SSTREAM_OUT(cpuid.BMI1(),        ss, ", BMI1");
    SSTREAM_OUT(cpuid.BMI2(),        ss, ", BMI2");
    SSTREAM_OUT(cpuid.CLFSH(),       ss, ", CLFSH");
    SSTREAM_OUT(cpuid.CMOV(),        ss, ", CMOV");
    SSTREAM_OUT(cpuid.CMPXCHG16B(),  ss, ", CMPXCHG16B");
    SSTREAM_OUT(cpuid.CX8(),         ss, ", CX8");
    SSTREAM_OUT(cpuid.ERMS(),        ss, ", ERMS");
    SSTREAM_OUT(cpuid.F16C(),        ss, ", F16C");
    SSTREAM_OUT(cpuid.FMA(),         ss, ", FMA");
    SSTREAM_OUT(cpuid.FSGSBASE(),    ss, ", FSGSBASE");
    SSTREAM_OUT(cpuid.FXSR(),        ss, ", FXSR");
    SSTREAM_OUT(cpuid.HLE(),         ss, ", HLE");
    SSTREAM_OUT(cpuid.INVPCID(),     ss, ", INVPCID");
    SSTREAM_OUT(cpuid.LAHF(),        ss, ", LAHF");
    SSTREAM_OUT(cpuid.LZCNT(),       ss, ", LZCNT");
    SSTREAM_OUT(cpuid.MMX(),         ss, ", MMX");
    SSTREAM_OUT(cpuid.MMXEXT(),      ss, ", MMXEXT");
    SSTREAM_OUT(cpuid.MONITOR(),     ss, ", MONITOR");
    SSTREAM_OUT(cpuid.MOVBE(),       ss, ", MOVBE");
    SSTREAM_OUT(cpuid.MSR(),         ss, ", MSR");
    SSTREAM_OUT(cpuid.OSXSAVE(),     ss, ", OSXSAVE");
    SSTREAM_OUT(cpuid.PCLMULQDQ(),   ss, ", PCLMULQDQ");
    SSTREAM_OUT(cpuid.POPCNT(),      ss, ", POPCNT");
    SSTREAM_OUT(cpuid.PREFETCHWT1(), ss, ", PREFETCHWT1");
    SSTREAM_OUT(cpuid.RDRAND(),      ss, ", RDRAND");
    SSTREAM_OUT(cpuid.RDSEED(),      ss, ", RDSEED");
    SSTREAM_OUT(cpuid.RDTSCP(),      ss, ", RDTSCP");
    SSTREAM_OUT(cpuid.RTM(),         ss, ", RTM");
    SSTREAM_OUT(cpuid.SEP(),         ss, ", SEP");
    SSTREAM_OUT(cpuid.SHA(),         ss, ", SHA");
    SSTREAM_OUT(cpuid.SSE(),         ss, ", SSE");
    SSTREAM_OUT(cpuid.SSE2(),        ss, ", SSE2");
    SSTREAM_OUT(cpuid.SSE3(),        ss, ", SSE3");
    SSTREAM_OUT(cpuid.SSE41(),       ss, ", SSE41");
    SSTREAM_OUT(cpuid.SSE42(),       ss, ", SSE42");
    SSTREAM_OUT(cpuid.SSE4a(),       ss, ", SSE4a");
    SSTREAM_OUT(cpuid.SSSE3(),       ss, ", SSSE3");
    SSTREAM_OUT(cpuid.SYSCALL(),     ss, ", SYSCALL");
    SSTREAM_OUT(cpuid.TBM(),         ss, ", TBM");
    SSTREAM_OUT(cpuid.XOP(),         ss, ", XOP");
    SSTREAM_OUT(cpuid.XSAVE(),       ss, ", XSAVE");
    SSTREAM_OUT(cpuid._3DNOW(),      ss, ", _3DNOW");
    SSTREAM_OUT(cpuid._3DNOWEXT(),   ss, ", _3DNOWEXT");
    ss << std::endl << std::endl;

    // Set as called and return stream
    m_bCalled = true;
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdCPUID::getInstance(){
    // Return const command reference
    return DxFeatures::Command::CmdCPUID::s_instance;
}
