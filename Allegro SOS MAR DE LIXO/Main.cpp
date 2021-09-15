#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
using namespace std;

int main() {

    al_init();
    ALLEGRO_DISPLAY* janela = al_create_display(800, 600);
    al_set_window_title(janela, "jogo");
    while (true)
        al_flip_display();

    return 0;
}