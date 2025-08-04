#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <exception>
#include <sstream>
#include <libcpuid.h>
#include <limits.h>
#include <string>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <algorithm>

#ifdef _WIN32

#define os_type 0
#include <lm.h>
#include <sysinfoapi.h>
#include <windows.h>
std::string GetWindowsName() {
    DWORD dwType = REG_SZ;
    HKEY hKey = 0;
    char value[1024];
    DWORD value_length = 1024;
    const char* subkey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
    RegQueryValueEx(hKey, "ProductName", NULL, &dwType, (LPBYTE)&value,
                    &value_length);
    return std::string(value);
}
#endif

#ifndef _WIN32
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <dirent.h>

std::string get_os_name() {
    std::vector<std::string> names;

    DIR* dir = opendir("/etc");
    if (!dir) return "";

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        if (filename.size() >= 8 && std::strcmp(filename.substr(filename.size() - 8).c_str(), "-release") == 0) {
            std::ifstream in("/etc/" + filename);
            std::string line;
            while (std::getline(in, line)) {
                if (line.size() >= 12 && line.compare(0, 12, "PRETTY_NAME=") == 0) {
                    auto val = line.substr(13);
                    if (!val.empty() && val.front() == '"') val.erase(0, 1);
                    if (!val.empty() && val.back() == '"') val.pop_back();
                    names.push_back(val);
                }
            }
        }
    }

    closedir(dir);
    std::reverse(names.begin(), names.end());

    std::string result;
    for (const auto& name : names)
        result += name + ' ';
    if (!result.empty()) result.pop_back();

    return result;
}

std::string getCpuModel() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.substr(0, 10) == "model name" || line.substr(0, 9) == "cpu model") {
            size_t colon = line.find(':');
            if (colon != std::string::npos)
                return line.substr(colon + 2); // Skip ": "
        }
    }
    return "Unknown CPU";
}
#endif

#if __APPLE__ || __MACH__
#define os_type 2
#elif __linux
#define os_type 1
#elif __unix
#define os_type 3
#endif

int main() {
    std::string ostypestring = (os_type == 0) ?  "Windows" : (os_type == 1) ? "Linux" : (os_type == 2) ? "MacOS" : (os_type == 3) ? "Unix" : "Unknown";
    std::string hostnamestr = "";
    std::string os_name = "";
    std::string total_ram = "";
    std::string free_ram = "";
    std::string cpu = "Unknown";

    #ifdef _WIN32
        os_name = GetWindowsName();
        char buffer[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD size = sizeof(buffer);
        GetComputerName(buffer, &size);
        hostnamestr = buffer;
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
        total_ram = std::to_string((float)statex.ullTotalPhys / pow(1024,3))+" GiB";
        free_ram = std::to_string((float)statex.ullAvailPhys / pow(1024,3))+" GiB";
    #else
        os_name = get_os_name();
        char hostname[HOST_NAME_MAX + 1];
        gethostname(hostname, HOST_NAME_MAX + 1);
        hostnamestr = hostname; 
        struct sysinfo si;
        sysinfo(&si);
        total_ram = std::to_string((float)si.totalram / pow(1024,3))+" GiB";
        free_ram = std::to_string((float)si.freeram / pow(1024,3))+" GiB";
    #endif

    if (cpuid_present()) {
        struct cpu_raw_data_t raw; 
        struct cpu_id_t data;
        if (cpuid_get_raw_data(&raw) < 0) {
            printf("Sorry, cannot get the CPUID raw data.\n");
            printf("Error: %s\n", cpuid_error());
            return -2;
        }
        if (cpu_identify(&raw, &data) < 0) {
            printf("Sorrry, CPU identification failed.\n");
            printf("Error: %s\n", cpuid_error());
            return -3;
        }
        cpu = data.brand_str;
    }
    #ifndef _WIN32
    else{
        cpu = getCpuModel();
    }
    #endif

    std::cout << "OS Type: "+ostypestring+"\nOS Name: "+os_name+"\nHostname: "+hostnamestr+"\nTotal RAM: "+total_ram+"\nTotal Free RAM: "+free_ram+"\nCPU: "+cpu+"\n";
    return 0;
}
