//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//int main() {
//    srand(time(0));  // 初始化随机数生成器
//    int playerpredictions[5], gameresults[5], points = 0;
//    int playerwins = 0, gamewins = 0, playerfails = 0, gamefails = 0;
//
//    printf("请输入你的预测（0表示输，1表示赢, 按enter键进行下一次输入）：\n");
//    for (int i = 0; i < 5; i++) {
//        if (scanf_s("%d", &playerpredictions[i]) != 1 || (playerpredictions[i] != 0 && playerpredictions[i] != 1)) {
//            printf("非法输入！请重新输入。\n");
//            i--;  // 重新读取这一次的输入
//            continue;
//        }
//        // 计算玩家和游戏的胜利次数
//        playerwins += (1 - playerpredictions[i]);
//        playerfails += playerpredictions[i];
//        if (playerwins == 3 || playerfails == 3) {
//            break;
//        }
//    }
//    for (int i = 0; i < 5; i++) {
//        gameresults[i] = rand() % 2;  // 生成游戏结果
//        if (playerpredictions[i] == gameresults[i]) {
//            points += 100;  // 如果预测正确，增加100点
//        }
//        gamewins += gameresults[i];
//        gamefails += (1 - gameresults[i]);
//        // 如果任一方赢了三局，游戏结束
//        if (gamewins == 3 || gamefails == 3) {
//            break;
//        }
//    }
//    printf("你的预测是：\n");
//    for (int i = 0; i < 5 && (playerpredictions[i] == 0 || playerpredictions[i] == 1); i++) {
//        printf("%d ", playerpredictions[i]);
//    }
//    printf("\n");
//
//    printf("游戏结果是：\n");
//    for (int i = 0; i < 5 && (gameresults[i] == 0 || gameresults[i] == 1); i++) {
//        printf("%d ", gameresults[i]);
//    }
//    printf("\n");
//
//    printf("你的最终得分是：%d\n", points);
//
//    return 0;
//}
