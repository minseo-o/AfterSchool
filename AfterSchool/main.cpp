#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
using namespace sf;

int main(void) {
	//윈도우 창 생성
	RenderWindow window(VideoMode(640, 480), "AfterSchool");
	window.setFramerateLimit(60);
	srand(time(0));
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.tff");
	Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(Color(255, 255, 255));
	text.setPosition(0, 0);
	text.setString("scroe");

	//사각형 창 그리기
	RectangleShape player;
	player.setSize(Vector2f(40, 40));
	player.setPosition(100, 100);
	window.draw(player);
	int player_score = 0;
	RectangleShape enemy[5];
	int enemy_life[5];
	int enemy_score = 100;// 적을 잡을 때 얻는 점수 
	//enemy 초기화
	for (int i = 0; i< 5; i++) {
		enemy[i].setSize(Vector2f(70, 70));
		enemy[i].setFillColor(Color::Yellow);
		enemy_life[i] = 1;
		enemy[i].setPosition(rand()%300+300, rand()%380);
		window.draw(enemy[i]);
	}
	
	
	


	//사각형 색상 변경
	player.setFillColor(Color::Red);

	//플레이어 스피드 5으로 초기화
	int player_speed = 5;

	//윈도우가 열려있을 때 까지 반복
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			//종료(x)버튼을 누르면  
			switch (event.type) {
			case Event::Closed:
				window.close();

			case Event::KeyPressed:
			{
				//스페이스 키 누르면 모든 enemy 다시 출현
				//TODO 한 번 누를 때, 한 번만 적용하기
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
		//플레이어 움직임 구현
		//else를 쓰지 않으면 중간으로 나갈 수 있음 제약이 줄어든다.(동시동작 가능)
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
		

		//충돌 처리를 enemy가 살아있을 때만 그리겠다. 
		for (int i = 0; i < 5; i++) {
			if (enemy_life[i] > 0) {
				//적과의 충돌처리
				if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
					printf("enemy[%d]과 충돌\n",i);
					enemy_life[i] -= 1;
					player_score += enemy_score;
				}
			}
		}
		
		printf("score : %d\n", player_score);

		//60분에 1초마다 그렸다 지웠다를 반복하게 된다. 
		window.clear(Color::Black);

		for (int i = 0; i < 5; i++) {
			if (enemy_life[i]> 0)
				window.draw(enemy[i]);

		}
		
		//draw는 나중에 호출할 수록 우선순위가 높아진다. 

		window.draw(player);
		window.draw(text);
		window.display();
	}
	return 0;
}