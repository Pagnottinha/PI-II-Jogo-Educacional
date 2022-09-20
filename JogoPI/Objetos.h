enum IDS {PLAYER, LANCA, ESCUDO, INIMIGO, ESPADA};
enum POS {X, Y};

typedef struct
{
	int ID;
	int pos[2];
	int vida;
	int velocidade;
} Player;

void initPlayer(Player* player);
ALLEGRO_BITMAP* criarBitmapPlayer(Player* player, ALLEGRO_DISPLAY* display);
void desenharPlayer(Player* player, ALLEGRO_BITMAP* imagePlayer);
void andarPlayerCima(Player* player);
void andarPlayerBaixo(Player* player);
void andarPlayerEsqueda(Player* player);
void andarPlayerDireita(Player* player);

typedef struct
{
	int ID;
	int pos[2];
	int dano;
} Lanca;

void initLanca(Lanca* lanca);
void desenharLanca(Lanca* lanca, Player* player);
void atacarLanca(Lanca* lanca);