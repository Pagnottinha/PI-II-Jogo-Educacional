enum IDS {PLAYER, LANCA, ESCUDO, INIMIGO, ESPADA};
enum POS {X, Y, BX, BY};
enum DIMENSOES {W, H};

typedef struct
{
	int ID;
	int pos[4];
	int dimensoes[2];
	int vida;
	int velocidade;
	ALLEGRO_BITMAP* imagem;
} Player;

void initPlayer(Player* player, ALLEGRO_DISPLAY* display);
ALLEGRO_BITMAP* criarBitmapPlayer(Player* player, ALLEGRO_DISPLAY* display);
void desenharPlayer(Player* player);
void andarPlayerCima(Player* player);
void andarPlayerBaixo(Player* player);
void andarPlayerEsqueda(Player* player);
void andarPlayerDireita(Player* player);

typedef struct
{
	int ID;
	int pos[4];
	int dano;
	int dimensoes[2];
	Player* player;
	ALLEGRO_BITMAP* imagem;
} Lanca;

void initLanca(Lanca* lanca, Player* player, ALLEGRO_DISPLAY* display);
ALLEGRO_BITMAP* criarBitmapLanca(Lanca* lanca, ALLEGRO_DISPLAY* display);
void desenharLanca(Lanca* lanca);
void atacarLanca(Lanca* lanca);