#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_SKILLS 4
#define MAX_NAME 20
#define MAX_POKEMON 3

// 스킬 구조체
typedef struct {
    char name[MAX_NAME];
    int damage;
    int uses;
} Skill;

// 포켓몬 구조체
typedef struct {
    char name[MAX_NAME];
    int hp;
    int max_hp;
    int attack;
    int defense;
    int speed;
    Skill skills[MAX_SKILLS];
} Pokemon;

// 플레이어 구조체
typedef struct {
    Pokemon pokemon[MAX_POKEMON];
    int active_pokemon;
} Player;

// 함수 선언
Skill create_skill(const char* name, int damage, int uses);
Pokemon create_pokemon(const char* name, int hp, int attack, int defense, int speed);
int calculate_damage(Pokemon attacker, Pokemon defender, Skill skill);
void clear_console();
void delay(int milliseconds);
void print_pokemon(const char* name);
void print_battle_screen(Pokemon* player, Pokemon* enemy);
void animate_skill(const char* attacker, const char* defender, const char* skill_name);
void switch_pokemon(Player* player);
void battle(Player* player, Pokemon* enemy);

// 스킬 초기화 함수
Skill create_skill(const char* name, int damage, int uses) {
    Skill skill;
    strncpy(skill.name, name, MAX_NAME - 1);
    skill.name[MAX_NAME - 1] = '\0';
    skill.damage = damage;
    skill.uses = uses;
    return skill;
}

// 포켓몬 초기화 함수
Pokemon create_pokemon(const char* name, int hp, int attack, int defense, int speed) {
    Pokemon pokemon;
    strncpy(pokemon.name, name, MAX_NAME - 1);
    pokemon.name[MAX_NAME - 1] = '\0';
    pokemon.hp = hp;
    pokemon.max_hp = hp;
    pokemon.attack = attack;
    pokemon.defense = defense;
    pokemon.speed = speed;
    return pokemon;
}

// 데미지 계산 함수
int calculate_damage(Pokemon attacker, Pokemon defender, Skill skill) {
    int damage = (attacker.attack + skill.damage - defender.defense / 2);
    return damage > 0 ? damage : 1;
}

// 콘솔 지우기 함수
void clear_console() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 지연 함수
void delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

// ASCII 아트 출력 함수
void print_pokemon(const char* name) {
    if (strcmp(name, "피카츄") == 0) {
        printf("  /\\_/\\\n");
        printf(" (>^.^<)\n");
        printf("  /)   )\n");
        printf(" //  // \n");
        printf("//  //  \n");
    } else if (strcmp(name, "꼬부기") == 0) {
        printf("   _____\n");
        printf("  /     \\\n");
        printf(" | ^   ^ |\n");
        printf(" |  \\_/  |\n");
        printf("  \\____/\n");
        printf("  //  \\\\\n");
    } else if (strcmp(name, "파이리") == 0) {
        printf("   /\\\n");
        printf("  (  )\n");
        printf(" ( `` )\n");
        printf("  \\  /\n");
        printf("   )(\n");
    } else
    {
        printf(("\n"));
        printf(("                                               `/:+`                      ```                        \n"));
        printf(("                                              :- .+`     `....``        -+-:/:                      \n"));
        printf(("                                              ./. `/--:::-....--:::::-./:   +.                      \n"));
        printf(("                                               `/.  .`              `.:`  `/.                       \n"));
        printf(("                                                `/                       `+`                        \n"));
        printf(("                                                `o                       /.                         \n"));
        printf(("                                                :-                       /.                         \n"));
        printf(("                                               `+                        ./                         \n"));
        printf(("                                               .:                        `+                         \n"));
        printf(("                                               `+    `.`           `     .+                         \n"));
        printf(("                                                :-`-:``.-`      `..` `-.`/.                         \n"));
        printf(("                                                `+``o/o.` `- `- ```:+-/ ./                          \n"));
        printf(("                                                 :- //Nh/. .:-/ .:hNh--.+`                          \n"));
        printf(("                        `-:::::-`                `+```:+ss::.`:/yoo/.``+`                           \n"));
        printf(("                       `+-`   `.+.              `:+-     ``     `     -:                            \n"));
        printf(("                       /-       .o              +.`./-.            `-:-`                            \n"));
        printf(("                       :/       :+:`           ::  --.-::.` ``. `.::.                               \n"));
        printf(("                        :/-...-/:`./:--..`     o   o    s.::-..::-`                                 \n"));
        printf(("                         `..-+-`    -+:..-:-.` + `.+:---o````.+-                                    \n"));
        printf(("                  `...`      :+      `:/-..-//:+:/:-.` `.--:``-:-.-.                                \n"));
        printf(("                -/:-.-:/-``.:/. -      .s:...-/-````.-:`  `..-:-  `:-                               \n"));
        printf(("               .o`     `o/--.  `o      o`     `o`     `/.      -``  -:                              \n"));
        printf(("        ```    -/       /-      +`     s       o`       +`     ` .:` :-                             \n"));
        printf(("    `-//:::://:-s:`   `:o.``    `.   ``++.`  `:/-`      -/     .- -/  +`                            \n"));
        printf(("  `//-`       `-:os+:::----:::.````-/:-.-:::::. ./`     `+      /  +` :/                            \n"));
        printf((" .o.   ``...:.    `:+.       `-::::-`            `+.    `+      `  :` :s                            \n"));
        printf(("`o.  `::----:+/`    `+:                           `/:`   /.      `..``/o                            \n"));
        printf((":+  `+.       -+`     //                            ./-` `::-..-::-` :./`                           \n"));
        printf(("o.  :/         -o`     /+                             -/.    `    `  /..:                           \n"));
        printf(("y   +.          :+      //                             `::        /. :-`/                           \n"));
        printf(("y   +.           //      o-                              +.       `o``+`/`                          \n"));
        printf(("s`  /:            +/     .o                              -/        .+ .+./`                         \n"));
        printf(("+-  .o             /+`    s.                             -:         -- .+.+`                        \n"));
        printf(("-+   +-             -o:   s`                        ./::-:` .`       `  `/:o`                       \n"));
        printf((" o`  `o.              -///-                      `:/-        ``       ````-/o:                      \n"));
        printf((" .o   `o`                                      `//`              .:-::::::/++s+                     \n"));
        printf(("  :/   `+-                                    -+`                 -:        :+:+-                   \n"));
        printf(("   //    :+`                                 :/`                   +         `o-:+`                 \n"));
        printf(("    :+`   `//`                              :/                     o          `s`-o`                \n"));
        printf(("     -+`    .//-                           -+                     .o           o. -+                \n"));
        printf(("      `+-     `-/:-.                     `-s                      +-           o.  /:               \n"));
        printf(("       `//`      `.-:::---.....-------::::s.                     .o           `s   `s               \n"));
        printf(("         .+:`         ````......``````   :/                     `o.           //    s`              \n"));
        printf(("           -/:`                         `o`                     +-           .o`    s`              \n"));
        printf(("             ./:`                       -/                    `+-           `o.     s`              \n"));
        printf(("               .:/-`                    +.                   `+-           `o-      s               \n"));
        printf(("                 `-/:.`                 o`                  .+-           -+.      `o               \n"));
        printf(("                    `-/:-.`             o`                `//`          ./:`       :-               \n"));
        printf(("                       `.-:::-.``       :`              `:/.          .//.        ./                \n"));
        printf(("                            `.--::::-.-:+`            .:/.         `-/:.        .::`                \n"));
        printf(("                                  `.://:`          `.//.        `-:/-`       .-/-`                  \n"));
        printf(("                                  -/-`          `-/+:.````...-:/s:.      `.-/-.                     \n"));
        printf(("                                 `o         .::::-:---------..` o       `+-`                        \n"));
        printf(("                                  o`      `-:-`                 ::      .+                          \n"));
        printf(("                                  o`     ./.                     +`     +.                          \n"));
        printf(("                                 `o     .o`                      +.     +                           \n"));
        printf(("                                 ::     o.                      `o`     /`                          \n"));
        printf(("                                `o`    :+                      `+-      `+-                         \n"));
        printf(("                                :/     y`                    ./o/-`      `:/.                       \n"));
        printf(("                               `o`     h/-                  -+. `-s`       `//.`                    \n"));
        printf(("                              `o.      y`o`                 o`    o.         `:/:`                  \n"));
        printf(("                              /:       s.o.                 -o.``:s.`           .:/:.`       ````   \n"));
        printf(("                             :/        :o-                   `///-`-:/:.         ...:///::::/::://` \n"));
        printf(("                            :/         `o.`..``                       .:+.        .-:/::/++-`    .+:\n"));
        printf(("                           -+  `://`    `/:..::/-                       `+:`               -+-    `s\n"));
        printf(("                          -o      -+            //                        -//:.```         `/o-:--:.\n"));
        printf(("                          /:     `/o-:::::::`   `s                           `-:::::::::--:-`       \n"));
        printf(("                           :/::://-        `:////-  \n"));
    }
}
// 배틀 화면 출력 함수
void print_battle_screen(Pokemon* player, Pokemon* enemy) {
    print_pokemon(enemy->name);
    printf("\n%s (HP: %d/%d)\n", enemy->name, enemy->hp, enemy->max_hp);
    printf("\n\n");
    print_pokemon(player->name);
    printf("\n%s (HP: %d/%d)\n", player->name, player->hp, player->max_hp);
}

// 스킬 사용 애니메이션
void animate_skill(const char* attacker, const char* defender, const char* skill_name) {
    clear_console();
    printf("\n\n%s가 %s 스킬을 사용합니다!\n", attacker, skill_name);
    delay(1000);
    clear_console();
    printf("\n\n%s에게 데미지를 입혔습니다!\n", defender);
    delay(1000);
}

// 포켓몬 교체 함수
void switch_pokemon(Player* player) {
    printf("\n교체할 포켓몬을 선택하세요:\n");
    for (int i = 0; i < MAX_POKEMON; i++) {
        if (i != player->active_pokemon && player->pokemon[i].hp > 0) {
            printf("%d. %s (HP: %d/%d)\n", i + 1, player->pokemon[i].name,
                   player->pokemon[i].hp, player->pokemon[i].max_hp);
        }
    }

    int choice;
    do {
        printf("선택: ");
        scanf("%d", &choice);
        choice--;
    } while (choice < 0 || choice >= MAX_POKEMON || choice == player->active_pokemon || player->pokemon[choice].hp <= 0);

    player->active_pokemon = choice;
    printf("%s로 교체했습니다!\n", player->pokemon[choice].name);
    delay(1000);
}

// 전투 함수
void battle(Player* player, Pokemon* enemy) {
    int turn = 0;

    while (1) {
        turn++;
        print_battle_screen(&player->pokemon[player->active_pokemon], enemy);
        printf("\n--- 턴 %d ---\n", turn);

        // 플레이어 턴
        printf("%s의 턴!\n", player->pokemon[player->active_pokemon].name);
        printf("0. 포켓몬 교체\n");
        for (int i = 0; i < MAX_SKILLS; i++) {
            printf("%d. %s (데미지: %d, 남은 사용 횟수: %d)\n",
                   i+1, player->pokemon[player->active_pokemon].skills[i].name,
                   player->pokemon[player->active_pokemon].skills[i].damage,
                   player->pokemon[player->active_pokemon].skills[i].uses);
        }

        int choice;
        do {
            printf("행동을 선택하세요: ");
            scanf("%d", &choice);
        } while (choice < 0 || choice > MAX_SKILLS ||
                 (choice > 0 && player->pokemon[player->active_pokemon].skills[choice-1].uses <= 0));

        if (choice == 0) {
            switch_pokemon(player);
        } else {
            choice--;
            int damage = calculate_damage(player->pokemon[player->active_pokemon], *enemy,
                                          player->pokemon[player->active_pokemon].skills[choice]);
            enemy->hp -= damage;
            player->pokemon[player->active_pokemon].skills[choice].uses--;

            animate_skill(player->pokemon[player->active_pokemon].name, enemy->name,
                          player->pokemon[player->active_pokemon].skills[choice].name);
            printf("%s가 %s 스킬을 사용했습니다! %s에게 %d의 데미지를 입혔습니다.\n",
                   player->pokemon[player->active_pokemon].name,
                   player->pokemon[player->active_pokemon].skills[choice].name,
                   enemy->name, damage);
            delay(2000);

            if (enemy->hp <= 0) {
                print_battle_screen(&player->pokemon[player->active_pokemon], enemy);
                printf("%s가 쓰러졌습니다! 승리!\n", enemy->name);
                return;
            }
        }

        // 적 턴
        print_battle_screen(&player->pokemon[player->active_pokemon], enemy);
        printf("\n%s의 턴!\n", enemy->name);
        int enemy_choice = rand() % MAX_SKILLS;
        while (enemy->skills[enemy_choice].uses <= 0) {
            enemy_choice = rand() % MAX_SKILLS;
        }

        int damage = calculate_damage(*enemy, player->pokemon[player->active_pokemon],
                                      enemy->skills[enemy_choice]);
        player->pokemon[player->active_pokemon].hp -= damage;
        enemy->skills[enemy_choice].uses--;

        animate_skill(enemy->name, player->pokemon[player->active_pokemon].name,
                      enemy->skills[enemy_choice].name);
        printf("%s가 %s 스킬을 사용했습니다! %s에게 %d의 데미지를 입혔습니다.\n",
               enemy->name, enemy->skills[enemy_choice].name,
               player->pokemon[player->active_pokemon].name, damage);
        delay(2000);

        if (player->pokemon[player->active_pokemon].hp <= 0) {
            print_battle_screen(&player->pokemon[player->active_pokemon], enemy);
            printf("%s가 쓰러졌습니다!\n", player->pokemon[player->active_pokemon].name);

            // 다른 포켓몬으로 교체 가능한지 확인
            int available_pokemon = 0;
            for (int i = 0; i < MAX_POKEMON; i++) {
                if (i != player->active_pokemon && player->pokemon[i].hp > 0) {
                    available_pokemon++;
                }
            }

            if (available_pokemon > 0) {
                switch_pokemon(player);
            } else {
                printf("사용 가능한 포켓몬이 없습니다. 패배...\n");
                return;
            }
        }
    }
}

int main() {
    // 인코딩 설정
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #else
    setlocale(LC_ALL, "ko_KR.UTF-8");
    #endif

    srand(time(NULL));

    Player player;
    player.pokemon[0] = create_pokemon("피카츄", 300, 50, 40, 90);
    player.pokemon[0].skills[0] = create_skill("전기쇼크", 40, 10);
    player.pokemon[0].skills[1] = create_skill("아이언테일", 60, 5);
    player.pokemon[0].skills[2] = create_skill("10만볼트", 90, 3);
    player.pokemon[0].skills[3] = create_skill("볼트태클", 120, 1);

    player.pokemon[1] = create_pokemon("파이리", 280, 55, 35, 85);
    player.pokemon[1].skills[0] = create_skill("할퀴기", 40, 10);
    player.pokemon[1].skills[1] = create_skill("화염방사", 70, 5);
    player.pokemon[1].skills[2] = create_skill("불대문자", 100, 3);
    player.pokemon[1].skills[3] = create_skill("오버히트", 130, 1);

    player.pokemon[2] = create_pokemon("꼬부기", 320, 45, 65, 45);
    player.pokemon[2].skills[0] = create_skill("물대포", 40, 10);
    player.pokemon[2].skills[1] = create_skill("아쿠아테일", 60, 5);
    player.pokemon[2].skills[2] = create_skill("하이드로펌프", 90, 3);
    player.pokemon[2].skills[3] = create_skill("하이드로캐논", 120, 1);

    player.active_pokemon = 0;

    Pokemon enemy = create_pokemon("뮤츠", 400, 70, 60, 100);
    enemy.skills[0] = create_skill("염동력", 50, 10);
    enemy.skills[1] = create_skill("사이코키네시스", 80, 5);
    enemy.skills[2] = create_skill("환상빔", 110, 3);
    enemy.skills[3] = create_skill("미래예지", 140, 1);

    clear_console();
    printf("포켓몬 배틀 시작!\n");
    printf("%s vs %s\n", player.pokemon[player.active_pokemon].name, enemy.name);
    delay(2000);

    battle(&player, &enemy);

    return 0;
}