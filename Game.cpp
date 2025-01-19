#include "Game.h"
#include "Map.h"
#include "Texture.h"
#include "Collision.h"
#include "Player.h"
#include "SoundManager.h"
#include "GUI/Button.h"
#include "GUI/TextField.h"
#include "GUI/TextLabel.h"
#include <fstream>
#include <random>
#include <memory>

#define size 5

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


SoundManager soundManager;

std::unique_ptr<Map> map;
std::unique_ptr<Player> player;
std::unique_ptr<ColliderObject> wall1, wall2;
std::unique_ptr<GameObject[]> spike; // Using a dynamic array
std::unique_ptr<Collision> collision;
std::unique_ptr<Button> b1, b2;
std::unique_ptr<TextLabel> t1, t3, t4, t5, t6, t7, health, speed, speedtext;
std::unique_ptr<TextField> t2;


void Game::collisionHandler() {
	if (check) {
		for (int i = 0; i < size; i++) {
			if (Collision::AABB(player->desRect, spike[i].desRect)) {
				if (player->health > 1) {
					player->changed("assets/boxed.png");
					player->health--;
					soundManager.playSoundEffect("sounds/collide_spike.wav", 0);
					check = false;
					timer = true;
				}
				else if (player->health == 1) {
					player->health--;
					player->changed("assets/fully_boxed.png");
					isMoving = false;
					player->isMoving = false;
					player->isJumping = false;
					player->velocity.y = 0;
					player->velocity.x = 0;
					//std::cout << "Player collided with spike " << i + 1 << std::endl;
					end = true;
					//std::cout << "Start Flag: " << start << " End flag: " << end << std::endl;
					soundManager.playSoundEffect("sounds/collide_spike.wav", 0);
					check = false;
				}
			}
		}
	}

	player->update();

	if (Collision::AABB(player->desRect, wall1->desRect)) {
		player->isJumping = false;
		player->velocity.y = 0;
		if (Time == 84) {
			soundManager.playSoundEffect("sounds/flip.wav", 0);
			player->isFlip = false;
			player->counter = false;
			player->velocity.y = 2;
		}
		
		//std::cout << "Player collided with wall1" << std::endl;
	}

	if (Collision::AABB(player->desRect, wall2->desRect)) {
		player->isJumping = false;
		player->velocity.y = 0;
		//std::cout << "Player collided with wall2" << std::endl;
	}
}

Game::Game() {
	
	timer = false;
	check = false;
	isMoving = false;
	start = true;
	speedFlag = false;
}

void Game::resetGame() {
	speedFlag = false;
	timer = false;
	check = false;
	start = true;
	end = false;
	isMoving = false;
	player->isMoving = false;
	player->isJumping = false;
	player->score = 0;
}

Game::~Game()
{}

void Game::generateRandom() {

	//random int generator (1 to 5)
	//Create a random number engine
	std::random_device rd; //to seed the engine (if available)
	std::mt19937 gen(rd()); //random number engine

	//uniform distribution between 1 and 5 (inclusive)
	std::uniform_int_distribution<int> distribution(1, 5);

	for (int i = 0; i < 5; i++) {
		randomNumbers[i] = distribution(gen);
	}

	std::sort(randomNumbers, randomNumbers + 5);

	//check duplicates
	hasTwoDuplicates = false;
	hasThreeDuplicates = false;
	threeDups = -1;
	for (int i = 0; i < 2; i++) {
		twoDups[i] = -1;
	}

	for (int i = 0; i < 4; i++) {
		if (randomNumbers[i] == randomNumbers[i + 1] && randomNumbers[i + 1] == randomNumbers[i + 2]) {
			hasThreeDuplicates = true;
			threeDups = randomNumbers[i];
		}
		else if (randomNumbers[i] == randomNumbers[i + 1] && threeDups != randomNumbers[i]) {
			if (hasTwoDuplicates) {
				if (twoDups[0] != randomNumbers[i]) {
					twoDups[1] = randomNumbers[i];
				}
			}
			hasTwoDuplicates = true;
			if (twoDups[0] == -1) {
				twoDups[0] = randomNumbers[i];
			}
		}
		else if (hasThreeDuplicates && hasTwoDuplicates) {
			break;
		}
	}
	//std::cout << "Threedups:" << hasThreeDuplicates << " Twodups:" << hasTwoDuplicates << std::endl;
}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flag = 0;
	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;


	TTF_Init();

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		//cout << "SDL subsystem Initialized!!" << endl;

		SDL_Surface* iconSurface = IMG_Load("./assets/box2.png");
		window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
		if (window) {
			SDL_SetWindowIcon(window, iconSurface);
			//cout << "Window Created!!" << endl;
		}
		SDL_FreeSurface(iconSurface);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			//cout << "Renderer Created!!" << endl;
		}

		soundManager.initialize();

		isRunning = true;

		generateRandom();

		map = std::make_unique<Map>();
		player = std::make_unique<Player>(2, 400, 576);
		wall1 = std::make_unique<ColliderObject>(0, 192, 320, 32, 7168, 1);
		wall2 = std::make_unique<ColliderObject>(0, 192, 640, 32, 7168, 1);
		collision = std::make_unique<Collision>();

		spike = std::make_unique<GameObject[]>(size);

		b1 = std::make_unique<Button>("Play");
		b2 = std::make_unique<Button>("Play again");
		t1 = std::make_unique<TextLabel>("DashLeapster");
		t3 = std::make_unique<TextLabel>("Player:");
		t4 = std::make_unique<TextLabel>("HighScore");
		t5 = std::make_unique<TextLabel>();
		t6 = std::make_unique<TextLabel>();
		t7 = std::make_unique<TextLabel>("GAME OVER");
		health = std::make_unique<TextLabel>();
		speed = std::make_unique<TextLabel>(">>>>");
		speedtext = std::make_unique<TextLabel>("SPEED:");
		t2 = std::make_unique<TextField>(Game::renderer, "Name");

		map->LoadMap("assets/level.map");
		int index2[2] = { 0,0 }, index3 = 0;
		for (int i = 1; i < size+1; i++) {
			//std::cout << randomNumbers[i - 1] << std::endl;
			if (hasThreeDuplicates) {
				if (threeDups == randomNumbers[i - 1]) {
					spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092 + (index3 * 64), 320 + 192 + 32 + 32);
					index3++;
				}
			}
			if (hasTwoDuplicates) {

				if (twoDups[0] == randomNumbers[i - 1]) {
					spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092 + (index2[0] * 64), 320 + 192 + 32 + 32);
					index2[0]++;
				}
				if (twoDups[1] == randomNumbers[i - 1]) {
					spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092 + (index2[1] * 64), 320 + 192 + 32 + 32);
					index2[1]++;
				}
			}
			if (threeDups != randomNumbers[i - 1] && twoDups[0] != randomNumbers[i - 1] && twoDups[1] != randomNumbers[i - 1]) {
				spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092, 320 + 192 + 32 + 32);
			}
		}

		//std::cout << "ThreDups: " << threeDups << std::endl;
		//std::cout << "TwoDups: "<< twoDups[0] << " , " << twoDups[1] << std::endl;

		//GUI
		std::string name="NoPlayer";

		std::ifstream inFile("data.txt");
		if (inFile.is_open()) {
			inFile >> previousScore >> name;
			inFile.close();
		}

		t1->setPosition(220, 100);
		t1->noRect();
		t1->changeFont("./fonts/maintext.ttf", 50);
		t1->changeColor(0, 0, 180, 255);

		t7->setPosition(269, 100);
		t7->noRect();
		t7->changeFont("./fonts/maintext.ttf", 50);
		t7->changeColor(0, 0, 180, 255);

		t4->setPosition(12, 15);
		t4->noRect();
		t4->changeFont("./fonts/highscore_name.ttf", NULL);
		t4->changeColor(255, 255, 255, 255);

		t5->setText(name + ":" + std::to_string(previousScore));
		t5->setPosition(15, 45);
		t5->noRect();
		t5->changeColor(255, 255, 255, 255);

		t6->setText("Score:" + std::to_string(player->score));
		t6->setPosition(685, 23);
		t6->noRect();
		t6->changeFont("./fonts/score.ttf", NULL);
		t6->changeColor(255, 255, 255, 255);

		health->setText("Health " + std::to_string(player->health));
		health->setPosition(600, 24);
		health->noRect();
		health->changeFont("./fonts/play.ttf", NULL);
		health->changeColor(255, 0, 0, 255);

		speed->setPosition(530, 1);
		speed->noRect();
		speed->changeFont("./fonts/score.ttf", 60);
		speed->changeColor(0, 255, 0, 255);

		speedtext->setPosition(425, 19);
		speedtext->noRect();
		speedtext->changeFont("./fonts/highscore_name.ttf", NULL);
		speedtext->changeColor(255, 255, 255, 255);

		b1->setPosition(376, 420);
		b1->changeFont("./fonts/play.ttf", 30);

		b2->setPosition(344, 420);
		b2->changeFont("./fonts/play.ttf", 30);

		t3->setPosition(247, 254);
		t3->noRect();
		t3->changeFont("./fonts/highscore_name.ttf", NULL);
		t3->changeColor(0, 0, 255, 255);

		t2->setPosition(352, 255, 200, 35);
	}
	else {
		isRunning = false;
	}
}

void Game::handleEvent() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		default:
			break;
		}
	default:
		break;
	}
	if (isMoving) {
		if (Collision::AABB(player->desRect, wall1->desRect) || Collision::AABB(player->desRect, wall2->desRect))
			player->KeyboardController();
	}

	//GUI handler for start
	if(start && !end)
		b1->buttonController(event);
	else if(end && !start)
		b2->buttonController(event);
	t2->handleEvent(event);
	t2->blinkCursor();

	//GUI Event handling for start
	if (b1->buttonClicked) {

		soundManager.playSoundEffect("sounds/button_click2.wav", 0);

		player->name = t2->getText();
		//std::cout << "player Name: " << player->name << std::endl;

		check = true;
		start = false;
		isMoving = true;
		player->isMoving = true;
		end = false;

		//std::cout << "Start Flag:" << start << "End flag:" << end << std::endl;

		b1->buttonClicked = false;
	}
	//GUI Event handling for end
	if (b2->buttonClicked) {
		player->changed("assets/box2.png");

		player->position.x = 400;
		player->position.y = 576;
		player->health = 2;

		player->update();

		soundManager.playSoundEffect("sounds/button_click2.wav", 0);

		resetGame();

		std::string name;
		std::ifstream inFile("data.txt");
		if (inFile.is_open()) {
			inFile >> previousScore >> name;
			inFile.close();
		}
		t5->setText(name + ":" + std::to_string(previousScore));

		//std::cout << "Start Flag: " << start << " End flag: " << end << std::endl;

		b2->buttonClicked = false;
	}
}

void Game::update() {


	cameraX = player->desRect.x - 800 / 2;
	cameraY = player->desRect.y - 640 / 2;

	int offsetX = -(cameraX + 192);
	int offsetY = -(cameraY + 0);


	if (isMoving) {
		if (player->counter) {
			Time += 1;
		}
		else if (timer) {
			checkTime += 1;
			if(checkTime % 2 == 0) {
				player->changed("assets/boxed.png");
			}
			else {
				player->changed("assets/boxcrashed.png");
			}
			if (checkTime == 64) {
				checkTime = 0;
				check = true;
				timer = false;
			}
		}
		else {
			Time = 0;
		}
		if (player->isMoving) {
			player->velocity.x = 1;
		}
		else {
			player->velocity.x = 0;
			player->velocity.y = 0;
		}

		//for game to loop
		if (player->position.x >= 6336) {
			int remainingDistance = player->position.x - 6336;
			player->position.x = 400 + remainingDistance;
			player->update();
			player->render(offsetX, offsetY);

			generateRandom();
			int index2[2] = { 0,0 }, index3 = 0;
			for (int i = 1; i < size + 1; i++) {
				//std::cout << randomNumbers[i - 1] << std::endl;
				if (hasThreeDuplicates) {
					if (threeDups == randomNumbers[i - 1]) {
						spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092 + (index3 * 64), 320 + 192 + 32 + 32);
						index3++;
					}
				}
				if (hasTwoDuplicates) {

					if (twoDups[0] == randomNumbers[i - 1]) {
						spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092 + (index2[0] * 64), 320 + 192 + 32 + 32);
						index2[0]++;
					}
					if (twoDups[1] == randomNumbers[i - 1]) {
						spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092 + (index2[1] * 64), 320 + 192 + 32 + 32);
						index2[1]++;
					}
				}
				if (threeDups != randomNumbers[i - 1] && twoDups[0] != randomNumbers[i - 1] && twoDups[1] != randomNumbers[i - 1]) {
					spike[i - 1].LoadObject(2, randomNumbers[i - 1] * 1092, 320 + 192 + 32 + 32);
				}
			}

			//std::cout << "ThreDups: " << threeDups << std::endl;
			//std::cout << "TwoDups: " << twoDups[0] << " , " << twoDups[1] << std::endl;
		}

		if (player->isJumping && player->position.y <= 512 - player->jumpHeight) {
			player->velocity.y = 1;
		}

		collisionHandler();

		wall1->update();
		wall2->update();
		for (int i = 1; i < size+1; i++) {
			spike[i - 1].update();
		}
		//score counter
		static int scoreIncreaseTimer = 0;
		scoreIncreaseTimer++;
		if (scoreIncreaseTimer >= 1) {
			player->score += 1;
			scoreIncreaseTimer = 0;
		}
		if (player->score != 0 && player->score % 800 == 0) {
			speedFlag = true;
			player->speed++;
		}
	}


	if (end) {
		if (player->score > previousScore) {
			std::ofstream outFile("data.txt");
			if (outFile.is_open()) {
				outFile << player->score<< ' ' << player->name;
				outFile.close();
			}
		}
		player->speed = 4;
	}
	
	t6->setText("Score:" + std::to_string(player->score));
	health->setText("Health:" + std::to_string(player->health));
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	int offsetX = -(cameraX + 192);
	int offsetY = -(cameraY + 0);

	map->Draw(offsetX, offsetY);

	wall1->render(offsetX, offsetY);
	wall2->render(offsetX, offsetY);
	for (int i = 1; i < size+1; i++) {
		spike[i-1].render(offsetX, offsetY);
	}
	player->render(offsetX, offsetY);
	if (!start && !end) {
		t6->renderLabel();
		health->renderLabel();
		speedtext->renderLabel();
		if (speedFlag) {
			speed->renderLabel();
			if (player->score % 200 == 0) {
				speedFlag = false;
			}
		}
	}

	//GUI Render for start
	if (start && !b1->buttonClicked) {
		t1->renderLabel();

		t4->renderLabel();
		t5->renderLabel();

		t3->renderLabel();

		t2->render(Game::renderer);

		b1->renderButton();
	}
	if (end && !b2->buttonClicked) {
		t6->renderLabel();
		t7->renderLabel();
		b2->renderButton();
		health->renderLabel();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();

	//cout << "Game Cleaned!!" << endl;
}

bool Game::running() {
	return isRunning;
}