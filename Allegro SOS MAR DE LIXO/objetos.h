enum IDS { JOGADOR, INIMIGOS, ANIMAIS, PROJETIL };
enum tipos { tartaruga, garrafa, macaco };
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
struct Balao {
    float x;
    float y;
    float velocidade;
    bool maximo;
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

    ALLEGRO_BITMAP* image;
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
    float velx;
    float vely;
    int dirx;
    int diry;
    int largura_t;
    int altura_t;

    ALLEGRO_BITMAP* image;
};
struct FUNDO {
    float x;
    float y;
    int largura_t;
    int altura_t;
    float velocidade;

    ALLEGRO_BITMAP* image;
};
