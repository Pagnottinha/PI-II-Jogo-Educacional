enum IDS {PLAYER, LANCA, ESCUDO, INIMIGO, ESPADA};
enum POS {X, Y, BOUNDX, BOUNDY};

typedef struct
{
	int ID;
	int pos[4];
	int vida;
	int velocidade;
} Player;