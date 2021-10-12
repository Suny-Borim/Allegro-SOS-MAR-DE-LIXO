enum IDS { JOGADOR, INIMIGOS };
struct NaveEspacial {
    int ID;
    int x;
    int y;
    int vidas;
    float velocidade;
    int borda_x;
    int borda_y;
    int pontos;
};
struct Cometas {
    int ID;
    int x;
    int y;
    int velocidade;
    int borda_x;
    int borda_y;
    bool ativo;
};