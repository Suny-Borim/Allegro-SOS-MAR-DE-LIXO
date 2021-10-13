enum IDS { JOGADOR, INIMIGOS, ANIMAIS };
enum tipos{lixos,turtuga,seupaidecalcinha};
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
    int tipos;
    int x;
    int y;
    int velocidade;
    int borda_x;
    int borda_y;
    bool ativo;
};