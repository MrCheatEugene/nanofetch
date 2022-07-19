	#include "stdio.h"
	#include <iostream>
	#include <iomanip>
	#include <fstream>
	#include <cstring>
	#include <stdio.h>
	#ifdef __MINGW32__
	   #include <windows.h>
	   #include <sysinfoapi.h>
	   #include <iostream>
	   #include <exception>
	   #include <sstream>
std::string GetWindowsName()
{
DWORD dwType = REG_SZ;
HKEY hKey = 0;
char value[1024];
DWORD value_length = 1024;
const char* subkey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
RegOpenKey(HKEY_LOCAL_MACHINE,subkey,&hKey);
RegQueryValueEx(hKey, "ProductName", NULL, &dwType, (LPBYTE)&value, &value_length);
return std::string(value);
}
	#endif

	#ifdef _WIN64
#include <libcpuid.h>
#define os "Windows(64 bit)"
#include <string>
#include <lm.h>
#include <sysinfoapi.h>
#include <iostream>
#include<windows.h>
	   int main(){
			printf("OS-type:");                   
			printf("Windows(64 bit)");
			printf("\n");
			printf("OS: ");
    		printf(GetWindowsName().c_str());
	    	printf("\n");
	   	  	char buffer[MAX_COMPUTERNAME_LENGTH+1];
			DWORD size;
			size=sizeof(buffer);
			GetComputerName(buffer,&size);
			printf("Hostname: ");
			printf(buffer);
			printf("\n");
			MEMORYSTATUSEX statex;
	   		statex.dwLength = sizeof (statex); // I misunderstand that
	   		GlobalMemoryStatusEx (&statex);
	   		std::cout << "Total RAM: " << (float)statex.ullTotalPhys/(1024*1024*1024);
	   		printf(" GB\n");
	   		std::cout << "Total Free RAM: " << (float)statex.ullAvailPhys/(1024*1024*1024);
	   		printf(" GB\n");
			if (!cpuid_present()) {                                                // check for CPUID presence                                         // check for CPUID presence
				printf("CPU: Unknown\n");
			}else{
				struct cpu_raw_data_t raw;                                             // contains only raw data
				struct cpu_id_t data;   
				if (cpuid_get_raw_data(&raw) < 0) {                                    // obtain the raw CPUID data
					printf("Sorry, cannot get the CPUID raw data.\n");
					printf("Error: %s\n", cpuid_error());                          // cpuid_error() gives the last error description
					return -2;
				}
				if (cpu_identify(&raw, &data) < 0) {                                   // identify the CPU, using the given raw data.
					printf("Sorrry, CPU identification failed.\n");
					printf("Error: %s\n", cpuid_error());
					return -3;
				}
				printf("CPU: ");             // print out the CPU brand string
				printf("%s", data.brand_str);
				printf("\n");
			}
			return 0;
	   }
	#elif __APPLE__ || __MACH__
    #define os "Macintosh"
	    #include <stdlib.h>
	#include <unistd.h>
	#include <limits.h>
	#include <sys/sysinfo.h>
	#include <libcpuid.h>
	#include <sys/utsname.h>
	#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
		int main(){
		struct sysinfo si;

   struct utsname buffer;

   errno = 0;

  	printf("\n");
	 	sysinfo(&si);
		printf("OS-type:");                   
		printf("Macintosh");
		printf("\n");
	   if (uname(&buffer) < 0) {
   	printf("Unknown OS!");
   }else{
   	    printf("OS Name: %s\n",exec("cat /etc/*-release | egrep 'PRETTY_NAME' | cut -d = -f 2 | tr -d '\"' | tac | tr '\n' ' '").c_str());
   		printf("Bitness: %s\n", buffer.machine);	
   		printf("Kernel version: %s\n", buffer.release);
   		printf("Version: %s\n", buffer.version);
   }
	    char hostname[HOST_NAME_MAX + 1];
	  	gethostname(hostname, HOST_NAME_MAX + 1);	
	  	printf("Hostname: ");
		printf("%s",hostname);
		printf("\n");
		std::cout << "Total RAM: " <<(float)si.totalram/1024/1024/1024 ;
		printf(" GB\n");
		std::cout << "Free RAM: " <<(float)si.freeram/1024/1024/1024 ;
		printf(" GB\n");
			if (!cpuid_present()) {                                                // check for CPUID presence                                         // check for CPUID presence
				printf("Unable to detect CPU!\n");
			}else{
				struct cpu_raw_data_t raw;                                             // contains only raw data
				struct cpu_id_t data;   
				if (cpuid_get_raw_data(&raw) < 0) {                                    // obtain the raw CPUID data
					printf("Sorry, cannot get the CPUID raw data.\n");
					printf("Error: %s\n", cpuid_error());                          // cpuid_error() gives the last error description
					return -2;
				}
				if (cpu_identify(&raw, &data) < 0) {                                   // identify the CPU, using the given raw data.
					printf("Sorrry, CPU identification failed.\n");
					printf("Error: %s\n", cpuid_error());
					return -3;
				}
				printf("CPU: ");             // print out the CPU brand string
				printf("%s", data.brand_str);
				printf("\n");
			}
		return 0;
		}
	#elif _WIN32
	   #define os "Windows"
	   #include <libcpuid.h>
	    int main(){
	    printf("OS: ");
    	printf(GetWindowsName().c_str());
	    printf("\n");
		printf("OS-type:");                   
		printf("Windows");
		printf("\n");   
		   	char buffer[MAX_COMPUTERNAME_LENGTH+1];
			DWORD size;
			size=sizeof(buffer);
			GetComputerName(buffer,&size);
			printf("Hostname: ");
			printf(buffer);
			printf("\n");
			MEMORYSTATUSEX statex;
	   		statex.dwLength = sizeof (statex); // I misunderstand that
	   		GlobalMemoryStatusEx (&statex);
	   		std::cout << "Total RAM: " << (float)statex.ullTotalPhys/(1024*1024*1024);
	   		printf(" GB\n");
	   		std::cout << "Total RAM: " << (float)statex.ullAvailPhys/(1024*1024*1024);
	   		printf(" GB\n");
			if (!cpuid_present()) {                                                // check for CPUID presence                                         // check for CPUID presence
				printf("Unable to detect CPU!\n");
			}else{
				struct cpu_raw_data_t raw;                                             // contains only raw data
				struct cpu_id_t data;   
				if (cpuid_get_raw_data(&raw) < 0) {                                    // obtain the raw CPUID data
					printf("Sorry, cannot get the CPUID raw data.\n");
					printf("Error: %s\n", cpuid_error());                          // cpuid_error() gives the last error description
					return -2;
				}
				if (cpu_identify(&raw, &data) < 0) {                                   // identify the CPU, using the given raw data.
					printf("Sorrry, CPU identification failed.\n");
					printf("Error: %s\n", cpuid_error());
					return -3;
				}
				printf("CPU: ");             // print out the CPU brand string
				printf("%s", data.brand_str);
				printf("\n");
			}
			return 0;
	   }
	#elif __linux
	    #define os "Linux"
	    #include <stdlib.h>
	#include <unistd.h>
	#include <limits.h>
	#include <sys/sysinfo.h>
	#include <libcpuid.h>
	#include <sys/utsname.h>
	#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
		int main(){
		struct sysinfo si;

   struct utsname buffer;

   errno = 0;

  	printf("\n");
	 	sysinfo(&si);
		printf("OS-type:");                   
		printf("Linux");
		printf("\n");
	   if (uname(&buffer) < 0) {
   	printf("Unknown OS!");
   }else{
   	    printf("OS Name: %s\n",exec("cat /etc/*-release | egrep 'PRETTY_NAME' | cut -d = -f 2 | tr -d '\"' | tac | tr '\n' ' '").c_str());
   		printf("Bitness: %s\n", buffer.machine);	
   		printf("Kernel version: %s\n", buffer.release);
   		printf("Version: %s\n", buffer.version);
   }
	    char hostname[HOST_NAME_MAX + 1];
	  	gethostname(hostname, HOST_NAME_MAX + 1);	
	  	printf("Hostname: ");
		printf("%s",hostname);
		printf("\n");
		std::cout << "Total RAM: " <<(float)si.totalram/1024/1024/1024 ;
		printf(" GB\n");
		std::cout << "Free RAM: " <<(float)si.freeram/1024/1024/1024 ;
		printf(" GB\n");
			if (!cpuid_present()) {                                                // check for CPUID presence                                         // check for CPUID presence
				printf("Unable to detect CPU!\n");
			}else{
				struct cpu_raw_data_t raw;                                             // contains only raw data
				struct cpu_id_t data;   
				if (cpuid_get_raw_data(&raw) < 0) {                                    // obtain the raw CPUID data
					printf("Sorry, cannot get the CPUID raw data.\n");
					printf("Error: %s\n", cpuid_error());                          // cpuid_error() gives the last error description
					return -2;
				}
				if (cpu_identify(&raw, &data) < 0) {                                   // identify the CPU, using the given raw data.
					printf("Sorrry, CPU identification failed.\n");
					printf("Error: %s\n", cpuid_error());
					return -3;
				}
				printf("CPU: ");             // print out the CPU brand string
				printf("%s", data.brand_str);
				printf("\n");
			}
		return 0;
		}
	#elif __unix // all unices not caught above
	    #include <stdlib.h>
	#include <unistd.h>
	#include <limits.h>
	#include <sys/sysinfo.h>
	#include <libcpuid.h>
	#include <sys/utsname.h>
	#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
		int main(){
		struct sysinfo si;

   struct utsname buffer;

   errno = 0;

  	printf("\n");
	 	sysinfo(&si);
		printf("OS-type:");                   
		printf("Unix");
		printf("\n");
	   if (uname(&buffer) < 0) {
   	printf("Unknown OS!");
   }else{
   	    printf("OS Name: %s\n",exec("cat /etc/*-release | egrep 'PRETTY_NAME' | cut -d = -f 2 | tr -d '\"' | tac | tr '\n' ' '").c_str());
   		printf("Bitness: %s\n", buffer.machine);	
   		printf("Kernel version: %s\n", buffer.release);
   		printf("Version: %s\n", buffer.version);
   }
	    char hostname[HOST_NAME_MAX + 1];
	  	gethostname(hostname, HOST_NAME_MAX + 1);	
	  	printf("Hostname: ");
		printf("%s",hostname);
		printf("\n");
		std::cout << "Total RAM: " <<(float)si.totalram/1024/1024/1024 ;
		printf(" GB\n");
		std::cout << "Free RAM: " <<(float)si.freeram/1024/1024/1024 ;
		printf(" GB\n");
			if (!cpuid_present()) {                                                // check for CPUID presence                                         // check for CPUID presence
				printf("Unable to detect CPU!\n");
			}else{
				struct cpu_raw_data_t raw;                                             // contains only raw data
				struct cpu_id_t data;   
				if (cpuid_get_raw_data(&raw) < 0) {                                    // obtain the raw CPUID data
					printf("Sorry, cannot get the CPUID raw data.\n");
					printf("Error: %s\n", cpuid_error());                          // cpuid_error() gives the last error description
					return -2;
				}
				if (cpu_identify(&raw, &data) < 0) {                                   // identify the CPU, using the given raw data.
					printf("Sorrry, CPU identification failed.\n");
					printf("Error: %s\n", cpuid_error());
					return -3;
				}
				printf("CPU: ");             // print out the CPU brand string
				printf("%s", data.brand_str);
				printf("\n");
			}
		return 0;
		}
	#endif

