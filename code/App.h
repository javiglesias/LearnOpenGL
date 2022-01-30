#pragma once
#ifndef C__APP_H
#define C__APP_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include "ECS/Entities/Entity.h"
#include "ECS/Entities/Hero.h"
#include "ECS/Entities/Monster.h"
#include "ECS/Entities/NPC.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/NetworkSystem.h"
#include "ECS/Systems/AISystem.h"
#include "ECS/Systems/PhysicsSystem.h"

//	TODO	IA
//	TODO	Colisiones
//	TODO	Generacion de laberinto
//	TODO	Online

#define FRAMECAP60 0.01666666666666667
#define FRAMECAP30 0.03333333333333333
#define FRAMECAP24 0.04166666666666667
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define MOVE_UP glm::vec2(0, .009f)
#define MOVE_DOWN glm::vec2(0, -.009f)
#define MOVE_RIGHT glm::vec2(.009f, 0)
#define MOVE_LEFT glm::vec2(-.009f, 0)
#define GAMEPAD_MIN 0.000015

class App
{
private:
	bool should_close = false, m_refresh = false;
	GLFWwindow* m_window = nullptr;

	Hero* m_hero_char;						//	Heroe
	std::vector<Monster*> m_enemies{};		//	Enemigos del heroe
	std::vector<NPC*> m_npcs{};	//	Colisiones estaticas
	std::vector<Entity*> m_static_world{};	//	Colisiones estaticas
	std::vector<Entity*> m_dynamic_world{};	//	Objetos que se mueven

	SoundSystem* m_sound_system;			//	Sonido
	NetworkSystem* m_network_system;		//	Red
	PhysicsSystem* m_physics_system;		//	Fisicas/colisiones
	void process_input(GLFWwindow* m_window);
	void refresh_level();
	bool enemies_left();
	std::string m_hero_name;
	bool m_is_restarting = false;
	bool m_joystick_detected = false;
	glm::vec2 m_scrolling{0.f};
	const unsigned char* m_joystick_buttons;
	const float* m_joystick_axes;
	int m_current_level = 0;
public:
	App(std::string _hero_name) { m_hero_name = _hero_name;}
	~App();
	int run();

	float m_new_frame = 0.f;
	float m_delta_time = 0.f;
	float m_current_frame = 0.f;
	float m_accumulated_time = 0.f;
	float m_accumulated_time_physics = 0.f;
	float m_accumulated_time_ia = 0.f;
	float m_frame_cap = FRAMECAP60;
	float m_frame_cap_physics = FRAMECAP30;
	float m_frame_cap_ia = FRAMECAP24;
	unsigned int m_frame_number = 0;
	AISystem* m_brain;
};
#endif