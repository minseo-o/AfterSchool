#include <stdio.h>
struct Saram {
	int hp;
	int speed;
};
int main(void) {
	struct Saram player;
	player.hp = 5;
	player.speed = 7;

	struct Saram enemy;
	enemy.hp = 5;
	enemy.hp = 7;

	printf("�÷��̾� ü�� %d �÷��̾� �ӵ� %d \n", player.hp, player.speed);
}