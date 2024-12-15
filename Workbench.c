#include <stdio.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 10

// atualiza a tela 
void renderizar (char frame [HEIGHT][WIDTH], char prev_frame [HEIGHT][WIDTH]) 
{
    for (int y = 0; y < HEIGHT; y++) 
        for (int x = 0; x < WIDTH; x++)
            if (frame[y][x] != prev_frame[y][x])
                printf("\033[%d;%dH%c", y + 1, x + 1, frame [y][x]);
    fflush (stdout);
}

// main
int main (void) 
{
    char frame [HEIGHT][WIDTH] = {{' '}};
    char prev_frame [HEIGHT][WIDTH] = {{' '}};

    printf ("\033[H\033[J"); // Limpa a tela no início

    for (int h = 21, m = 39, s = 0; 1;)
    {
        memset (frame, ' ', sizeof (frame));

        // decimos de hora
        frame [2][2] = '0' + h/10;
        frame [2][3] = '0' + h%10;
        frame [2][4] = ':';
        frame [2][5] = '0' + m/10;
        frame [2][6] = '0' + m%10;
        frame [2][7] = ':';
        frame [2][8] = '0' + s/10;
        frame [2][9] = '0' + s%10;
        
        renderizar (frame, prev_frame);

        memcpy (prev_frame, frame, sizeof (frame));
        usleep (1000000);

        if (++s >= 60) {s = 0; m++;}
        if (  m >= 60) {m = 0; h++;}
        if (  h >= 24) {h = 0;     }
    }

    return 0;
}
