#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

char current_user[32] = "citron";
char current_pass[32] = "citron";
int is_root = 0;

typedef void (*GetPassFunc)(char*, int);
typedef void (*SetPassFunc)(const char*);

void load_login() {
    FILE *f = fopen("login.dat", "r");
    if (f != NULL) {
        if (fgets(current_user, sizeof(current_user), f) != NULL) {
            current_user[strcspn(current_user, "\r\n")] = 0;
        }
        fclose(f);
    } else {
        strcpy(current_user, "citron");
    }
}

void save_login() {
    FILE *f = fopen("login.dat", "w");
    if (f != NULL) {
        fprintf(f, "%s", current_user);
        fclose(f);
    }
}

void load_password() {
    HMODULE hDll = LoadLibrary("citron_config.dll");
    if (hDll != NULL) {
        GetPassFunc get_password = (GetPassFunc)GetProcAddress(hDll, "get_password");
        if (get_password != NULL) {
            get_password(current_pass, sizeof(current_pass));
        }
        FreeLibrary(hDll);
    } else {
        strcpy(current_pass, "citron");
    }
}

void save_password() {
    HMODULE hDll = LoadLibrary("citron_config.dll");
    if (hDll != NULL) {
        SetPassFunc set_password = (SetPassFunc)GetProcAddress(hDll, "set_password");
        if (set_password != NULL) {
            set_password(current_pass);
        }
        FreeLibrary(hDll);
    }
}

void get_masked_password(char *buffer, int max_len) {
    int i = 0;
    char ch;
    while (i < max_len - 1) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (ch >= 32 && ch <= 126) {
            buffer[i++] = ch;
            printf("*");
        }
    }
    buffer[i] = '\0';
    printf("\n");
}

void cmd_help();
void cmd_uname();
void cmd_pwd();
void cmd_whoami();
void cmd_date();
void cmd_ls();
void cmd_uptime();
void cmd_free();
void cmd_df();
void cmd_ps();
void cmd_history();
void cmd_hostname();
void cmd_env();
void cmd_systeminfo();
void cmd_citroninfo();
void cmd_citronfetch();
void cmd_fastfetch();
void cmd_citron_list();
void cmd_version();
void cmd_license();
void cmd_credits();
void cmd_pwdmod();
void cmd_loginmod();
void cmd_sudosu();
void cmd_filegui();
void cmd_startbrowser();
void cmd_startnotepad();
void cmd_restart32();
void cmd_localhost_systeminfo();
void cmd_recovery();
void cmd_cirtm(const char *arg);
void cmd_echo(const char *arg);
void cmd_cat(const char *arg);
void cmd_ping(const char *arg);
void cmd_touch(const char *arg);
void cmd_mkdir(const char *arg);
void cmd_rm(const char *arg);
void cmd_cp(const char *arg);
void cmd_mv(const char *arg);
void cmd_ip();
void cmd_reboot();
void cmd_shutdown();
void cmd_neofetch();
void cmd_top();
void cmd_htop();
void cmd_nano(const char *arg);
void cmd_vim(const char *arg);
void cmd_gcc(const char *arg);
void cmd_make();
void cmd_git(const char *arg);
void cmd_curl(const char *arg);
void cmd_wget(const char *arg);
void cmd_tar(const char *arg);
void cmd_zip(const char *arg);
void cmd_unzip(const char *arg);
void cmd_python(const char *arg);
void cmd_node(const char *arg);
void cmd_docker(const char *arg);
void cmd_clearcache();

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    load_login();
    load_password();

    char userBuffer[32];
    char passBuffer[32];
    int authenticated = 0;

    while (!authenticated) {
        system("cls");
        printf("+------------------------------------------------------------+\n");
        printf("|                    Citron CLI v2.7                         |\n");
        printf("+------------------------------------------------------------+\n");
        printf(" Source code on https://github.com/citron-software/Citron-CLI\n\n");
        
        printf("%s login: ", current_user);
        if (fgets(userBuffer, sizeof(userBuffer), stdin) == NULL) continue;
        userBuffer[strcspn(userBuffer, "\r\n")] = 0;

        printf("Password: ");
        get_masked_password(passBuffer, sizeof(passBuffer));

        if (strcmp(userBuffer, current_user) == 0 && strcmp(passBuffer, current_pass) == 0) {
            authenticated = 1;
        } else {
            printf("\nIdentifiants incorrects. Appuyez sur Entree pour reessayer...");
            getchar();
        }
    }

    system("cls");
    printf("+------------------------------------------------------------+\n");
    printf("|                    Citron CLI v2.7                         |\n");
    printf("+------------------------------------------------------------+\n");
    printf(" Source code on https://github.com/citron-software/Citron-CLI\n\n");
    printf("Logged in as: %s\n\n", current_user);

    char inputBuffer[128];
    
    while (1) {
        if (is_root) {
            printf("root@citron:~# ");
        } else {
            printf("%s@citron:~# ", current_user);
        }

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) break;
        inputBuffer[strcspn(inputBuffer, "\r\n")] = 0;

        if (strcmp(inputBuffer, "exit") == 0) {
            if (is_root) {
                is_root = 0;
                printf("logout\n\n");
            } else {
                break;
            }
        } else if (strcmp(inputBuffer, "help") == 0) {
            cmd_help();
        } else if (strcmp(inputBuffer, "uname") == 0) {
            cmd_uname();
        } else if (strcmp(inputBuffer, "pwd") == 0) {
            cmd_pwd();
        } else if (strcmp(inputBuffer, "whoami") == 0) {
            cmd_whoami();
        } else if (strcmp(inputBuffer, "date") == 0) {
            cmd_date();
        } else if (strcmp(inputBuffer, "ls") == 0) {
            cmd_ls();
        } else if (strncmp(inputBuffer, "echo ", 5) == 0) {
            cmd_echo(inputBuffer + 5);
        } else if (strcmp(inputBuffer, "uptime") == 0) {
            cmd_uptime();
        } else if (strcmp(inputBuffer, "free") == 0) {
            cmd_free();
        } else if (strcmp(inputBuffer, "df") == 0) {
            cmd_df();
        } else if (strcmp(inputBuffer, "ps") == 0) {
            cmd_ps();
        } else if (strcmp(inputBuffer, "history") == 0) {
            cmd_history();
        } else if (strcmp(inputBuffer, "hostname") == 0) {
            cmd_hostname();
        } else if (strcmp(inputBuffer, "env") == 0) {
            cmd_env();
        } else if (strncmp(inputBuffer, "cat ", 4) == 0) {
            cmd_cat(inputBuffer + 4);
        } else if (strncmp(inputBuffer, "touch ", 6) == 0) {
            cmd_touch(inputBuffer + 6);
        } else if (strncmp(inputBuffer, "mkdir ", 6) == 0) {
            cmd_mkdir(inputBuffer + 6);
        } else if (strncmp(inputBuffer, "rm ", 3) == 0) {
            cmd_rm(inputBuffer + 3);
        } else if (strncmp(inputBuffer, "cp ", 3) == 0) {
            cmd_cp(inputBuffer + 3);
        } else if (strncmp(inputBuffer, "mv ", 3) == 0) {
            cmd_mv(inputBuffer + 3);
        } else if (strncmp(inputBuffer, "ping ", 5) == 0) {
            cmd_ping(inputBuffer + 5);
        } else if (strcmp(inputBuffer, "ip") == 0) {
            cmd_ip();
        } else if (strcmp(inputBuffer, "reboot") == 0) {
            cmd_reboot();
        } else if (strcmp(inputBuffer, "shutdown") == 0) {
            cmd_shutdown();
        } else if (strcmp(inputBuffer, "neofetch") == 0) {
            cmd_neofetch();
        } else if (strcmp(inputBuffer, "fastfetch") == 0) {
            cmd_fastfetch();
        } else if (strcmp(inputBuffer, "top") == 0) {
            cmd_top();
        } else if (strcmp(inputBuffer, "htop") == 0) {
            cmd_htop();
        } else if (strncmp(inputBuffer, "nano ", 5) == 0) {
            cmd_nano(inputBuffer + 5);
        } else if (strncmp(inputBuffer, "vim ", 4) == 0) {
            cmd_vim(inputBuffer + 4);
        } else if (strncmp(inputBuffer, "gcc ", 4) == 0) {
            cmd_gcc(inputBuffer + 4);
        } else if (strcmp(inputBuffer, "make") == 0) {
            cmd_make();
        } else if (strncmp(inputBuffer, "git ", 4) == 0) {
            cmd_git(inputBuffer + 4);
        } else if (strncmp(inputBuffer, "curl ", 5) == 0) {
            cmd_curl(inputBuffer + 5);
        } else if (strncmp(inputBuffer, "wget ", 5) == 0) {
            cmd_wget(inputBuffer + 5);
        } else if (strncmp(inputBuffer, "tar ", 4) == 0) {
            cmd_tar(inputBuffer + 4);
        } else if (strcmp(inputBuffer, "zip") == 0) {
            cmd_zip("");
        } else if (strncmp(inputBuffer, "zip ", 4) == 0) {
            cmd_zip(inputBuffer + 4);
        } else if (strncmp(inputBuffer, "unzip ", 6) == 0) {
            cmd_unzip(inputBuffer + 6);
        } else if (strncmp(inputBuffer, "python ", 7) == 0) {
            cmd_python(inputBuffer + 7);
        } else if (strncmp(inputBuffer, "node ", 5) == 0) {
            cmd_node(inputBuffer + 5);
        } else if (strncmp(inputBuffer, "docker ", 7) == 0) {
            cmd_docker(inputBuffer + 7);
        } else if (strncmp(inputBuffer, "sudo ", 5) == 0) {
            char passInput[32];
            printf("[sudo] password for %s: ", current_user);
            get_masked_password(passInput, sizeof(passInput));

            if (strcmp(passInput, current_pass) == 0) {
                char *realCmd = inputBuffer + 5;
                if (strncmp(realCmd, "cirtm install ", 14) == 0) {
                    cmd_cirtm(realCmd + 14);
                } else {
                    char binPath[256];
                    char firstWord[64];
                    sscanf(realCmd, "%s", firstWord);
                    sprintf(binPath, "citron_pkgs\\%s\\bin.exe", firstWord);
                    
                    DWORD attrib = GetFileAttributes(binPath);
                    if (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY)) {
                        printf("[%s] Lancement en mode administrateur...\n", firstWord);
                        char cmdLine[512];
                        sprintf(cmdLine, "citron_pkgs\\%s\\bin.exe %s", firstWord, realCmd + strlen(firstWord));
                        system(cmdLine);
                        printf("\n");
                    } else {
                        printf("sudo: %s: commande introuvable ou non installée via cirtm\n\n", firstWord);
                    }
                }
            } else {
                printf("%s is not in the sudoers file. This incident will be reported.\n\n", current_user);
            }
        } else if (strcmp(inputBuffer, "clearcache") == 0) {
            cmd_clearcache();
        } else if (strcmp(inputBuffer, "systeminfo") == 0) {
            cmd_systeminfo();
        } else if (strcmp(inputBuffer, "citroninfo") == 0) {
            cmd_citroninfo();
        } else if (strcmp(inputBuffer, "citronfetch") == 0) {
            cmd_citronfetch();
        } else if (strcmp(inputBuffer, "citron list") == 0) {
            cmd_citron_list();
        } else if (strcmp(inputBuffer, "version") == 0) {
            cmd_version();
        } else if (strcmp(inputBuffer, "license") == 0) {
            cmd_license();
        } else if (strcmp(inputBuffer, "credits") == 0) {
            cmd_credits();
        } else if (strcmp(inputBuffer, "pwdmod") == 0) {
            cmd_pwdmod();
        } else if (strcmp(inputBuffer, "loginmod") == 0) {
            cmd_loginmod();
        } else if (strcmp(inputBuffer, "sudo su") == 0) {
            cmd_sudosu();
        } else if (strcmp(inputBuffer, "filegui") == 0) {
            cmd_filegui();
        } else if (strcmp(inputBuffer, "startbrowser") == 0) {
            cmd_startbrowser();
        } else if (strcmp(inputBuffer, "startnotepad") == 0) {
            cmd_startnotepad();
        } else if (strcmp(inputBuffer, "restart32") == 0) {
            cmd_restart32();
        } else if (strcmp(inputBuffer, "localhost systeminfo") == 0) {
            cmd_localhost_systeminfo();
        } else if (strcmp(inputBuffer, "recovery") == 0) {
            cmd_recovery();
        } else if (strcmp(inputBuffer, "clear") == 0) {
            system("cls");
        } else if (strcmp(inputBuffer, "") != 0) {
            char binPath[256];
            sprintf(binPath, "citron_pkgs\\%s\\bin.exe", inputBuffer);
            
            DWORD attrib = GetFileAttributes(binPath);
            if (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY)) {
                printf("[%s] Lancement du programme...\n", inputBuffer);
                system(binPath);
                printf("\n");
            } else {
                char firstWord[64];
                sscanf(inputBuffer, "%s", firstWord);
                sprintf(binPath, "citron_pkgs\\%s\\bin.exe", firstWord);
                attrib = GetFileAttributes(binPath);
                
                if (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY)) {
                    char cmdLine[512];
                    sprintf(cmdLine, "citron_pkgs\\%s\\bin.exe %s", firstWord, inputBuffer + strlen(firstWord));
                    system(cmdLine);
                    printf("\n");
                } else {
                    printf("bash: %s: commande introuvable\n\n", inputBuffer);
                }
            }
        }
    }

    return 0;
}

void cmd_help() {
    printf("\nCitron CLI v2.7 - 59 Commandes Supportees :\n");
    printf("  1. help        2. uname       3. pwd         4. whoami      5. date\n");
    printf("  6. ls          7. echo        8. uptime      9. free       10. df\n");
    printf(" 11. ps         12. history    13. hostname   14. env        15. cat\n");
    printf(" 16. touch      17. mkdir      18. rm         19. cp         20. mv\n");
    printf(" 21. ping       22. ip         23. reboot     24. shutdown   25. neofetch\n");
    printf(" 26. fastfetch  27. top        28. htop       29. nano       30. vim\n");
    printf(" 31. gcc        32. make       33. git        34. curl       35. wget\n");
    printf(" 36. tar        37. zip        38. unzip      39. python     40. node\n");
    printf(" 41. docker     42. sudo cirtm 43. clearcache 44. systeminfo 45. citroninfo\n");
    printf(" 46. citronfetch 47. citron list 48. version  49. license    50. credits\n");
    printf(" 51. pwdmod     52. loginmod   53. sudo su    54. filegui    55. startbrowser\n");
    printf(" 56. startnotepad 57. restart32 58. localhost systeminfo 59. exit/clear\n\n");
}

void cmd_uname() { printf("Linux citron 6.12.0-citron-amd64 x86_64 GNU/Linux\n\n"); }
void cmd_pwd() { 
    char cwd[MAX_PATH];
    if (GetCurrentDirectory(MAX_PATH, cwd)) {
        printf("%s\n\n", cwd);
    } else {
        printf("/home/%s\n\n", current_user);
    }
}
void cmd_whoami() { 
    if (is_root) {
        printf("root\n\n");
    } else {
        printf("%s\n\n", current_user);
    }
}
void cmd_date() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s", asctime(tm));
    printf("\n");
}
void cmd_ls() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Erreur lors de la lecture du repertoire.\n\n");
        return;
    }

    printf("Repertoire courant :\n");
    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("  [DIR]  %s\n", findFileData.cFileName);
        } else {
            printf("         %s\n", findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    printf("\n");
}
void cmd_echo(const char *arg) { printf("%s\n\n", arg); }
void cmd_uptime() { printf(" 18:36:40 up 4 days,  2:14,  1 user,  load average: 0.05, 0.12, 0.08\n\n"); }
void cmd_free() { printf("               total        used        free      shared  buff/cache   available\nMem:         262144      115200       81920        2048       65024      146944\n\n"); }
void cmd_df() { printf("Filesystem     1K-blocks      Used Available Use%% Mounted on\nC:\\citron       52428800  18432000  33996800  36%% /\n\n"); }
void cmd_ps() { printf("  PID TTY          TIME CMD\n 1337 tty1     00:00:00 bash\n 1450 tty1     00:00:00 citron-cli\n\n"); }
void cmd_history() { printf("  1  help\n  2  uname\n  3  systeminfo\n  4  citronfetch\n\n"); }
void cmd_hostname() { printf("citron-node-01\n\n"); }
void cmd_env() { printf("USER=%s\nHOME=/home/%s\nSHELL=/bin/bash\nTERM=xterm-256color\n\n", is_root ? "root" : current_user, is_root ? "root" : current_user); }
void cmd_cat(const char *arg) { printf("[cat] Contenu du fichier virtuel '%s' :\n(fichier vide ou inexistant)\n\n", arg); }
void cmd_touch(const char *arg) { printf("Fichier '%s' cree avec succes.\n\n", arg); }
void cmd_mkdir(const char *arg) { printf("[sudo] Fichier/Dossier '%s' cree avec succes.\n\n", arg); }
void cmd_rm(const char *arg) { printf("Fichier/Dossier '%s' supprime.\n\n", arg); }
void cmd_cp(const char *arg) { printf("Copie effectuee (%s).\n\n", arg); }
void cmd_mv(const char *arg) { printf("Deplacement effectue (%s).\n\n", arg); }
void cmd_ping(const char *arg) { printf("PING %s (127.0.0.1) 56(84) bytes of data.\n64 bytes from 127.0.0.1: icmp_seq=1 ttl=64 time=0.042 ms\n\n", arg); }
void cmd_ip() { printf("1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65535 qdisc noqueue state UNKNOWN\n2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP\n    inet 192.168.1.50/24 brd 192.168.1.255 scope global eth0\n\n"); }
void cmd_reboot() { printf("Redemarrage du systeme en cours...\n\n"); }
void cmd_shutdown() { printf("Arret du systeme...\n\n"); }
void cmd_neofetch() { cmd_citronfetch(); }
void cmd_fastfetch() { cmd_citronfetch(); }
void cmd_top() { printf("top - 18:36:40 up 4 days,  1 user,  load average: 0.00, 0.01, 0.05\nTasks: 42 total, 1 running, 41 sleeping\n%Cpu(s):  0.3 us,  0.3 sy,  0.0 ni, 99.3 id\n\n"); }
void cmd_htop() { cmd_top(); }
void cmd_nano(const char *arg) { printf("[Nano Editor] Edition de '%s' (simulation)\n\n", arg); }
void cmd_vim(const char *arg) { printf("[Vim Editor] Ouverture de '%s' (simulation)\n\n", arg); }
void cmd_gcc(const char *arg) { printf("[GCC Compiler] Compilation de '%s' -> a.out [OK]\n\n", arg); }
void cmd_make() { printf("make: Rien a faire pour 'all'.\n\n"); }
void cmd_git(const char *arg) { printf("git %s: Succes de l'operation Git.\n\n", arg); }
void cmd_curl(const char *arg) { printf("[curl] Telechargement depuis %s [OK]\n\n", arg); }
void cmd_wget(const char *arg) { printf("[wget] Sauvegarde terminee pour %s\n\n", arg); }
void cmd_tar(const char *arg) { printf("[tar] Extraction/Compression archive %s [OK]\n\n", arg); }
void cmd_zip(const char *arg) { 
    if (strlen(arg) == 0) {
        printf("Utilisation : zip <archive.zip> <fichiers...>\n\n");
    } else {
        printf("[zip] Archive '%s' creee avec succes.\n\n", arg); 
    }
}
void cmd_unzip(const char *arg) { printf("[unzip] Extraction terminee (%s).\n\n", arg); }
void cmd_python(const char *arg) { printf("Python 3.12.0 (main, Sep 11 2026)\n[GCC 13.2.0] on win32\nExecution de '%s'\n\n", arg); }
void cmd_node(const char *arg) { printf("Node.js v22.0.0\nExecution de '%s'\n\n", arg); }
void cmd_docker(const char *arg) { printf("[Docker Engine] Commande executee: %s\n\n", arg); }

void cmd_cirtm(const char *arg) {
    const char *pkg = arg;
    printf("[sudo] Recherche de '%s' sur les miroirs Citron...\n", pkg);

    HINTERNET hInternet = InternetOpen("CitronOS-Cirtm", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        printf("E: Erreur réseau.\n\n");
        return;
    }

    char url[512];
    HINTERNET hUrl = NULL;
    int found = 0;

    CreateDirectory("citron_pkgs", NULL);
    char folderPath[256];
    sprintf(folderPath, "citron_pkgs\\%s", pkg);
    CreateDirectory(folderPath, NULL);
    char filePath[256];
    sprintf(filePath, "%s\\bin.exe", folderPath);

    sprintf(url, "https://packages.debian.org/trixie/%s", pkg);
    hUrl = InternetOpenUrl(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);

    if (hUrl != NULL) {
        printf("-> Paquet trouvé dans les dépôts officiels Citron !\n");
        found = 1;
        InternetCloseHandle(hUrl);
    } else {
        sprintf(url, "https://flathub.org/api/v2/appstream/%s", pkg);
        hUrl = InternetOpenUrl(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (hUrl != NULL) {
            printf("-> Paquet trouvé sur Flathub (Flatpak) !\n");
            found = 1;
            InternetCloseHandle(hUrl);
        }
    }

    InternetCloseHandle(hInternet);

    if (found) {
        HANDLE hFile = CreateFile(filePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            const char *simData = "CitronOS Online Package Wrapper";
            DWORD written;
            WriteFile(hFile, simData, strlen(simData), &written, NULL);
            CloseHandle(hFile);
        }
        printf("Succès : Paquet '%s' téléchargé et installé dans 'citron_pkgs/%s' !\n\n", pkg, pkg);
    } else {
        printf("E: Impossible de trouver le paquet '%s' sur les miroirs Citron ni sur Flatpak.\n\n", pkg);
    }
}

void cmd_clearcache() { printf("Cache systeme nettoye avec succes (0 Mo conserves).\n\n"); }
void cmd_systeminfo() {
    printf("--- System Hardware & Environment ---\n");
    printf(" Hostname: citron-node-01\n");
    printf(" OS: Citron CLI v2.7 x86_64 Core\n");
    printf(" Kernel: Win32-Subsystem Emulation\n");
    printf(" Memory: 256 MB Allocated / 42 MB Used\n");
    printf(" Storage: Win32 Virtual Mount (rw)\n\n");
}
void cmd_citroninfo() {
    printf("--- Citron Distribution Details ---\n");
    printf(" Codename: Trixie-Preview (v2.7)\n");
    printf(" Package Manager: citron-pkg (v1.4)\n");
    printf(" Maintainer: Citron Software Core Team\n");
    printf(" Initiative: AI Testing & Embedded Shells\n\n");
}
void cmd_citronfetch() {
    printf("       _      _                 Terminal: Citron CLI v2.7 x86_64\n");
    printf("      (_)    | |                Kernel: Win32 UEFI Stub\n");
    printf("   ___ _ _ __| |_ _ __ ___      Uptime: active\n");
    printf("  / __| | '__| __| '_ ` _ \\     Shell: Citron Terminal\n");
    printf(" | (__| | |  | |_| | | | | |    Terminal: Win32 Console\n");
    printf("  \\___|_|_|   \\__|_| |_| |_|    CPU: x86_64 Emulated\n\n");
}
void cmd_citron_list() {
    printf("Catalogue des paquets CitronOS :\n");
    printf("  - coreutils [installe] (v9.4-1)\n");
    printf("  - bash [installe] (v5.2-6)\n");
    printf("  - gcc [disponible] (v13.2.0-2)\n");
    printf("  - make [disponible] (v4.4.1-1)\n");
    printf("  - git [disponible] (v2.43.0-1)\n");
    printf("  - vim [disponible] (v9.0-1)\n");
    printf("  - nano [disponible] (v7.2-1)\n");
    printf("  - python3 [disponible] (v3.12.0-1)\n");
    printf("  - nodejs [disponible] (v22.0.0-1)\n");
    printf("  - docker-ce [disponible] (v25.0.0-1)\n");
    printf("  - curl [disponible] (v8.5.0-1)\n");
    printf("  - wget [disponible] (v1.21.4-1)\n");
    printf("  - htop [disponible] (v3.3.0-1)\n");
    printf("  - tmux [disponible] (v3.4-1)\n\n");
}
void cmd_pwdmod() {
    char oldPass[32], newPass[32], confirmPass[32];

    printf("Mot de passe actuel : ");
    get_masked_password(oldPass, sizeof(oldPass));

    if (strcmp(oldPass, current_pass) != 0) {
        printf("Erreur : Mot de passe actuel incorrect.\n\n");
        return;
    }

    printf("Nouveau mot de passe : ");
    get_masked_password(newPass, sizeof(newPass));

    printf("Confirmer le mot de passe : ");
    get_masked_password(confirmPass, sizeof(confirmPass));

    if (strcmp(newPass, confirmPass) != 0) {
        printf("Erreur : Les nouveaux mots de passe ne correspondent pas.\n\n");
        return;
    }

    strcpy(current_pass, newPass);
    save_password();
    printf("Mot de passe modifie et sauvegarde via la DLL avec succes !\n\n");
}
void cmd_loginmod() {
    char oldLogin[32], newLogin[32], confirmLogin[32];

    printf("Ancien login : ");
    if (fgets(oldLogin, sizeof(oldLogin), stdin) == NULL) return;
    oldLogin[strcspn(oldLogin, "\r\n")] = 0;

    if (strcmp(oldLogin, current_user) != 0) {
        printf("Erreur : Ancien login incorrect.\n\n");
        return;
    }

    printf("Nouveau login : ");
    if (fgets(newLogin, sizeof(newLogin), stdin) == NULL) return;
    newLogin[strcspn(newLogin, "\r\n")] = 0;

    printf("Confirmer le login : ");
    if (fgets(confirmLogin, sizeof(confirmLogin), stdin) == NULL) return;
    confirmLogin[strcspn(confirmLogin, "\r\n")] = 0;

    if (strcmp(newLogin, confirmLogin) != 0) {
        printf("Erreur : Les nouveaux logins ne correspondent pas.\n\n");
        return;
    }

    strcpy(current_user, newLogin);
    save_login();
    printf("Login modifie et sauvegarde dans login.dat avec succes !\n\n");
}
void cmd_sudosu() {
    char passInput[32];

    printf("[sudo] password for %s: ", current_user);
    get_masked_password(passInput, sizeof(passInput));

    if (strcmp(passInput, current_pass) == 0) {
        is_root = 1;
        printf("\n");
    } else {
        printf("%s is not in the sudoers file. This incident will be reported.\n\n", current_user);
    }
}
void cmd_filegui() {
    printf("[Citron FileGUI] Ouverture de l'explorateur de fichiers...\n");
    system("explorer .");
    printf("Explorateur ouvert dans le repertoire courant.\n\n");
}
void cmd_startbrowser() {
    printf("[Citron Browser] Lancement du navigateur par defaut...\n");
    system("start https://github.com/citron-software");
    printf("Navigateur ouvert.\n\n");
}
void cmd_startnotepad() {
    printf("[Citron Notepad] Lancement du Bloc-notes Windows...\n");
    system("notepad");
    printf("Bloc-notes ouvert.\n\n");
}
void cmd_restart32() {
    printf("[Citron Arch] Basculement en mode 32-bits et redemarrage...\n");
    system("cls");
    printf("+------------------------------------------------------------+\n");
    printf("|              Citron CLI v2.7 (x86 - 32-bit)                |\n");
    printf("+------------------------------------------------------------+\n");
    printf(" Redemarrage effectue en architecture x86 (32-bit).\n\n");
}
void cmd_localhost_systeminfo() {
    printf("[Citron WinSys] Ouverture des Informations Systeme Windows...\n");
    system("msinfo32");
    printf("Informations systeme lancees.\n\n");
}
void cmd_recovery() {
    char passInput[32];
    printf("[Recovery Mode] Entrez le mot de passe pour acceder au recovery : ");
    get_masked_password(passInput, sizeof(passInput));

    if (strcmp(passInput, current_pass) != 0) {
        printf("Mot de passe incorrect. Acces au recovery refuse.\n\n");
        return;
    }

    char choice[16];
    while (1) {
        printf("\n+------------------------------------------------------------+\n");
        printf("|                   Citron Recovery Menu                     |\n");
        printf("+------------------------------------------------------------+\n");
        printf(" 1. Reset le CLI (Remet le login et mot de passe sur 'citron')\n");
        printf(" 2. View Updates (Ouvre les releases GitHub)\n");
        printf(" 3. Wipe Cache (Nettoie le cache systeme)\n");
        printf(" 4. Exit (Sortir du recovery)\n");
        printf("Choix : ");

        if (fgets(choice, sizeof(choice), stdin) == NULL) break;
        choice[strcspn(choice, "\r\n")] = 0;

        if (strcmp(choice, "1") == 0) {
            strcpy(current_user, "citron");
            strcpy(current_pass, "citron");
            save_login();
            save_password();
            is_root = 0;
            printf("\n[Recovery] CLI reinitialise avec succes ! Login: citron | Password: citron\n");
        } else if (strcmp(choice, "2") == 0) {
            printf("\n[Recovery] Ouverture de la page des mises a jour...\n");
            system("start https://github.com/citron-software/Citron-CLI/releases");
        } else if (strcmp(choice, "3") == 0) {
            printf("\n[Recovery] Cache systeme nettoye avec succes !\n");
        } else if (strcmp(choice, "4") == 0 || _stricmp(choice, "exit") == 0) {
            printf("\nSortie du mode recovery.\n\n");
            break;
        } else {
            printf("\nOption invalide. Veuillez reessayer.\n");
        }
    }
}
void cmd_version() { printf("Citron CLI Core v2.7.0-release\n\n"); }
void cmd_license() { printf("Citron Software Open License (MIT Compatible)\n\n"); }
void cmd_credits() { printf("Developed by Citron Software Team.\n\n"); }