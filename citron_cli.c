#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

char current_pass[32] = "citron";
int is_root = 0;

typedef void (*GetPassFunc)(char*, int);
typedef void (*SetPassFunc)(const char*);

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
void cmd_citron_list();
void cmd_version();
void cmd_license();
void cmd_credits();
void cmd_pwdmod();
void cmd_sudosu();
void cmd_filegui();
void cmd_startbrowser();
void cmd_localhost_systeminfo();
void cmd_reset();
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

    load_password();

    char userBuffer[32];
    char passBuffer[32];
    int authenticated = 0;

    while (!authenticated) {
        system("cls");
        printf("+------------------------------------------------------------+\n");
        printf("|                    Citron CLI v2.5                         |\n");
        printf("+------------------------------------------------------------+\n");
        printf(" Source code on https://github.com/citron-software/Citron-CLI\n\n");
        
        printf("citron login: ");
        if (fgets(userBuffer, sizeof(userBuffer), stdin) == NULL) continue;
        userBuffer[strcspn(userBuffer, "\r\n")] = 0;

        printf("Password: ");
        get_masked_password(passBuffer, sizeof(passBuffer));

        if (strcmp(userBuffer, "citron") == 0 && strcmp(passBuffer, current_pass) == 0) {
            authenticated = 1;
        } else {
            printf("\nIdentifiants incorrects. Appuyez sur Entree pour reessayer...");
            getchar();
        }
    }

    system("cls");
    printf("+------------------------------------------------------------+\n");
    printf("|                    Citron CLI v2.5                         |\n");
    printf("+------------------------------------------------------------+\n");
    printf(" Source code on https://github.com/citron-software/Citron-CLI\n\n");
    printf("Logged in as: citron\n\n");

    char inputBuffer[128];
    
    while (1) {
        if (is_root) {
            printf("root@citron:~# ");
        } else {
            printf("citron@citron:~# ");
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
        } else if (strcmp(inputBuffer, "zip") == 0 || strncmp(inputBuffer, "zip ", 4) == 0) {
            cmd_zip(inputBuffer + (strlen(inputBuffer) > 3 ? 4 : 0));
        } else if (strncmp(inputBuffer, "unzip ", 6) == 0) {
            cmd_unzip(inputBuffer + 6);
        } else if (strncmp(inputBuffer, "python ", 7) == 0) {
            cmd_python(inputBuffer + 7);
        } else if (strncmp(inputBuffer, "node ", 5) == 0) {
            cmd_node(inputBuffer + 5);
        } else if (strncmp(inputBuffer, "docker ", 7) == 0) {
            cmd_docker(inputBuffer + 7);
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
        } else if (strcmp(inputBuffer, "sudo su") == 0) {
            cmd_sudosu();
        } else if (strcmp(inputBuffer, "filegui") == 0) {
            cmd_filegui();
        } else if (strcmp(inputBuffer, "startbrowser") == 0) {
            cmd_startbrowser();
        } else if (strcmp(inputBuffer, "localhost systeminfo") == 0) {
            cmd_localhost_systeminfo();
        } else if (strcmp(inputBuffer, "reset") == 0) {
            cmd_reset();
        } else if (strcmp(inputBuffer, "clear") == 0) {
            system("cls");
        } else if (strcmp(inputBuffer, "") != 0) {
            printf("bash: %s: commande introuvable\n\n", inputBuffer);
        }
    }

    return 0;
}

void cmd_help() {
    printf("\nCitron CLI v2.5 - 55 Commandes Supportees :\n");
    printf("  1. help        2. uname       3. pwd         4. whoami      5. date\n");
    printf("  6. ls          7. echo        8. uptime      9. free       10. df\n");
    printf(" 11. ps         12. history    13. hostname   14. env        15. cat\n");
    printf(" 16. touch      17. mkdir      18. rm         19. cp         20. mv\n");
    printf(" 21. ping       22. ip         23. reboot     24. shutdown   25. neofetch\n");
    printf(" 26. top        27. htop       28. nano       29. vim        30. gcc\n");
    printf(" 31. make       32. git        33. curl       34. wget       35. tar\n");
    printf(" 36. zip        37. unzip      38. python     39. node       40. docker\n");
    printf(" 41. clearcache 42. systeminfo 43. citroninfo 44. citronfetch45. citron list\n");
    printf(" 46. version    47. license    48. credits    49. pwdmod     50. sudo su\n");
    printf(" 51. filegui    52. startbrowser 53. localhost systeminfo 54. reset\n");
    printf(" 55. exit/clear\n\n");
}

void cmd_uname() { printf("Linux citron 6.12.0-citron-amd64 x86_64 GNU/Linux\n\n"); }
void cmd_pwd() { printf("/home/citron\n\n"); }
void cmd_whoami() { 
    if (is_root) {
        printf("root\n\n");
    } else {
        printf("citron\n\n");
    }
}
void cmd_date() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s\n", asctime(tm));
}
void cmd_ls() {
    printf("total 24\n");
    printf("drwxr-xr-x 4 citron citron 4096 Sep 11 18:36 Documents\n");
    printf("drwxr-xr-x 2 citron citron 4096 Sep 11 18:36 Projects\n");
    printf("-rw-r--r-- 1 citron citron  220 Sep 11 18:36 citron.conf\n");
    printf("-rwxr-xr-x 1 citron citron 1024 Sep 11 18:36 bootx64.efi\n\n");
}
void cmd_echo(const char *arg) { printf("%s\n\n", arg); }
void cmd_uptime() { printf(" 18:36:40 up 4 days,  2:14,  1 user,  load average: 0.05, 0.12, 0.08\n\n"); }
void cmd_free() { printf("               total        used        free      shared  buff/cache   available\nMem:         262144      115200       81920        2048       65024      146944\n\n"); }
void cmd_df() { printf("Filesystem     1K-blocks      Used Available Use%% Mounted on\nC:\\citron       52428800  18432000  33996800  36%% /\n\n"); }
void cmd_ps() { printf("  PID TTY          TIME CMD\n 1337 tty1     00:00:00 bash\n 1450 tty1     00:00:00 citron-cli\n\n"); }
void cmd_history() { printf("  1  help\n  2  uname\n  3  systeminfo\n  4  citronfetch\n\n"); }
void cmd_hostname() { printf("citron-node-01\n\n"); }
void cmd_env() { printf("USER=%s\nHOME=/home/%s\nSHELL=/bin/bash\nTERM=xterm-256color\n\n", is_root ? "root" : "citron", is_root ? "root" : "citron"); }
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
void cmd_zip(const char *arg) { printf("[zip] Archive creee avec succes (%s).\n\n", arg); }
void cmd_unzip(const char *arg) { printf("[unzip] Extraction terminee (%s).\n\n", arg); }
void cmd_python(const char *arg) { printf("Python 3.12.0 (main, Sep 11 2026)\n[GCC 13.2.0] on win32\nExecution de '%s'\n\n", arg); }
void cmd_node(const char *arg) { printf("Node.js v22.0.0\nExecution de '%s'\n\n", arg); }
void cmd_docker(const char *arg) { printf("[Docker Engine] Commande executee: %s\n\n", arg); }
void cmd_clearcache() { printf("Cache systeme nettoye avec succes (0 Mo conserves).\n\n"); }
void cmd_systeminfo() {
    printf("--- System Hardware & Environment ---\n");
    printf(" Hostname: citron-node-01\n");
    printf(" OS: Citron CLI v2.5 x86_64 Core\n");
    printf(" Kernel: Win32-Subsystem Emulation\n");
    printf(" Memory: 256 MB Allocated / 42 MB Used\n");
    printf(" Storage: Win32 Virtual Mount (rw)\n\n");
}
void cmd_citroninfo() {
    printf("--- Citron Distribution Details ---\n");
    printf(" Codename: Trixie-Preview (v2.5)\n");
    printf(" Package Manager: citron-pkg (v1.4)\n");
    printf(" Maintainer: Citron Software Core Team\n");
    printf(" Initiative: AI Testing & Embedded Shells\n\n");
}
void cmd_citronfetch() {
    printf("       _      _                 Terminal: Citron CLI v2.5 x86_64\n");
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
void cmd_sudosu() {
    char passInput[32];

    printf("[sudo] password for citron: ");
    get_masked_password(passInput, sizeof(passInput));

    if (strcmp(passInput, current_pass) == 0) {
        is_root = 1;
        printf("\n");
    } else {
        printf("citron is not in the sudoers file. This incident will be reported.\n\n");
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
void cmd_localhost_systeminfo() {
    printf("[Citron WinSys] Ouverture des Informations Systeme Windows...\n");
    system("msinfo32");
    printf("Informations systeme lancees.\n\n");
}
void cmd_reset() {
    strcpy(current_pass, "citron");
    save_password();
    is_root = 0;
    system("cls");
    printf("+------------------------------------------------------------+\n");
    printf("|                    Citron CLI v2.5                         |\n");
    printf("+------------------------------------------------------------+\n");
    printf(" Source code on https://github.com/citron-software/Citron-CLI\n\n");
    printf("[Citron Reset] Reinitialisation aux parametres par defaut effectuee !\n\n");
}
void cmd_version() { printf("Citron CLI Core v2.5.0-release\n\n"); }
void cmd_license() { printf("Citron Software Open License (MIT Compatible)\n\n"); }
void cmd_credits() { printf("Developed by Citron Software Team.\n\n"); }