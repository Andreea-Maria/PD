#include <iostream>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <initguid.h>

#pragma comment(lib, "setupapi.lib")

int main() {
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        printf("Eroare la obtinerea listei de dispozitive.");
        return -1;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    printf("Dispozitive USB conectate:");
    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        char deviceName[256];
        char printName[256];
        DWORD size;

        if (SetupDiGetDeviceInstanceIdA(deviceInfoSet, &deviceInfoData, deviceName, sizeof(deviceName), NULL)) {
            if (strncmp(deviceName, "USB\\", 4) == 0) {
                printf("Dispozitiv USB %d: %s", i + 1, deviceName);

                if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)printName, sizeof(printName), &size) ||
                    SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)printName, sizeof(printName), &size)) {
                    printf("(%s)", printName);
                }

                printf("\n");
            }
        }
    }
    system("pause");
    return 0;
}