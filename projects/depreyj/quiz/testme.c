#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// Generate random character from 9 possibilities ([, (, {, ' ', a, x, }, ), ])
char inputChar()
{
    int randomNumber = rand() % 9;
    char randomChar;
    switch (randomNumber) {
      case 0:
        randomChar = '[';
        break;
      case 1:
        randomChar = '(';
        break;
      case 2:
        randomChar = '{';
        break;
      case 3:
        randomChar = ' ';
        break;
      case 4:
        randomChar = 'a';
        break;
      case 5:
        randomChar = 'x';
        break;
      case 6:
        randomChar = '}';
        break;
      case 7:
        randomChar = ')';
        break;
      case 8:
        randomChar = ']';
        break;
    }
    return randomChar;
}


char *inputString()
{
    int i = 0;
    static char randomStr[6];
    char randomChar;

    for (i = 0; i < 6; i++) {
      randomChar = rand() % 6;

      switch(randomChar) {
        case 0:
          randomStr[i] = 'r';
          break;
        case 1:
          randomStr[i] = 'e';
          break;
        case 2:
          randomStr[i] = 's';
          break;
        case 3:
          randomStr[i] = 'e';
          break;
        case 4:
          randomStr[i] = 't';
          break;
        case 5:
          randomStr[i] = '\0';
          break;
      }
    }
    return randomStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
