#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <Windows.h>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int speed;
	int score;
	int life = 10;
	float x, y;		//플레이어 좌표
};

struct Enemy {
	RectangleShape sprite;
	int speed;
	int life;
};

struct Bullet {
	RectangleShape sprite;
	//int speed;
	int is_fire;

};
struct Item {
	RectangleShape sprite;
	int delay;
	int is_presented;
};

struct Textures {
	Texture bg;			// 배경 이미지
	Texture gameover;	//게임오버 이미지
	Texture player;		//플레이어 이미지
	Texture enemy;
	Texture bullet;
	Texture item_delay;
	Texture item_speed;
};
struct SButters {
	SoundBuffer BGM;
	SoundBuffer bubble;
	SoundBuffer gun;
};

//obj1과 obj2의 충돌하면 1반환, 충돌 안하면 0 반환 
int is_collide(RectangleShape obj1, RectangleShape obj2) {
	return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}

//전역변수
const int ENEMY_NUM = 10;
const int W_WIDTH = 1200, W_HEIGHT = 600;
const int GO_WIDTH = 700, GO_HEIGHT = 300;
const int BULLET_NUM = 50;

int main(void)
{
	struct Textures t;
	t.bg.loadFromFile("./resources/images/background.png");
	t.gameover.loadFromFile("./resources/images/gameover.png");
	t.player.loadFromFile("./resources/images/player.png");
	t.enemy.loadFromFile("./resources/images/enemy.png");
	t.bullet.loadFromFile("./resources/images/bullet.png");
	t.item_delay.loadFromFile("./resources/images/delay.png");
	t.item_speed.loadFromFile("./resources/images/speed.png");
	struct SButters sb;
	sb.BGM.loadFromFile("./resources/sounds/bgm.ogg");
	sb.bubble.loadFromFile("./resources/sounds/bubble.wav");
	sb.gun.loadFromFile("./resources/sounds/bubble2.wav");
	// 윈도창 생성
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AfterSchool");
	window.setFramerateLimit(60);
	srand(time(0));

	long start_time = clock();	// 게임 시작시간
	long spent_time;			// 게임 진행시간
	int is_gameover = 0;
	long fired_time = 0; //최근에 발사한 시간 
	//BGM
	
	Sound BGM_sound;
	BGM_sound.setBuffer(sb.BGM);
	BGM_sound.setLoop(1);	//BMG 무한 반복 !
	BGM_sound.play();

	// text
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(30);		// 글자크기 조절
	text.setFillColor(Color(255, 255, 255));
	text.setPosition(0, 0);
	char info[40];

	// 배경
	Sprite bg_sprite;
	bg_sprite.setTexture(t.bg);
	bg_sprite.setPosition(0, 0);

	//gameover
	Sprite gameover_sprite;
	gameover_sprite.setTexture(t.gameover);
	gameover_sprite.setPosition((W_WIDTH - GO_WIDTH)/2, (W_HEIGHT - GO_HEIGHT)/2);

	// 플레이어
	struct Player player;
	player.sprite.setTexture(&t.player);
	player.sprite.setSize(Vector2f(210, 120));
	player.sprite.setPosition(100, 100);
	player.x = player.sprite.getPosition().x;
	player.y = player.sprite.getPosition().y;
	
	player.speed = 10;
	player.score = 0;

	// 총알
	int bullet_deplay=500;
	int bullet_idx = 0;
	int bullet_speed = 20;
	Sound Bullet_sound;
	Bullet_sound.setBuffer(sb.gun);
	struct Bullet bullet[BULLET_NUM];

	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i].sprite.setTexture(&t.bullet);
		bullet[i].sprite.setSize(Vector2f(35, 35));
		bullet[i].sprite.setPosition(player.x + 100, player.y + 50);	 //임시 테스트
		bullet[i].is_fire = 0;
	}


	// 적(enemy)
	struct Enemy enemy[ENEMY_NUM];
	Sound enemy_explosion_sound;
	enemy_explosion_sound.setBuffer(sb.bubble);
	int enemy_score = 100;
	int enemy_respawn_time = 8;
	// enemy 초기화
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].sprite.setTexture(&t.enemy);
		enemy[i].sprite.setSize(Vector2f(70, 70));
		enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH*0.9, rand() % 580);
		enemy[i].life = 1;
		enemy[i].speed = -(rand() % 10 + 1);
	}

	//item
	struct Item item[2];
	item[0].sprite.setTexture(&t.item_speed);
	item[0].delay = 25000;// 25초
	item[0].sprite.setSize(Vector2f(70, 70));
	item[0].is_presented = 1;
	// 윈도가 열려있을 때까지 반복
	while (window.isOpen())
	{
		spent_time = clock() - start_time;
		player.x = player.sprite.getPosition().x;
		player.y = player.sprite.getPosition().y;

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// 종료(x) 버튼을 누르면 Event::Closed(0)
			case Event::Closed:
				window.close();		// 윈도를 닫는다
				break;
				// 키보드를 눌렀을 때(누른 순간만을 감지)
			case Event::KeyPressed:
			{
				//// 스페이스 키 누르면 모든 enemy 다시 출현
				//if (event.key.code == Keyboard::Space)
				//{
				//	for (int i = 0; i < ENEMY_NUM; i++)
				//	{
				//		enemy[i].sprite.setSize(Vector2f(70, 70));
				//		enemy[i].sprite.setFillColor(Color::Yellow);
				//		enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 580);
				//		enemy[i].life = 1;
				//		enemy[i].speed = -(rand() % 10 + 1);
				//	}
				//}
				break;
			}

			}
		}

		

		/* player update*/
		// 방향키 start
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.sprite.move(-player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.sprite.move(player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.sprite.move(0, -player.speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
		
			player.sprite.move(0, player.speed);
		}	// 방향키 end
		//Player 이동범위 제한
		// TODO: 오른쪽 아래쪽 제한을 의도대로 고치기
		if (player.sprite.getPosition().x <0) {
			player.sprite.setPosition(0, player.sprite.getPosition().y);
		}
		
		else if (player.sprite.getPosition().x > W_WIDTH-210) {
			player.sprite.setPosition(W_WIDTH-210, player.sprite.getPosition().y);
		}
		if (player.sprite.getPosition().y < 0) {
			player.sprite.setPosition( player.sprite.getPosition().x,0);
		}
		else if (player.sprite.getPosition().y > W_HEIGHT-100) {
			player.sprite.setPosition(player.sprite.getPosition().x, W_HEIGHT-100);
		}
		 
		/* bullet undate */
		for (int i = 0; i < BULLET_NUM; i++) {

		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (spent_time-fired_time> bullet_deplay) {

				if (!bullet[bullet_idx].is_fire) {

					bullet[bullet_idx].sprite.setPosition(player.x + 200, player.y + 50);
					bullet[bullet_idx].is_fire = 1;
					bullet_idx++;
					bullet_idx = bullet_idx % BULLET_NUM;
					Bullet_sound.play();
					fired_time = spent_time;

				}
			}
			

		}
		for (int i = 0; i < BULLET_NUM; i++) {
			
			if (bullet[i].is_fire) {
				bullet[i].sprite.move(bullet_speed, 0);
				if (bullet[i].sprite.getPosition().x > W_WIDTH) {
					bullet[i].is_fire = 0;
				}
			}
		}
		//item update
		if (item[0].is_presented) {
			//TODO: 충돌시 아이템 효과를 주고 사라진다. 
		}

		/* enemy update*/
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			//10초마다 enemy 젠
			if (spent_time %(1000*enemy_respawn_time) < 1000 / 60 + 1) {
				//게임이 진행중일 때만 적을 리스폰 시키겟다
				if (!is_gameover) {
					enemy[i].sprite.setSize(Vector2f(70, 70));

					enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 580);
					enemy[i].life = 1;
					enemy[i].speed = -(rand() % 10 + 1 + (spent_time / 1000 / enemy_respawn_time));
				}
				
			}
			//Enemy update
			if (enemy[i].life > 0)
			{
				//TODO : 총알이 관통하는 버그 수정할 것 
				//player , enemy 충돌
				if (is_collide(player.sprite, enemy[i].sprite))
					
				{
				
					enemy[i].life -= 1;
					player.score += enemy_score;

			
					if (enemy[i].life == 0)
					{
						enemy_explosion_sound.play();
					}
				}
				//적이 왼쪽 끝에 진입하려는 순간
				else if (enemy[i].sprite.getPosition().x<0) {
					player.life -= 1;
					enemy[i].life = 0;

				}
				//총알과 enemy 충돌
				for (int j = 0; j < BULLET_NUM; j++) {
					if (is_collide(bullet[j].sprite, enemy[i].sprite)) {
						if (bullet[j].is_fire) {
							enemy[i].life -= 1;
							player.score += enemy_score;

							// TODO : 코드 refactoring 필요
							if (enemy[i].life == 0)
							{
								enemy_explosion_sound.play();
							}
							bullet[j].is_fire = 0;
						}
						
					}
				}
				enemy[i].sprite.move(enemy[i].speed, 0);
			}
		}

		
		if (player.life <= 0) {
			is_gameover = 1;
		}
		
		sprintf(info, "life : %dscore:%d time:%d"
			,player.life, player.score, spent_time / 1000);
		text.setString(info);

		window.clear(Color::Black);
		window.draw(bg_sprite);
		for (int i = 0; i < BULLET_NUM; i++) {
			if (bullet[i].is_fire) {
				window.draw(bullet[i].sprite);
			}
		}
		
		// draw는 나중에 호출할수록 우선순위가 높아짐
		for (int i = 0; i < ENEMY_NUM; i++)
			if (enemy[i].life > 0)
				window.draw(enemy[i].sprite);
		if (item[0].is_presented) {
			window.draw(item[0].sprite);
		}
		window.draw(player.sprite);
		window.draw(text);
		if (is_gameover) {
			window.draw(gameover_sprite);
		}

		window.display();
	}

	return 0;
}