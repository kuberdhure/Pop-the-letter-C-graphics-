#include <graphics.h>
#include <math.h>
#include <stdio.h>


/* A utility function to reverse a string  */
void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        swap(*(str + start), *(str + end));
        start++;
        end--;
    }
}

// Implementation of itoa()
//converts integer to array
char* itoa(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';  // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

struct BubbleData {
    int x, y;
    char ch;
    int color;
};

int generate_random(int l, int r) {
    int rand_num = (rand() % (r - l + 1)) + l;
    return rand_num;
}

void drawbb(int* score, int noOfBubbles, int bubbleInitialColor, int bubbleFinalColor) {
    struct BubbleData bubbles[noOfBubbles];

    int sectionWidth = int((float)getmaxx() / noOfBubbles);
    for (int i = 0; i < noOfBubbles; i++) {
        bubbles[i].x = generate_random(((i * sectionWidth) + 30), (((i + 1) * sectionWidth) - 30));
        bubbles[i].y = generate_random(getmaxy(), 1.5 * getmaxy());
        int isCapital = generate_random(0, 1);
        if (isCapital) {
            bubbles[i].ch = generate_random(65, 90);
        } else {
            bubbles[i].ch = generate_random(97, 122);
        }
        bubbles[i].color = bubbleInitialColor;
    }

    int isAllBubblesDone = 0;
    do {
        // Score
        char scoreText[100];
        itoa(*score, scoreText, 10);
        outtextxy(getmaxx() - 70, 10, "Score: ");
        outtextxy(getmaxx() - 20, 10, scoreText);

        // Bubbles
        for (int i = 0; i < noOfBubbles; i++) {
            char chText[2] = {bubbles[i].ch, '\0'};
            setfillstyle(SOLID_FILL, bubbles[i].color);
            circle(bubbles[i].x, bubbles[i].y, 30);
            outtextxy(bubbles[i].x, bubbles[i].y, chText);
            floodfill(bubbles[i].x, bubbles[i].y, 15);
            bubbles[i].y -= 1;
        }

        // Check For Key Press
        if(kbhit()){
        int userCh = getch();
        printf("User Pressed: %c\n", userCh);
        
        for (int i = 0; i < noOfBubbles; i++) {
            if (bubbles[i].ch == userCh && bubbles[i].color != bubbleFinalColor) {
                *score += 1;
                bubbles[i].color = bubbleFinalColor;
                printf("%c Bubble Done\n", bubbles[i].ch);
            }
        }
        
        printf("\n");
        }
        // Delay
       

        // Clear Screen
        cleardevice();

        isAllBubblesDone = 1;
        for (int i = 0; i < noOfBubbles; i++) {
            if (bubbles[i].y >= 0) {
                isAllBubblesDone = 0;
                break;
            }
        }
    } while (!isAllBubblesDone);
}

int main() {
    int score = 0;
      
    // initwindow(1280, 720);
    int gd = DETECT, gm;
    initgraph(&gd,&gm,"");

    while (1) {
        int noOfBubbles = generate_random(3, 7);
        drawbb(&score, noOfBubbles, BLUE, GREEN);
    }

    getch();
    closegraph();

    return 0;
}
