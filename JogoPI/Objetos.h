enum IDS {PLAYER, LANCA, ESCUDO, INIMIGO, ESPADA};
enum POS {X, Y, BOUNDX, BOUNDY};

typedef struct
{
	int ID;
	int pos[4];
	int vida;
	int velocidade;
} Player;

void initPlayer(Player* player);
void desenharPlayer(Player* player);
void andarPlayerCima(Player* player);
void andarPlayerBaixo(Player* player);
void andarPlayerEsqueda(Player* player);
void andarPlayerDireita(Player* player);

typedef struct
{
	int ID;
	int pos[2];
	int dano;
	bool ataque;
} Lanca;

void initLanca(Lanca* lanca);
void desenharLanca(Lanca* lanca, Player* player);
void atacarLanca(Lanca* lanca);