#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));  // ��ʼ�������������
    int playerpredictions[5], gameresults[5], points = 0;
    int playerwins = 0, gamewins = 0, playerfails = 0, gamefails = 0;

    printf("���������Ԥ�⣨0��ʾ�䣬1��ʾӮ, ��enter��������һ�����룩��\n");
    for (int i = 0; i < 5; i++) {
        if (scanf("%d", &playerpredictions[i]) != 1 || (playerpredictions[i] != 0 && playerpredictions[i] != 1)) {
            printf("�Ƿ����룡���������롣\n");
            i--;  // ���¶�ȡ��һ�ε�����
            continue;
        }
        // ������Һ���Ϸ��ʤ������
        playerwins += (1 - playerpredictions[i]);
        playerfails += playerpredictions[i];
        if (playerwins == 3 || playerfails == 3) {
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        gameresults[i] = rand() % 2;  // ������Ϸ���
        if (playerpredictions[i] == gameresults[i]) {
            points += 100;  // ���Ԥ����ȷ������100��
        }
        gamewins += gameresults[i];
        gamefails += (1 - gameresults[i]);
        // �����һ��Ӯ�����֣���Ϸ����
        if (gamewins == 3 || gamefails == 3) {
            break;
        }
    }
    printf("���Ԥ���ǣ�\n");
    for (int i = 0; i < 5 && (playerpredictions[i] == 0 || playerpredictions[i] == 1); i++) {
        printf("%d ", playerpredictions[i]);
    }
    printf("\n");

    printf("��Ϸ����ǣ�\n");
    for (int i = 0; i < 5 && (gameresults[i] == 0 || gameresults[i] == 1); i++) {
        printf("%d ", gameresults[i]);
    }
    printf("\n");

    printf("������յ÷��ǣ�%d\n", points);

    return 0;
}
