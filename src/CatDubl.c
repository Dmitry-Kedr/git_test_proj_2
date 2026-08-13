#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc == 1)//помощь по утилите
  {
    printf("Использование: MCat [КЛЮЧ]… [ФАЙЛ]…\n\n Печатает слияние ФАЙЛ(ов) на стандартный вывод.\n");
    printf("\n-b - нумеровать непустые строки при выводе\n");
    printf("\n-E - показывать $ в конце каждой строки\n");
    printf("\n-n - нумеровать все строки при выводе\n");
    printf("\n-T - показывать символы табуляции как ^I\n");
    return 0;
  }
  uint j = 0, k = 0, v = 0, vn = 0, flagE = 0, flagn = 0, flagb = 0, T = 0;
  char *sz = {NULL};//для ключей
  char *fl[255] = {NULL};//для файлов
  char ARGT[255];//для строк из файлов
  for (size_t i = 1; i < argc; i++)//определение списка файлов
  {
    sz = argv[i];
    if(sz[0] != '-')
    {
      if(j == 255)
      {
        printf("\nСлишком большое количество файлов.\n");
        return 1;
      }
      fl[j] = argv[i];
      j++;
    }
  }
  for (size_t i = 0; i < j; i++)//пофайловое чтение
  {
    //k = 0;//отдельная нумерация
    FILE *file = fopen(fl[i], "r");
    if(!file)
    {
      printf("\nОшибка: файл %s не найден.\n\n", fl[i]);
      continue;
    }
    //printf("\n%s\n\n", fl[i]);//вывод названий фалов
    while(fgets(ARGT, 255, file) != NULL)//построчное чтение из файла
    {
      for(uint o = 0; o < argc; o++)//поиск ключей
      {
        sz = argv[o];
        if(sz[0] == '-')
        {
          for(v = 1; v < strlen(sz); v++)
          {
            if(sz[v] == 'b')//ключ b
            {
              if(flagb == 1)
              {
                continue;
              }
              for(vn = 0; vn < strlen(ARGT); vn++)
              {
                if(ARGT[vn] == '\n' || ARGT[vn] == '$')
                {                  
                  break;
                }
                else if(ARGT[vn] != ' ')
                {
                  k++;
                  flagb = 1;
                  break;
                }
              }
              continue;
            }
            if (sz[v] == 'n')//ключ n
            {
              if(flagn == 1)
              {
                continue;
              }
              k++;
              flagn = 1;
              continue;
            }
            if (sz[v] == 'E')//ключ E
            {
              if(ARGT[strlen(ARGT) - 1] == '\n')
              {
                ARGT[strlen(ARGT) - 1] = '$';
                flagE = 1;
              }
              continue;
            }
            if (sz[v] == 'T')//ключ T
            {
              for(T = 0; T < strlen(ARGT); T++)
              {
                if(ARGT[T] == '\t')
                {
                  for(int tsr = strlen(ARGT) + 1; tsr - 1 > T; tsr--)
                  {
                    ARGT[tsr + 1] = ARGT[tsr];
                    ARGT[tsr] = ARGT[tsr - 1];
                  }
                  ARGT[T] = '^';
                  ARGT[T + 1] = 'I';
                }
              }
            }
          }
        }
      }
      if(flagb == 1 || flagn == 1)
      {
        if(flagb == flagn )
        {
          printf("\nОшибка: одновременный ввод ключей n и b\n");
          return 1;
        }
        printf("   %d  ", k);
        flagb = 0;
        flagn = 0;
      }
      if(flagE == 0)//если нет $
      {
        printf("%s", ARGT);
      }
      else
      {
        printf("%s\n", ARGT);
      }
    }
    fclose(file);
  }
  return 0;
}
