#include <windows.h> 
#include <stdio.h>

void EnumerateSubKeys(HKEY hKey) {
	CHAR subKeyName[256];
	DWORD subKeyNameSize = sizeof(subKeyName);
	DWORD index = 0;

	while (RegEnumKeyExA(hKey, index, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
		HKEY hSubKey;
		if (RegOpenKeyExA(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
			CHAR imagePath[1024];
			DWORD imagePathSize = sizeof(imagePath);
			DWORD type;

			if (RegQueryValueExA(hSubKey, "ImagePath", NULL, &type, (LPBYTE)imagePath, &imagePathSize) == ERROR_SUCCESS) {
				if (type == REG_SZ || type == REG_EXPAND_SZ) {
					printf("Subkey: %s\n", subKeyName);
					printf("ImagePath: %s\n\n", imagePath);
				}
			}

			RegCloseKey(hSubKey);
		}

		subKeyNameSize = sizeof(subKeyName);
		index++;
	}
}

int main() {
	HKEY hKey;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		EnumerateSubKeys(hKey);
		RegCloseKey(hKey);
	}
	else {
		printf("Nu s-a putut deschide cheia de registru.\n");
	}

	return 0;
}