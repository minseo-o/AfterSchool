#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
using namespace sf;

int main(void) {
	//������ â ����
	RenderWindow window(VideoMode(640, 480), "AfterSchool");
	window.setFramerateLimit(60);
	srand(time(0));

	//�簢�� â �׸���
	RectangleShape player;
	player.setSize(Vector2f(40, 40));
	player.setPosition(100, 100);
	window.draw(player);

	RectangleShape enemy[5];
	int enemy_life[5];
	//enemy �ʱ�ȭ
	for (int i = 0; i< 5; i++) {
		enemy[i].setSize(Vector2f(70, 70));
		enemy[i].setFillColor(Color::Yellow);
		enemy_life[i] = 1;
		enemy[i].setPosition(rand()%300+300, rand()%380);
		window.draw(enemy[i]);
	}
	
	
	


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

			case Event::KeyPressed:
			{
				//�����̽� Ű ������ ��� enemy �ٽ� ����
				//TODO �� �� ���� ��, �� ���� �����ϱ�
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					for (int i = 0; i < 5; i++) {
						enemy[i].setSize(Vector2f(70, 70));
						enemy[i].setFillColor(Color::Yellow);
						enemy_life[i] = 1;
						enemy[i].setPosition(rand() % 300 + 300, rand() % 380);
						window.draw(enemy[i]);
					}
				}
				break;
				
			}
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
		for (int i = 0; i < 5; i++) {
			if (enemy_life[i] > 0) {
				//������ �浹ó��
				if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
					printf("enemy[%d]�� �浹\n",i);
					enemy_life[i] -= 1;
				}
			}
		}
		


		//60�п� 1�ʸ��� �׷ȴ� �����ٸ� �ݺ��ϰ� �ȴ�. 
		window.clear(Color::Black);

		for (int i = 0; i < 5; i++) {
			if (enemy_life[i]> 0)
				window.draw(enemy[i]);

		}
		
		//draw�� ���߿� ȣ���� ���� �켱������ ��������. 

		window.draw(player);
		window.display();
	}
	return 0;
}