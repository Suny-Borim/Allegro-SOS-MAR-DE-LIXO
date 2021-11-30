#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cstdlib>
#include <ctime>
//-----Arquivos criados------//

#include "objetos.h"


//-----Variáveis Globais-----//
//Background BG;
//Background(MG);
//Background(FG);
int gamestart = 0;
const int largura_t = 850;
const int altura_t = 400;
const int FPS = 60;
const int NUM_LixosOuBichos = 10;
const int NUM_BALAS = 10;

ALLEGRO_BITMAP* bgImage = NULL;
ALLEGRO_BITMAP* mgImage = NULL;
ALLEGRO_BITMAP* fgImage = NULL;

ALLEGRO_SAMPLE* trilha_sonora = NULL;
ALLEGRO_SAMPLE* laser = NULL;
ALLEGRO_SAMPLE* explosao = NULL;
ALLEGRO_SAMPLE* aplausos = NULL;

ALLEGRO_SAMPLE_INSTANCE* inst_trilha_sonora = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_laser = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_explosao = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_aplausos = NULL;

enum TECLAS { CIMA, BAIXO, ESQUERDA, DIREITA, SPACE };

//-----Protótipos-----//
void InitNave(BARCO& barquin, ALLEGRO_BITMAP* image);
void DesenhaNave(BARCO& barquin);

void MoveNaveCima(BARCO& barquin);
void MoveNaveBaixo(BARCO& barquin);
void MoveNaveDireita(BARCO& barquin);
void MoveNaveEsquerda(BARCO& barquin);

void InitBalao(Balao& balaozin, ALLEGRO_BITMAP* image);
void DesenhaBalao(Balao& balaozin);
void AtualizaBalao(Balao& balaozin);

void InitFundo(FUNDO& move, ALLEGRO_BITMAP* image);
void DesenhaFundo(FUNDO& move);
void AtualizaFundo(FUNDO& move);

void InitCometas(JogadosnoMAR BichinhosELixos[], int tamanho,ALLEGRO_BITMAP*image,ALLEGRO_BITMAP*image2);
void LiberaCometas(JogadosnoMAR BichinhosELixos[], int tamanho);
void AtualizarCometas(JogadosnoMAR BichinhosELixos[], int tamanho);
void DesenhaCometas(JogadosnoMAR BichinhosELixos[], int tamanho);
void CometaColidido(JogadosnoMAR BichinhosELixos[], int c_tamanho, BARCO& barquin);

void InitBalas(Projeteis balas[], int tamanho);
void AtiraBalas(Projeteis balas[], int tamanho, BARCO barquin);
void AtualizarBalas(Projeteis balas[], int tamanho, BARCO barquin);
void DesenhaBalas(Projeteis balas[], int tamanho);
void BalaColidida(Projeteis balas[], int b_tamanho, JogadosnoMAR BichinhosELixos[], int c_tamanho, BARCO& barquin);

//void InitBackground(Background& back, float x, float y, float velx, float vely, int largura_t, int altura_t, int dirx, int diry, ALLEGRO_BITMAP* image);
//void UpdateBackground(Background& back);
//void DrawBackground(Background& back);


int main() {
    //-----Configurações do sistema-----//
    al_init();
    al_init_native_dialog_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    //bgImage = al_load_bitmap("imgs\\parte3.png");
    //mgImage = al_load_bitmap("imgs\\parte2.png");
    //fgImage = al_load_bitmap("imgs\\parte1.png");

    //InitBackground(BG, 0, 0, 1, 0, 850, 400, -1, 1, bgImage);
    //InitBackground(MG, 0, 0, 2, 0, 850, 400, -1, 1, mgImage);
    //InitBackground(FG, 0, 0, 3, 0, 850, 400, -1, 1, fgImage);
    

    ALLEGRO_FONT* arial = al_load_font("arial.ttf", 30, NULL);
    ALLEGRO_FONT* fast = al_load_font("fast99.ttf", 30, NULL);
    ALLEGRO_FONT* matrix = al_load_font("matrix.ttf", 30, NULL);



    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10);


    al_install_keyboard();
    al_init_primitives_addon();

    //-----Variáveis do Jogo-----//
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* bgImage = NULL;
    ALLEGRO_BITMAP* mgImage = NULL;
    ALLEGRO_BITMAP* fgImage = NULL;

    

    bool fim = false;
    bool desenha = true;
    
    
    bool teclas[] = { false, false, false, false, false };
    bool tocar_aplausos = false;

    //-----Adicionando imagens-----//
    ALLEGRO_BITMAP* START = al_load_bitmap("imgs\\gamestart.png");
    ALLEGRO_BITMAP* fundo = al_load_bitmap("imgs\\fundo.png");
    ALLEGRO_BITMAP* fundoINT = al_load_bitmap("imgs\\fundo24.png");
    ALLEGRO_BITMAP* BARRA = al_load_bitmap("imgs\\Barra.png");
    ALLEGRO_BITMAP* WIN = al_load_bitmap("imgs\\WIN.png");
    ALLEGRO_BITMAP* LOSE = al_load_bitmap("imgs\\LOSE.png");


    ALLEGRO_BITMAP* barco;

    barco = al_load_bitmap("imgs\\test.png");


    ALLEGRO_BITMAP* latinha;
    latinha = al_load_bitmap("imgs\\Latinha.png");

    ALLEGRO_BITMAP* balao;
    balao = al_load_bitmap("imgs\\Balao.png");

    ALLEGRO_BITMAP* tortuga;
    tortuga = al_load_bitmap("imgs\\tortuga2.png");

    Balao balaozin;
    FUNDO move;
    //-----Inicialização de Objetos-----//
    BARCO barquin;
    JogadosnoMAR BichinhosELixos[NUM_LixosOuBichos];
    Projeteis balas[NUM_BALAS];

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

    trilha_sonora = al_load_sample("trilha_sonora.ogg");
    inst_trilha_sonora = al_create_sample_instance(trilha_sonora);
    al_attach_sample_instance_to_mixer(inst_trilha_sonora, al_get_default_mixer());
    al_set_sample_instance_playmode(inst_trilha_sonora, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(inst_trilha_sonora, 0.5);


    //-----Registro de Sources-----//
    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));

    //-----Funções iniciais-----//
    srand(time(NULL));
    InitNave(barquin, barco);
    InitBalao(balaozin, balao);
    InitCometas(BichinhosELixos, NUM_LixosOuBichos,latinha,tortuga);
    InitFundo(move, fundoINT);
 
    InitBalas(balas, NUM_BALAS);


    //-----Loop principal----//
    al_start_timer(timer);

gamestart:
    while (!fim) {



        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);


        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fim = true;
        }

        if (barquin.vidas == 0||barquin.pontos<0) {
            switch (ev.keyboard.keycode) {

            case ALLEGRO_KEY_ENTER:
                barquin.vidas = 5;
                barquin.pontos = 0;

                goto gamestart;

                break;

            case ALLEGRO_KEY_DOWN:
                teclas[BAIXO] = true;
                break;
            }
        }
        else if (barquin.pontos == 1000) {

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
                AtiraBalas(balas, NUM_BALAS, barquin);
                break;
            case ALLEGRO_KEY_ENTER:
                gamestart = 1;
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
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER && gamestart == 1) {
            desenha = true;

            if (teclas[CIMA])
                MoveNaveCima(barquin);
            if (teclas[BAIXO])
                MoveNaveBaixo(barquin);
            if (teclas[DIREITA])
                MoveNaveDireita(barquin);
            if (teclas[ESQUERDA])
                MoveNaveEsquerda(barquin);
            if (teclas[SPACE])
                AtualizarBalas(balas, NUM_BALAS, barquin);

            //UpdateBackground(BG);
           //UpdateBackground(FG);
            //UpdateBackground(MG);
            AtualizaFundo(move);
            LiberaCometas(BichinhosELixos, NUM_LixosOuBichos);
            AtualizarCometas(BichinhosELixos, NUM_LixosOuBichos);
            AtualizaBalao(balaozin);
            CometaColidido(BichinhosELixos, NUM_LixosOuBichos, barquin);
            BalaColidida(balas, NUM_BALAS, BichinhosELixos, NUM_LixosOuBichos, barquin);
            al_play_sample_instance(inst_trilha_sonora);
        }

        //----Desenho temporario-----//
        if (desenha && al_is_event_queue_empty(fila_eventos) && gamestart == 0) {
            

            al_draw_bitmap(START, 0, 0, 0);
            desenha = false;
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
        }
        if (desenha && al_is_event_queue_empty(fila_eventos) && gamestart == 1) {
            al_draw_bitmap(fundo, 0, -150, 0);
            DesenhaFundo(move);
           // DrawBackground(BG);
           // DrawBackground(FG);
           // DrawBackground(MG);
            desenha = false;
            DesenhaBalas(balas, NUM_BALAS);
            DesenhaCometas(BichinhosELixos, NUM_LixosOuBichos);
            DesenhaNave(barquin);
            DesenhaBalao(balaozin);
            al_draw_bitmap(BARRA, 0, 0, 0);
            al_draw_textf(matrix, al_map_rgb(0, 0, 0), largura_t * 0.10, 11, 0, "%d", barquin.vidas);
            al_draw_textf(matrix, al_map_rgb(0, 0, 0), 190, 11, 0, "%d", barquin.pontos);
            if (barquin.vidas == 0 || barquin.pontos < 0) {
                al_draw_bitmap(LOSE, 0, altura_t / 8, 0);

            }
            else if (barquin.pontos == 1000) {
                al_draw_bitmap(WIN, 0, 0, 0);

            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));

        }
    }



    //-----Finalizações do programa------//
    
    al_destroy_display(display);
    al_destroy_bitmap(START);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(BARRA);
    al_destroy_bitmap(LOSE);
    al_destroy_bitmap(WIN);
    al_destroy_font(matrix);
    al_destroy_bitmap(barco);
    al_destroy_bitmap(latinha);
    al_destroy_bitmap(bgImage);
    al_destroy_bitmap(fgImage);
    al_destroy_bitmap(mgImage);
    
    

    al_destroy_sample(trilha_sonora);
    al_destroy_sample_instance(inst_trilha_sonora);

    return 0;
}

//-----Definição de Funções-----//

//-----Barco-----//


//void InitBackground(Background& back, float x, float y, float velx, float vely, int largura_t, int altura_t, int dirx, int diry, ALLEGRO_BITMAP* image) {
   // back.x = x;
   // back.y = y;
   // back.vely = vely;
   // back.velx = velx;
   // back.largura_t = largura_t;
   // back.altura_t = altura_t;
   // back.dirx = dirx;
   // back.diry = diry;
   // back.image = image;
//}
//void DrawBackground(Background& back)
//{
  //  al_draw_bitmap(back.image, back.x, back.y, 0);
    //if (back.x + back.altura_t < altura_t)
      //  al_draw_bitmap(back.image, back.x + back.altura_t, back.y, 0);
//}

//void UpdateBackground(Background& back)
// {
  //  back.x += back.velx * back.dirx;
  //  if (back.x + back.altura_t <= 0)
  //      back.x = 0;
//}


void InitNave(BARCO& barquin, ALLEGRO_BITMAP* image) {
    barquin.x = 20;
    barquin.y = altura_t / 2;
    barquin.ID = JOGADOR;
    barquin.vidas = 5;
    barquin.velocidade = 4, 6;
    barquin.borda_x =10;
    barquin.borda_y = 15;
    barquin.pontos = 0;
    barquin.arma = true;
    barquin.image = image;
}
void InitFundo(FUNDO& move, ALLEGRO_BITMAP* image) {
    move.x = 0;
    move.y = -150;
    move.largura_t = largura_t;
    move.altura_t = altura_t;
    move.velocidade = 1;

    move.image = image;
}
void DesenhaFundo(FUNDO& move) {
    al_draw_bitmap(move.image, move.x, move.y, NULL);
}
void AtualizaFundo(FUNDO& move) {
    move.x -= move.velocidade;
        if (move.x == -largura_t*2.8) {
            move.x = 0;
        }
        if (move.x == -largura_t/2) {
            move.x == largura_t / 2;
        }
}
void DesenhaNave(BARCO& barquin) {
    al_draw_bitmap(barquin.image, barquin.x, barquin.y, NULL);
}
void InitBalao(Balao& balaozin, ALLEGRO_BITMAP* image) {
    balaozin.x = largura_t;
    balaozin.y = rand() % altura_t / 4 + 20;
    balaozin.velocidade = 0.5;
    balaozin.image = image;
}
void DesenhaBalao(Balao& balaozin) {
    al_draw_bitmap(balaozin.image, balaozin.x, balaozin.y, NULL);
}
void AtualizaBalao(Balao& balaozin) {
    if (balaozin.x > -80)
        balaozin.x -= balaozin.velocidade;
    else {
        balaozin.x = largura_t;
        balaozin.y = rand() % altura_t / 4 + 20;
    }
}
void MoveNaveCima(BARCO& barquin) {
    barquin.y -= barquin.velocidade;
    if (barquin.y < altura_t / 2 - altura_t * 0.10)
        barquin.y = altura_t / 2 - altura_t * 0.10;

}
void MoveNaveBaixo(BARCO& barquin) {
    barquin.y += barquin.velocidade;

    if (barquin.y > altura_t - altura_t * 0.10)
        barquin.y = altura_t - altura_t * 0.10;
}
void MoveNaveDireita(BARCO& barquin) {
    barquin.x += barquin.velocidade;

    if (barquin.x > largura_t / 2)
        barquin.x = largura_t / 2;
}
void MoveNaveEsquerda(BARCO& barquin) {
    barquin.x -= barquin.velocidade;

    if (barquin.x < 0)
        barquin.x = 0;
}
void InitCometas(JogadosnoMAR BichinhosELixos[], int tamanho,ALLEGRO_BITMAP*image,ALLEGRO_BITMAP*image2) {
    for (int i = 0; i < tamanho; i++) {
        BichinhosELixos[i].ID = INIMIGOS;
        BichinhosELixos[i].velocidade = 3;
        BichinhosELixos[i].borda_x = 18;
        BichinhosELixos[i].borda_y = 22;
        BichinhosELixos[i].ativo = false;
        BichinhosELixos[i].tipos = rand() %2;
        if(BichinhosELixos[i].tipos %2==0)
        BichinhosELixos[i].image = image2;
        else
        BichinhosELixos[i].image = image;
    }
}
void LiberaCometas(JogadosnoMAR BichinhosELixos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (!BichinhosELixos[i].ativo) {
            if (rand() % 500 == 0) {
                BichinhosELixos[i].x = largura_t;
                BichinhosELixos[i].y = altura_t / 2 + rand() % altura_t / 2;
             
                BichinhosELixos[i].ativo = true;
                break;
            }
        }
    }
}
void AtualizarCometas(JogadosnoMAR BichinhosELixos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (BichinhosELixos[i].ativo) {
            BichinhosELixos[i].x -= BichinhosELixos[i].velocidade;

        }
    }
}
void DesenhaCometas(JogadosnoMAR BichinhosELixos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (BichinhosELixos[i].ativo) {
            al_draw_bitmap(BichinhosELixos[i].image, BichinhosELixos[i].x, BichinhosELixos[i].y, 0);
        }
          
    }
}
void CometaColidido(JogadosnoMAR BichinhosELixos[], int c_tamanho, BARCO& barquin) {
    for (int i = 0; i < c_tamanho; i++) {
        if (BichinhosELixos[i].ativo) {

            if ((BichinhosELixos[i].x - BichinhosELixos[i].borda_x) < (barquin.x + barquin.borda_x) &&
                (BichinhosELixos[i].x + BichinhosELixos[i].borda_x) > (barquin.x + barquin.borda_x) &&
                (BichinhosELixos[i].y - BichinhosELixos[i].borda_y) < (barquin.y + barquin.borda_y) &&
                (BichinhosELixos[i].y + BichinhosELixos[i].borda_y) > (barquin.y + barquin.borda_y) &&
                BichinhosELixos[i].tipos % 2 == 0)
            {

                BichinhosELixos[i].ativo = false;
                barquin.pontos += 50;
            }
            if ((BichinhosELixos[i].x - BichinhosELixos[i].borda_x) < (barquin.x + barquin.borda_x) &&
                (BichinhosELixos[i].x + BichinhosELixos[i].borda_x) > (barquin.x + barquin.borda_x) &&
                (BichinhosELixos[i].y - BichinhosELixos[i].borda_y) < (barquin.y + barquin.borda_y) &&
                (BichinhosELixos[i].y + BichinhosELixos[i].borda_y) > (barquin.y + barquin.borda_y) &&
                BichinhosELixos[i].tipos % 2 != 0)
            {
                BichinhosELixos[i].ativo = false;
                barquin.vidas--;
            }

            else if (BichinhosELixos[i].x < 0) {
                BichinhosELixos[i].ativo = false;
                barquin.pontos -= 50;
            }

        }
    }
}


//Projeteis

void BalaColidida(Projeteis balas[], int b_tamanho, JogadosnoMAR BichinhosELixos[], int c_tamanho, BARCO& barquin)
{
    for (int i = 0; i < b_tamanho; i++)
    {
        if (balas[i].ativo)
        {
            for (int j = 0; j < c_tamanho; j++)
            {
                if (BichinhosELixos[j].ativo)
                {
                    if (barquin.arma == true) {
                        if (balas[i].x -17> (BichinhosELixos[j].x - BichinhosELixos[j].borda_x) &&
                            balas[i].x -17 < (BichinhosELixos[j].x + BichinhosELixos[j].borda_x) &&
                            balas[i].y -17>(BichinhosELixos[j].y - BichinhosELixos[j].borda_y) &&
                            balas[i].y  -17< (BichinhosELixos[j].y + BichinhosELixos[j].borda_y) && BichinhosELixos[j].tipos % 2 == 0)
                        {
                            balas[i].ativo = false;
                            BichinhosELixos[j].ativo = false;
                            barquin.pontos -= 50;
                        }
                    }
                    if (barquin.arma == true)
                        if (balas[i].x -17> (BichinhosELixos[j].x - BichinhosELixos[j].borda_x) &&
                            balas[i].x  -17< (BichinhosELixos[j].x + BichinhosELixos[j].borda_x) &&
                            balas[i].y  -17>(BichinhosELixos[j].y - BichinhosELixos[j].borda_y) &&
                            balas[i].y  -17 < (BichinhosELixos[j].y + BichinhosELixos[j].borda_y) && BichinhosELixos[j].tipos % 2 != 0)
                        {
                            balas[i].ativo = false;
                            BichinhosELixos[j].ativo = false;
                            barquin.pontos += 50;
                        }
                }
            }
        }
    }
}

void InitBalas(Projeteis balas[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        balas[i].ID = PROJETIL;
        balas[i].velocidade = 4;
        balas[i].ativo = false;
    }
}
void AtiraBalas(Projeteis balas[], int tamanho, BARCO barquin)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (!balas[i].ativo)
        {
            balas[i].x = barquin.x + 25;
            balas[i].y = barquin.y + barquin.y * 0.18;
            balas[i].ativo = true;
            break;
        }
    }
}
void AtualizarBalas(Projeteis balas[], int tamanho, BARCO barquin)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (balas[i].ativo)
        {
            balas[i].x += balas[i].velocidade;

            if (balas[i].x > largura_t)
                balas[i].ativo = false;
        }
    }
}
void DesenhaBalas(Projeteis balas[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (balas[i].ativo)
        {
            al_draw_filled_circle(balas[i].x, balas[i].y, 4, al_map_rgb(0, 0, 255));
        }
    }

}

