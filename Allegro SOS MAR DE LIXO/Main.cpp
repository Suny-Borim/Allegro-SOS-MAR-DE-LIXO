#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <ctime>
//-----Arquivos criados------//

#include "objetos.h"

//-----Variáveis Globais-----//

const int largura_t = 850;
const int altura_t = 400;
const int FPS = 60;
const int NUM_COMETAS = 10;


enum TECLAS { CIMA, BAIXO, ESQUERDA, DIREITA, SPACE };

//-----Protótipos-----//
void InitNave(NaveEspacial& nave);
void DesenhaNave(NaveEspacial& nave);

void MoveNaveCima(NaveEspacial& nave);
void MoveNaveBaixo(NaveEspacial& nave);
void MoveNaveDireita(NaveEspacial& nave);
void MoveNaveEsquerda(NaveEspacial& nave);

void InitCometas(Cometas cometas[], int tamanho);
void LiberaCometas(Cometas cometas[], int tamanho);
void AtualizarCometas(Cometas cometas[], int tamanho);
void DesenhaCometas(Cometas cometas[], int tamanho);

int main() {
    //-----Configurações do sistema-----//
    al_init();
    al_init_native_dialog_addon();
    al_init_primitives_addon();
    al_init_image_addon();

    al_install_keyboard();
    al_init_primitives_addon();
    //-----Variáveis do Jogo-----//
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    ALLEGRO_TIMER* timer = NULL;

    //-----Adicionando imagens-----//
    ALLEGRO_BITMAP* fundo = al_load_bitmap("imgs\\fundo.png");
    bool fim = false;
    bool desenha = true;
    bool teclas[] = { false, false, false, false, false };
    //-----Inicialização de Objetos-----//
    NaveEspacial nave;
    Cometas cometas[NUM_COMETAS];
    //-----Inicialização do Allegro e da Display-----//
    ALLEGRO_DISPLAY* display = NULL;

    if (!al_init()) {
        al_show_native_message_box(NULL, "AVISO", "ERRO", "ERRO AO INICIALIZAR O ALLEGRO!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    display = al_create_display(largura_t, altura_t);

    if (!display) {
        al_show_native_message_box(NULL, "AVISO", "ERRO", "ERRO AO ABRIR O JOGO!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }


    //-----Criação de fila e demais dispositivos------//
    fila_eventos = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    //-----Registro de Sources-----//
    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    //-----Funções iniciais-----//
    srand(time(NULL));
    InitNave(nave);
    InitCometas(cometas, NUM_COMETAS);

    //-----Loop principal----//
    al_start_timer(timer);


    while (!fim) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);


        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fim = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                fim = true;
                break;
            case ALLEGRO_KEY_UP:
                teclas[CIMA] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                teclas[BAIXO] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                teclas[DIREITA] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                teclas[ESQUERDA] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                teclas[SPACE] = true;
                break;
            }
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                teclas[CIMA] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                teclas[BAIXO] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                teclas[DIREITA] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                teclas[ESQUERDA] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                teclas[SPACE] = false;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER) {
            desenha = true;

            if (teclas[CIMA])
                MoveNaveCima(nave);
            if (teclas[BAIXO])
                MoveNaveBaixo(nave);
            if (teclas[DIREITA])
                MoveNaveDireita(nave);
            if (teclas[ESQUERDA])
                MoveNaveEsquerda(nave);
            LiberaCometas(cometas, NUM_COMETAS);
            AtualizarCometas(cometas, NUM_COMETAS);
        }

        //----Desenho temporario-----//
        if (desenha && al_is_event_queue_empty(fila_eventos)) {
            al_draw_bitmap(fundo, 0, -150, 0);

            desenha = false;

            
            DesenhaCometas(cometas, NUM_COMETAS);
            DesenhaNave(nave);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }


    }



    //-----Finalizações do programa------//
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(fundo);
    return 0;
}

//-----Definição de Funções-----//

//-----Barco-----//
void InitNave(NaveEspacial& nave) {
    nave.x = 20;
    nave.y = altura_t / 2;
    nave.ID = JOGADOR;
    nave.vidas = 3;
    nave.velocidade = 3, 7;
    nave.borda_x = 6;
    nave.borda_y = 7;
    nave.pontos = 0;

}
void DesenhaNave(NaveEspacial& nave) {
    al_draw_filled_rectangle(nave.x, nave.y - 18, nave.x + 20, nave.y - 14, al_map_rgb(255, 0, 0));

    al_draw_filled_triangle(nave.x, nave.y - 24, nave.x + 24, nave.y, nave.x, nave.y, al_map_rgb(0, 255, 0));
    al_draw_filled_rectangle(nave.x - 24, nave.y - 4, nave.x + 30, nave.y + 4, al_map_rgb(0, 0, 255));
}
void MoveNaveCima(NaveEspacial& nave) {
    nave.y -= nave.velocidade;
    if (nave.y < altura_t / 2)
        nave.y = altura_t / 2;

}
void MoveNaveBaixo(NaveEspacial& nave) {
    nave.y += nave.velocidade;

    if (nave.y > altura_t)
        nave.y = altura_t;
}
void MoveNaveDireita(NaveEspacial& nave) {
    nave.x += nave.velocidade;

    if (nave.x > largura_t / 2)
        nave.x = largura_t / 2;
}
void MoveNaveEsquerda(NaveEspacial& nave) {
    nave.x -= nave.velocidade;

    if (nave.x < 0)
        nave.x = 0;
}
void InitCometas(Cometas cometas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        cometas[i].ID = INIMIGOS;
        cometas[i].velocidade = 5;
        cometas[i].borda_x = 18;
        cometas[i].borda_y = 18;
        cometas[i].ativo = false;
    }
}
void LiberaCometas(Cometas cometas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (!cometas[i].ativo) {
            if (rand() % 500 == 0) {
                cometas[i].x = largura_t;
                cometas[i].y = altura_t/2 + rand() % altura_t/2;
                cometas[i].tipos = rand() % 3;
                cometas[i].ativo = true;
                break;
            }
        }
    }
}
void AtualizarCometas(Cometas cometas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (cometas[i].ativo) {
            cometas[i].x -= cometas[i].velocidade;
            if (cometas[i].x < 0) {
                cometas[i].ativo = false;
            }
        }
    }
}
void DesenhaCometas(Cometas cometas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        switch (cometas[i].ativo){
        case 1:
            switch (cometas[i].tipos)
            {
            case 0:
                al_draw_filled_circle(cometas[i].x, cometas[i].y, 20, al_map_rgb(255, 0, 0));
                break;
            case 1:
                al_draw_filled_circle(cometas[i].x, cometas[i].y, 20, al_map_rgb(255, 255, 0));
                break;
            case 2:
                al_draw_filled_circle(cometas[i].x, cometas[i].y, 20, al_map_rgb(255, 0, 255));
                break;
            }break;
        }   
    }
}
