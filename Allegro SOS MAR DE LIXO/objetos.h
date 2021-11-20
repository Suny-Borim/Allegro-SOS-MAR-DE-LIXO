enum IDS { JOGADOR, INIMIGOS, ANIMAIS, PROJETIL };
enum tipos { tartaruga,garrafa,macaco};
bool inicio;
struct BARCO {
    int ID;
    int x;
    int y;
    int vidas;
    float velocidade;
    int borda_x;
    int borda_y;
    int pontos;
    bool arma;

    ALLEGRO_BITMAP* image;
};
struct JogadosnoMAR {
    int ID;
    int tipos;
    int x;
    int y;
    int velocidade;
    int borda_x;
    int borda_y;
    bool ativo;
};
//objeto
struct Projeteis {
    int ID;
    int x;
    int y;
    int velocidade;
    bool ativo;
};
struct fundo {
    float x;
    float y;

    ALLEGRO_BITMAP* fundo2 = al_load_bitmap("imgs\\fundo2.png");
};