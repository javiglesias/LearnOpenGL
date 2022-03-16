#pragma once
#ifndef C__APP_H
#define C__APP_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <string>
#include "common.h"
#include <time.h>
#include "ECS/Entities/Entity.h"
#include "ECS/Entities/Corridor.h"
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

#define FRAMECAP120		0.00833333333333333f
#define FRAMECAP60		0.01666666666666667f
#define FRAMECAP30		0.03333333333333333f
#define FRAMECAP24		0.04166666666666667f
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define MOVE_UP glm::vec2(0, .009f)
#define MOVE_DOWN glm::vec2(0, -.009f)
#define MOVE_RIGHT glm::vec2(.009f, 0)
#define MOVE_LEFT glm::vec2(-.009f, 0)
#define GAMEPAD_MIN 0.000015
#define MAP_GENERATION 1

class App
{
private:
	bool should_close = false, m_refresh = false;
	bool is_step_by_step = false;
	bool is_advancing_frame = false;
	bool advance_step = false;
	GLFWwindow* m_window = nullptr;
	register int i = 0;

	Room* m_rooms[10];
	Hero* m_hero_char;		//	Heroe
	Monster* m_enemies[MAX_ENTITIES];	//	Enemigos del heroe
	NPC* m_npcs[MAX_ENTITIES];	//	Colisiones estaticas
	
	SoundSystem* m_sound_system;			//	Sonido
	NetworkSystem* m_network_system;		//	Red
	PhysicsSystem* m_physics_system;		//	Fisicas/colisiones
	void process_input(GLFWwindow* m_window);
	void refresh_level();
	bool enemies_left();
	void generate_map_rooms(int _value);
	std::string m_hero_name;
	bool m_is_restarting = false;
	bool m_joystick_detected = false;
	glm::vec2 m_scrolling{0.f};
	const unsigned char* m_joystick_buttons;
	const float* m_joystick_axes;
	int m_current_level = 0;
	float m_gamepad_L_yAxis = 0.f, m_gamepad_L_xAxis = 0.f;
	float m_gamepad_A = 0.f;
	float m_gamepad_B = 0.f;
	float m_gamepad_X = 0.f;
	float m_gamepad_Y = 0.f;
	clock_t begin_map_generation = clock();
	clock_t end_map_generation = clock();
	
	glm::vec2 m_start_points[4] = {
		glm::vec2(-.8,-.8),
		glm::vec2(-.8,-.6),
		glm::vec2(-.6,-.8),
		glm::vec2(-.6,-.6)
	};
	Entity::Color m_vegetation_colors[4] = {
		Entity::Color(0.f, 170.f / 255.f, 0.f),
		Entity::Color(41.f / 255.f, 134.f / 255.f,  204.f / 255.f),
		Entity::Color(0.f, 170.f / 255.f, 0.f),
		Entity::Color(41.f / 255.f, 134.f / 255.f,  204.f / 255.f)
	};
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
	float m_frame_cap = FRAMECAP120;
	float m_frame_cap_physics = FRAMECAP30;
	float m_frame_cap_ia = FRAMECAP24;
	unsigned int m_frame_number = 0;
	AISystem* m_brain;
};
#endif