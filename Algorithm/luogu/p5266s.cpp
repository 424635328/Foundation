#include <iostream>
#include <string.h>
using namespace std;
char name[10001][20];
int score[10001];

int find(char *s, int m)
{
    for (int i = 0; i < m; i++)
    {
        if (!strcmp(s, name[i]))
            return i;
    }
    return -1;
}

int main()
{
    int m, n;
    scanf("%d", &m);
    int operations[m];
    char s[20];
    
    for (int i = 0; i < m; i++)
    {
        
        scanf("%d", &n);
        if (n != 4)
        cin >> s;
        operations[i] = n;
        switch (n)
        {
        case 1:
        {

            int j = find(s, i + 1);
            if (j != -1)
            {
                scanf("%d", &score[j]);
            }
            else
            {
                strcpy(name[i], s);
                scanf("%d", &score[i]);
            }
            printf("OK\n");
            break;
        }
        case 2:
        {

            int j = find(s, i + 1);
            if (j != -1)
            {
                printf("%d\n", score[j]);
            }
            else
            {
                printf("Not found\n");
            }
            break;
        }
        case 3:
        {

            int j = find(s, i + 1);
            if (j != -1)
            {
                strcpy(name[j], "deleted");
                score[j] = 0;
                printf("Deleted successfully\n");
            }
            else
            {
                printf("Not found\n");
            }
            break;
        }
        case 4:
            int count = 0;
            for (int i = 0; i < m; i++)
            {
                if (strcmp(name[i], "deleted") != 0 && score[i])
                {
                    count++;
                }
            }
            printf("%d\n", count);
            break;
        }
    }
    return 0;
}