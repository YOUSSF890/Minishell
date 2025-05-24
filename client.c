// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

char board[9] = {'1','2','3','4','5','6','7','8','9'};

void draw_board() {
    printf("\n");
    for(int i = 0; i < 9; i++) {
        printf(" %c ", board[i]);
        if ((i+1)%3 == 0)
            printf("\n");
    }
    printf("\n");
}

int check_winner() {
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int i = 0; i < 8; i++) {
        if (board[wins[i][0]] == board[wins[i][1]] && board[wins[i][1]] == board[wins[i][2]])
            return 1;
    }
    return 0;
}

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[2];
    int move;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    printf("Enter server IP address: ");
    char ip[20]; scanf("%s", ip);
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Connected! You are 'O', opponent is 'X'\n");

    while (1) {
        printf("Waiting for opponent...\n");
        read(sock, &move, 1);
        if (board[move] == 'X' || board[move] == 'O') continue;
        board[move] = 'X';
        draw_board();

        if (check_winner()) {
            printf("You lose!\n");
            break;
        }

        printf("Your move (1-9): ");
        scanf("%d", &move);
        move--;
        if (board[move] == 'X' || board[move] == 'O') continue;
        board[move] = 'O';
        write(sock, &move, 1);

        if (check_winner()) {
            draw_board();
            printf("You win!\n");
            break;
        }
    }

    close(sock);
    return 0;
}