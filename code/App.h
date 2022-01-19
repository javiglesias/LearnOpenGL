#pragma once
#ifndef C__APP_H
#define C__APP_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include "ECS/Entity.h"
#include "ECS/Hero.h"
#include "ECS/Monster.h"
#include "ECS/Wall.h"
#include "ECS/Door.h"
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
#define MOVE_UP glm::vec2(0, .01f)
#define MOVE_DOWN glm::vec2(0, -.01f)
#define MOVE_RIGHT glm::vec2(.01f, 0)
#define MOVE_LEFT glm::vec2(-.01f, 0)

class App
{
private:
	bool should_close = false, m_refresh = false;
	GLFWwindow* m_window = nullptr;
	std::vector<Entity*> m_enemies{};		//	Enemigos del heroe
	std::vector<Entity*> m_static_world{};	//	Colisiones estaticas
	std::vector<Entity*> m_future_static_world{};	//	Colisiones estaticas
	std::vector<Entity*> m_dynamic_world{};	//	Objetos que se mueven
	Hero* m_hero_char;						//	Heroe
	Door* m_exit_door;
	SoundSystem* m_sound_system;			//	Sonido
	NetworkSystem* m_network_system;		//	Red
	PhysicsSystem* m_physics_system;		//	Fisicas/colisiones
	void process_input(GLFWwindow* m_window);
	void refresh_level();
	std::string m_hero_name;
	bool m_is_restarting = false;
	glm::vec2 m_scrolling{0.f};
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