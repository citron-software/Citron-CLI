#include <windows.h>
#include <stdio.h>
#include <string.h>

#define DATA_FILE "password.dat"
#define EXPORT __declspec(dllexport)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

// Fonction pour récupérer le mot de passe depuis la DLL
EXPORT void get_password(char *buffer, int max_len) {
    FILE *f = fopen(DATA_FILE, "r");
    if (f != NULL) {
        if (fgets(buffer, max_len, f) != NULL) {
            buffer[strcspn(buffer, "\r\n")] = 0;
            if (strlen(buffer) == 0) {
                strcpy(buffer, "citron");
            }
        } else {
            strcpy(buffer, "citron");
        }
        fclose(f);
    } else {
        strcpy(buffer, "citron");
        FILE *fw = fopen(DATA_FILE, "w");
        if (fw != NULL) {
            fprintf(fw, "citron");
            fclose(fw);
        }
    }
}

// Fonction pour enregistrer le nouveau mot de passe via la DLL
EXPORT void set_password(const char *new_pass) {
    FILE *f = fopen(DATA_FILE, "w");
    if (f != NULL) {
        fprintf(f, "%s", new_pass);
        fclose(f);
    }
}