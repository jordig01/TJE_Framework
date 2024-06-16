#include "stage.h"
#include "framework/entities/entityPlayer.h"

//----- MENU STAGE -----
MenuStage::MenuStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/Icons/background.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);

	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/start_button2.png");
	play_button = new EntityUI(Vector2(width * 0.5, 350), Vector2(200,75), play_mat, eButtonId::PlayButton);
	play_button->hover_texture = Texture::Get("data/hud/start_button.png");


	Material exit_mat;
	exit_mat.diffuse = Texture::Get("data/hud/exit_button2.png");
	exit_button = new EntityUI(Vector2(width * 0.5, 450), Vector2(200, 75), exit_mat, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

	background->addChild(play_button);
	background->addChild(exit_button);

	background_channel = Audio::Play("data/sounds/intro_audio.wav", 0.2f, BASS_SAMPLE_LOOP);
}

void MenuStage::reload() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background->material);

	play_button = new EntityUI(Vector2(width * 0.5, height * 0.5 + 50), Vector2(200, 75), play_button->material, eButtonId::PlayButton);
	play_button->hover_texture = Texture::Get("data/hud/start_button.png");


	exit_button = new EntityUI(Vector2(width * 0.5, height * 0.5 + 150), Vector2(200, 75), exit_button->material, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

}


void MenuStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);

	if (Input::isKeyPressed(SDL_SCANCODE_1)) Game::instance->goToStage(GAME_OVER);
	if (Input::isKeyPressed(SDL_SCANCODE_2)) Game::instance->goToStage(WIN_STAGE);
}

void MenuStage::onEnterStage()
{
	
}

void MenuStage::render() {
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);
	play_button->render(camera2D);
	exit_button->render(camera2D);
}

void MenuStage::onButtonPressed(eButtonId buttonId)
{
	switch (buttonId) {
	case PlayButton:
		Game::instance->goToStage(TUTORIAL_STAGE);
		break;
	case ExitButton:
		exit(0);
		break;
	}
}

void MenuStage::onExitStage()
{
	Audio::Stop(background_channel);
}



//----- INTRODUCTION STAGE -----
IntroStage::IntroStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/intro_tutorial.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);

	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/continue.png");
	continue_button = new EntityUI(Vector2(width * 0.5, 525), Vector2(200, 75), play_mat, eButtonId::ContinueIntroButton);
	continue_button->hover_texture = Texture::Get("data/hud/continue_2.png");

	background->addChild(continue_button);
}

void IntroStage::reload() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background->material);

	continue_button = new EntityUI(Vector2(width * 0.5, 530), Vector2(200, 75), continue_button->material, eButtonId::ContinueIntroButton);
	continue_button->hover_texture = Texture::Get("data/hud/continue_2.png");

}


void IntroStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	continue_button->update(seconds_elapsed);
}

void IntroStage::onEnterStage()
{
	background_channel = Audio::Play("data/sounds/tutorial_menu.mp3", 0.6f, BASS_MUSIC_LOOP);
}

void IntroStage::render() {
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);
	continue_button->render(camera2D);
}

void IntroStage::onExitStage()
{
	Audio::Stop(background_channel);
}



//----- TUTORIAL STAGE -----
TutorialStage::TutorialStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/tutorial.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);

	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/continue.png");
	continue_button = new EntityUI(Vector2(width - 200, height - 50), Vector2(200, 75), play_mat, eButtonId::ContinueButton);
	continue_button->hover_texture = Texture::Get("data/hud/continue_2.png");

	background->addChild(continue_button);
}

void TutorialStage::reload() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background->material);

	continue_button = new EntityUI(Vector2(width - 200, height - 50), Vector2(200, 75), continue_button->material, eButtonId::ContinueButton);
	continue_button->hover_texture = Texture::Get("data/hud/continue_2.png");

}


void TutorialStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	continue_button->update(seconds_elapsed);
}

void TutorialStage::onEnterStage()
{
	background_channel = Audio::Play("data/sounds/tutorial_menu.mp3", 0.6f, BASS_MUSIC_LOOP);
}

void TutorialStage::render() {
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);
	continue_button->render(camera2D);
}

void TutorialStage::onButtonPressed(eButtonId buttonId)
{
	switch (buttonId) {
	case ContinueButton:
		Game::instance->goToStage(PLAY_STAGE);
		break;
	}
}

void TutorialStage::onExitStage()
{
	Audio::Stop(background_channel);
}


//----- PLAY STAGE -----
PlayStage::PlayStage() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material controls_material;
	controls_material.diffuse = Texture::Get("data/hud/controls_1.png");
	controls = new EntityUI(Vector2(50, 100), Vector2(115, 38), controls_material, eButtonId::ControlsButton);
	controls->hover_texture = Texture::Get("data/hud/controls_2.png");

	// ---- Square and Surprise Objects ----
	Material square_material;
	square_material.diffuse = Texture::Get("data/hud/cuadrado.png");
	square = new EntityUI(Vector2(50, 45), Vector2(75, 75), square_material);

	Material thunder_material;
	thunder_material.diffuse = Texture::Get("data/Icons/thunder.png");
	thunder = new EntityUI(Vector2(50, 45), Vector2(50, 50), thunder_material);

	Material bullet_material;
	bullet_material.diffuse = Texture::Get("data/Icons/fireball.png");
	bullet = new EntityUI(Vector2(50, 45), Vector2(50, 50), bullet_material);

	Material heart_material;
	heart_material.diffuse = Texture::Get("data/Icons/fullheart.png");
	heart = new EntityUI(Vector2(50, 45), Vector2(50, 50), heart_material);

	Material cube_mat;
	cube_mat.diffuse = Texture::Get("data/Icons/fake_cube.png");
	fake_cube = new EntityUI(Vector2(50, 45), Vector2(50, 50), cube_mat);


	// ---- Lifes, Turbo and Fireballs ----
	Material life0_mat;
	life0_mat.diffuse = Texture::Get("data/hud/lives0.png");
	life0 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life0_mat);

	Material life1_mat;
	life1_mat.diffuse = Texture::Get("data/hud/lives1.png");
	life1 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life1_mat);

	Material life2_mat;
	life2_mat.diffuse = Texture::Get("data/hud/lives2.png");
	life2 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life2_mat);

	Material life3_mat;
	life3_mat.diffuse = Texture::Get("data/hud/lives3.png");
	life3 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life3_mat);

	Material boost_mat;
	boost_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/boost.fs");
	boost = new EntityUI(Vector2(760, 470), Vector2(20, 200), boost_mat);

	Material fireball_mat;
	fireball_mat.diffuse = Texture::Get("data/Icons/fireball.png");
	fireball = new EntityUI(Vector2(700, 40), Vector2(75, 75), fireball_mat);
	

	// --- CountDown ---
	number_mat.diffuse = Texture::Get("data/Icons/3.png");
	countdown_num = new EntityUI(Vector2(width * 0.5, height*0.5 - 80), Vector2(150, 150), number_mat);
	

	// --- Finish ---
	Material finish_mat;
	finish_mat.diffuse = Texture::Get("data/Icons/finish_title.png");
	finish = new EntityUI(Vector2(width * 0.5, height * 0.5 - 80), Vector2(200, 40), finish_mat);


	// ---- Score ----
	Material score_mat;
	score_mat.diffuse = Texture::Get("data/hud/score.png");
	score = new EntityUI(Vector2(40, height - 20), Vector2(75, 20), score_mat);

	zero_mat.diffuse = Texture::Get("data/hud/Numbers/zero.png");
	one_mat.diffuse = Texture::Get("data/hud/Numbers/one.png");
	two_mat.diffuse = Texture::Get("data/hud/Numbers/two.png");
	three_mat.diffuse = Texture::Get("data/hud/Numbers/three.png");
	four_mat.diffuse = Texture::Get("data/hud/Numbers/four.png");
	five_mat.diffuse = Texture::Get("data/hud/Numbers/five.png");
	six_mat.diffuse = Texture::Get("data/hud/Numbers/six.png");
	seven_mat.diffuse = Texture::Get("data/hud/Numbers/seven.png");
	eight_mat.diffuse = Texture::Get("data/hud/Numbers/eight.png");
	nine_mat.diffuse = Texture::Get("data/hud/Numbers/nine.png");


}

void PlayStage::reload() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;


	// ---- Square and Surprise Objects ----
	square = new EntityUI(Vector2(50, 45), Vector2(75, 75), square->material);

	controls = new EntityUI(Vector2(75, 150), Vector2(100, 40), controls->material);

	thunder = new EntityUI(Vector2(50, 45), Vector2(50, 50), thunder->material);

	bullet = new EntityUI(Vector2(50, 45), Vector2(50, 50), bullet->material);

	heart = new EntityUI(Vector2(50, 45), Vector2(50, 50), heart->material);

	fake_cube = new EntityUI(Vector2(50, 45), Vector2(50, 50), fake_cube->material);

	countdown_num = new EntityUI(Vector2(width * 0.5, height * 0.5 - 80), Vector2(150, 150), countdown_num->material);

	// ---- Lifes, Turbo, Fireballs and Score ----
	life0 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life0->material);

	life1 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life1->material);

	life2 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life2->material);

	life3 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life3->material);

	boost = new EntityUI(Vector2(width - 40 , height - 130), Vector2(20, 200), boost->material);

	fireball = new EntityUI(Vector2(width - 100, 40), Vector2(75, 75), fireball->material);

	score = new EntityUI(Vector2(40, height - 20), Vector2(75, 20), score->material);


	finish = new EntityUI(Vector2(width * 0.5, height * 0.5 - 80), Vector2(200, 40), finish->material);

	controls = new EntityUI(Vector2(50, 100), Vector2(115, 38), controls->material, eButtonId::ControlsButton);
	controls->hover_texture = Texture::Get("data/hud/controls_2.png");

}


void PlayStage::render()	
{

	Camera* camera2D = World::get_instance()->camera2D;
	EntityPlayer* player = World::get_instance()->root_player;

	World::get_instance()->render();

	if (Input::wasKeyPressed(SDL_SCANCODE_R)) {
		Game::instance->restart();
	}
	switch (player->total_lives) {
		case 3:
			life3->render(camera2D);
			break;
		case 2:
			life2->render(camera2D);
			break;
		case 1:
			life1->render(camera2D);
			break;
		case 0:
			life0->render(camera2D);
			Game::instance->goToStage(GAME_OVER);
			break;
	}

	boost->render(camera2D);
	controls->render(camera2D);

	fireball->render(camera2D);

	// --- Suprise Objects render ---
	square->render(camera2D);

	if (player->object_collected == "turbo") {
		thunder->render(camera2D);
	}
	else if (player->object_collected == "life") {
		heart->render(camera2D);

	}
	else if (player->object_collected == "bullet") {
		bullet->render(camera2D);

	}
	else if (player->object_collected == "obstacle") {
		fake_cube->render(camera2D);
	}

	if (player->position.y > 68.f) {
		just_enter = false;
	}

	if (player->position.y < 68.f && !just_enter) {
		finish->render(camera2D);
		finish_game = true;
	}


	if (timer < 0.0f) {
		finish_game = false;
		just_enter = true;
		timer = 3.0f;
		World::instance->root_player->initial_rotation = true;
		World::instance->root_player->rotation -= World::instance->root_player->rotation + 1.5f;
		World::instance->root_player->cam_rotation = -1.5f;
		World::instance->root_player->total_points += World::instance->root_player->end_score;
		
		World::instance->wheels[0]->model.translate(Vector3(-3.62, 1.5, -4));
		World::instance->wheels[1]->model.translate(Vector3(3.62, 1.5,-4));
		World::instance->wheels[2]->model.translate(Vector3(0,2,3.3));

		Game::instance->goToStage(WIN_STAGE);
	}


	// --- COUNTDOWN ---
	if (World::instance->root_player->initial_rotation) {
		World::instance->root_player->model.rotate(World::instance->root_player->rotation, Vector3(0, 1, 0));
		
		World::instance->wheels[0]->model.rotate(World::instance->wheels[0]->rotation, Vector3(0, 1, 0));
		World::instance->wheels[0]->model.translate(Vector3(-3.62,1.5,-4));

		World::instance->wheels[1]->model.rotate(World::instance->wheels[1]->rotation, Vector3(0, 1, 0));
		World::instance->wheels[1]->model.translate(Vector3(3.62,1.5,-4));

		World::instance->wheels[2]->model.rotate(World::instance->wheels[2]->rotation, Vector3(0, 1, 0));
		World::instance->wheels[2]->model.translate(Vector3(0, 2, 3.3));


		World::instance->root_player->initial_rotation = false;
	}

	if (!World::instance->root_player->countdown_finished) {
		countdown_num->render(camera2D);
	}

	if (World::instance->root_player->start_music) {
		start_channel = Audio::Play("data/sounds/race_start.mp3", 0.3f, BASS_MUSIC_MONO);
	}
	else {
		Audio::Stop(start_channel);
	}

	if (World::instance->root_player->countdown_timer <= 5.0f) {
		countdown_num->material.diffuse = Texture::Get("data/Icons/2.png");
	}
	if (World::instance->root_player->countdown_timer <= 3.0f) {
		countdown_num->material.diffuse = Texture::Get("data/Icons/1.png");
	}
	if (World::instance->root_player->countdown_timer <= 2.0f) {
		countdown_num->material.diffuse = Texture::Get("data/Icons/GO.png");
		World::instance->root_player->start_music = false;
		World::instance->move_player = true;
	}
	if (World::instance->root_player->countdown_timer <= 0.0f) {
		World::instance->root_player->countdown_finished = true;
	}
	


	// --- Score render ---
	score->render(camera2D);
	int current_score = player->total_points;
	int digits = 0;

	while (current_score > 0) {
		current_score = current_score / 10;
		digits++;
	}

	
	int height = Game::instance->window_height;
	current_score = player->total_points;
	EntityUI* num = new EntityUI(Vector2(100, height - 20), Vector2(75, 20), zero_mat);;
	int number;

	if (current_score <= 0) {
		EntityUI* zero = num = new EntityUI(Vector2(100, height - 20), Vector2(20, 20), zero_mat);
		zero->render(camera2D);
		return;
	}

	for (int i = 0; i < digits; i++) {
		number = current_score % 10;

		if (number == 0) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), zero_mat);
		else if (number == 1) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), one_mat);
		else if (number == 2) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), two_mat);
		else if (number == 3) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), three_mat);
		else if (number == 4) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), four_mat);
		else if (number == 5) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), five_mat);
		else if (number == 6) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), six_mat);
		else if (number == 7) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), seven_mat);
		else if (number == 8) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), eight_mat);
		else if (number == 9) num = new EntityUI(Vector2(150 - i * 18, height - 20), Vector2(20, 20), nine_mat);

		num->render(camera2D);
		current_score = current_score / 10;
	}

}

void PlayStage::update(float seconds_elapsed) {

	World::instance->update(seconds_elapsed);
	life3->update(seconds_elapsed);
	boost->update(seconds_elapsed);
	square->update(seconds_elapsed);
	score->update(seconds_elapsed);
	controls->update(seconds_elapsed);

	if (!World::instance->root_player->countdown_finished) {
		World::instance->root_player->countdown_timer -= seconds_elapsed;
	}

	if (finish_game) {
		timer -= seconds_elapsed;
		Audio::Play("data/sounds/finish.mp3", 0.5f, BASS_MUSIC_MONO);
	}


	if (Input::isKeyPressed(SDL_SCANCODE_1)) Game::instance->goToStage(GAME_OVER);
	if (Input::isKeyPressed(SDL_SCANCODE_2)) Game::instance->goToStage(WIN_STAGE);
}

void PlayStage::onEnterStage() {
	sound = Audio::Play("data/sounds/mainScene.mp3", 0.05f, BASS_MUSIC_LOOP | BASS_MUSIC_MONO);
	countdown_num->material.diffuse = Texture::Get("data/Icons/3.png");
}



void PlayStage::onExitStage() {
	Audio::Stop(sound);
	Audio::Stop(start_channel);

	EntityPlayer* player = World::instance->root_player;

	Audio::Stop(player->turbo_channel);
	Audio::Stop(player->handle_channel);
	Audio::Stop(player->move_channel);
	Audio::Stop(player->drift_sound_channel);

}

//----- WIN STAGE -----
WinStage::WinStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/win.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);

	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/restart_button2.png");
	play_button = new EntityUI(Vector2(280, 350), Vector2(200, 75), play_mat, eButtonId::RestartButton);
	play_button->hover_texture = Texture::Get("data/hud/restart_button.png");


	Material exit_mat;
	exit_mat.diffuse = Texture::Get("data/hud/exit_button2.png");
	exit_button = new EntityUI(Vector2(280, 450), Vector2(200, 75), exit_mat, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

	Material score_mat;
	score_mat.diffuse = Texture::Get("data/hud/score.png");
	score = new EntityUI(Vector2(100, height * 0.5 - 50), Vector2(200, 75), score_mat);

	zero_mat.diffuse = Texture::Get("data/hud/Numbers/zero.png");
	one_mat.diffuse = Texture::Get("data/hud/Numbers/one.png");
	two_mat.diffuse = Texture::Get("data/hud/Numbers/two.png");
	three_mat.diffuse = Texture::Get("data/hud/Numbers/three.png");
	four_mat.diffuse = Texture::Get("data/hud/Numbers/four.png");
	five_mat.diffuse = Texture::Get("data/hud/Numbers/five.png");
	six_mat.diffuse = Texture::Get("data/hud/Numbers/six.png");
	seven_mat.diffuse = Texture::Get("data/hud/Numbers/seven.png");
	eight_mat.diffuse = Texture::Get("data/hud/Numbers/eight.png");
	nine_mat.diffuse = Texture::Get("data/hud/Numbers/nine.png");

	background->addChild(play_button);
	background->addChild(exit_button);
}

void WinStage::reload() {

	int width = Game::instance->window_width;
	int height = Game::instance->window_height;
	Camera* camera2D = World::get_instance()->camera2D;
	EntityPlayer* player = World::get_instance()->root_player;

	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background->material);

	play_button = new EntityUI(Vector2(width * 0.25, height * 0.5 + 50), Vector2(200, 75), play_button->material, eButtonId::RestartButton);
	play_button->hover_texture = Texture::Get("data/hud/restart_button.png");

	exit_button = new EntityUI(Vector2(width * 0.25, height * 0.5 + 150), Vector2(200, 75), exit_button->material, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

	score = new EntityUI(Vector2(100, height * 0.5 - 50), Vector2(200, 75), score->material);
	renderNumber(World::instance->camera2D, World::instance->root_player, width, height);

}

void WinStage::render()
{
	Camera* camera2D = World::get_instance()->camera2D;
	EntityPlayer* player = World::get_instance()->root_player;
	

	int height = Game::instance->window_height;
	int width = Game::instance->window_width;

	background->render(camera2D);
	play_button->render(camera2D);
	exit_button->render(camera2D);

	score->render(camera2D);
	renderNumber(camera2D, player, width, height);
}

void WinStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);
}

void WinStage::onEnterStage()
{
	winBackground = Audio::Play("data/sounds/WinStage.wav", 0.3f, BASS_MUSIC_LOOP);
}

void WinStage::onExitStage() {
	Audio::Stop(winBackground);
}

void WinStage::renderNumber(Camera* camera2D, EntityPlayer* player, int width, int height)
{
	int current_score = player->total_points;
	int digits = 0;

	while (current_score > 0) {
		current_score = current_score / 10;
		digits++;
	}


	current_score = player->total_points;
	num = new EntityUI(Vector2(100, height - 20), Vector2(75, 20), zero_mat);;
	int number;


	Vector2 dimension = Vector2(50, 50);

	// If the score is zero or less then zero, render the zero digit and return
	if (current_score <= 0) {
		EntityUI* zero = new EntityUI(Vector2(250, height * 0.5 - 50), dimension, zero_mat);
		zero->render(camera2D);
		return;
	}


	for (int i = 0; i < digits; i++) {
		number = current_score % 10;
		Vector2 position = Vector2(width * 0.5 - 25 - i * 45, height * 0.5 - 50);
		if (number == 0) num = new EntityUI(position, dimension, zero_mat);
		else if (number == 1) num = new EntityUI(position, dimension, one_mat);
		else if (number == 2) num = new EntityUI(position, dimension, two_mat);
		else if (number == 3) num = new EntityUI(position, dimension, three_mat);
		else if (number == 4) num = new EntityUI(position, dimension, four_mat);
		else if (number == 5) num = new EntityUI(position, dimension, five_mat);
		else if (number == 6) num = new EntityUI(position, dimension, six_mat);
		else if (number == 7) num = new EntityUI(position, dimension, seven_mat);
		else if (number == 8) num = new EntityUI(position, dimension, eight_mat);
		else if (number == 9) num = new EntityUI(position, dimension, nine_mat);

		num->render(camera2D);
		current_score = current_score / 10;
	}
}




//----- GAME OVER STAGE -----
GameOverStage::GameOverStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/game_over2.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);
	
	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/restart_button2.png");
	play_button = new EntityUI(Vector2(200, 350), Vector2(200, 75), play_mat, eButtonId::RestartButton);
	play_button->hover_texture = Texture::Get("data/hud/restart_button.png");


	Material exit_mat;
	exit_mat.diffuse = Texture::Get("data/hud/exit_button2.png");
	exit_button = new EntityUI(Vector2(200, 450), Vector2(200, 75), exit_mat, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

	Material score_mat;
	score_mat.diffuse = Texture::Get("data/hud/score.png");
	score = new EntityUI(Vector2(125, height * 0.5 - 50), Vector2(175, 50), score_mat);

	zero_mat.diffuse = Texture::Get("data/hud/Numbers/zero.png");
	one_mat.diffuse = Texture::Get("data/hud/Numbers/one.png");
	two_mat.diffuse = Texture::Get("data/hud/Numbers/two.png");
	three_mat.diffuse = Texture::Get("data/hud/Numbers/three.png");
	four_mat.diffuse = Texture::Get("data/hud/Numbers/four.png");
	five_mat.diffuse = Texture::Get("data/hud/Numbers/five.png");
	six_mat.diffuse = Texture::Get("data/hud/Numbers/six.png");
	seven_mat.diffuse = Texture::Get("data/hud/Numbers/seven.png");
	eight_mat.diffuse = Texture::Get("data/hud/Numbers/eight.png");
	nine_mat.diffuse = Texture::Get("data/hud/Numbers/nine.png");

	background->addChild(play_button);
	background->addChild(exit_button);
}

void GameOverStage::reload() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background->material);

	play_button = new EntityUI(Vector2(width * 0.25, height * 0.5 + 50), Vector2(200, 75), play_button->material, eButtonId::RestartButton);
	play_button->hover_texture = Texture::Get("data/hud/restart_button.png");

	exit_button = new EntityUI(Vector2(width * 0.25, height * 0.5 + 150), Vector2(200, 75), exit_button->material, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

	score = new EntityUI(Vector2(125, height * 0.5 - 50), Vector2(175, 50), score->material);

	renderNumber(World::instance->camera2D, World::instance->root_player, width, height);

}

void GameOverStage::render()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;
	Camera* camera2D = World::get_instance()->camera2D;
	EntityPlayer* player = World::get_instance()->root_player;

	background->render(camera2D);
	play_button->render(camera2D);
	exit_button->render(camera2D);

	score->render(camera2D);
	
	renderNumber(camera2D, player,width, height);
}

void GameOverStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);

}

void GameOverStage::renderNumber(Camera* camera2D, EntityPlayer* player, int width, int height)
{
	int current_score = player->total_points;
	int digits = 0;

	while (current_score > 0) {
		current_score = current_score / 10;
		digits++;
	}

	current_score = player->total_points;
	num = new EntityUI(Vector2(100, height - 20), Vector2(75, 20), zero_mat);;
	int number;


	Vector2 dimension = Vector2(50, 50);

	// If the score is zero or less then zero, render the zero digit and return
	if (current_score <= 0) {
		EntityUI* zero = new EntityUI(Vector2(250, height * 0.5 - 50), dimension, zero_mat);
		zero->render(camera2D);
		return;
	}


	for (int i = 0; i < digits; i++) {
		number = current_score % 10;
		Vector2 position = Vector2(width * 0.5 - 25 - i * 45, height * 0.5 - 50);
		if (number == 0) num = new EntityUI(position, dimension, zero_mat);
		else if (number == 1) num = new EntityUI(position, dimension, one_mat);
		else if (number == 2) num = new EntityUI(position, dimension, two_mat);
		else if (number == 3) num = new EntityUI(position, dimension, three_mat);
		else if (number == 4) num = new EntityUI(position, dimension, four_mat);
		else if (number == 5) num = new EntityUI(position, dimension, five_mat);
		else if (number == 6) num = new EntityUI(position, dimension, six_mat);
		else if (number == 7) num = new EntityUI(position, dimension, seven_mat);
		else if (number == 8) num = new EntityUI(position, dimension, eight_mat);
		else if (number == 9) num = new EntityUI(position, dimension, nine_mat);

		num->render(camera2D);
		current_score = current_score / 10;
	}
}


void GameOverStage::onEnterStage() {
	loseBackground = Audio::Play("data/sounds/GameOver.mp3", 0.2f, BASS_MUSIC_MONO);
}

void GameOverStage::onExitStage() {
	Audio::Stop(loseBackground);
}
