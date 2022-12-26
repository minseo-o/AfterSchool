#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {
	//������ â ����
	RenderWindow window(VideoMode(640, 480), "AfterSchool");
	window.setFramerateLimit(60);

	//�簢�� â �׸���
	RectangleShape player;
	player.setSize(Vector2f(40, 40));
	player.setPosition(100, 100);
	window.draw(player);

	RectangleShape enemy;
	enemy.setSize(Vector2f(70, 70));
	enemy.setPosition(500, 300);
	window.draw(enemy);
	enemy.setFillColor(Color::Yellow);
	int enemy_life = 1;


	//�簢�� ���� ����
	player.setFillColor(Color::Red);

	//�÷��̾� ���ǵ� 3���� �ʱ�ȭ
	int player_speed = 5;

	//�����찡 �������� �� ���� �ݺ�
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			//����(x)��ư�� ������  
			switch (event.type) {
			case Event::Closed:
				window.close();
			}
		}
		//�÷��̾� ������ ����
		//else�� ���� ������ �߰����� ���� �� ���� ������ �پ���.(���õ��� ����)
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.move(-player_speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player.move(0, -player_speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player.move(0, player_speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.move(player_speed, 0);
		}

		//�浹 ó���� enemy�� ������� ���� �׸��ڴ�. 
		if (enemy_life > 0) {
			//������ �浹ó��
			if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
				printf("enemy�� �浹\n");
				enemy_life -= 1;
			}
		}


		//60�п� 1�ʸ��� �׷ȴ� �����ٸ� �ݺ��ϰ� �ȴ�. 
		window.clear(Color::Black);

		if (enemy_life > 0)
			window.draw(enemy);

		//draw�� ���߿� ȣ���� ���� �켱������ ��������. 

		window.draw(player);
		window.display();
	}
	return 0;
}