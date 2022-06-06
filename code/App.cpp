#include "App.h"
#include <cstdio>
#include <wtypes.h>
#include "common.h"
void refresh()
{
	//fprintf(stdout, "\nCallback de hablar con el NPC.\n");
	return;
}
void framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
{
	glViewport(-1,-1, _width, _height);
	//glOrtho(0, _width, 0, _height, 0, 1);
}
void App::process_input(GLFWwindow* m_window)
{
	if (glfwJoystickPresent(GLFW_JOYSTICK_1))
	{
		int axes_count = -1, button_count = -1;
		m_joystick_detected = true;
		m_joystick_axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
		m_joystick_buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1,
			&button_count);
		m_gamepad_L_yAxis = round(m_joystick_axes[1]);
		m_gamepad_L_xAxis = round(m_joystick_axes[0]);
		m_gamepad_A = m_joystick_buttons[0];
		m_gamepad_B = m_joystick_buttons[1];
		m_gamepad_X = m_joystick_buttons[2];
		m_gamepad_Y = m_joystick_buttons[3];

	}
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS || m_gamepad_L_yAxis < 0.f)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS )
		{
			sprint = 1.5f;
		}
		if(m_hero_char->GetPosition().y < 0.98)
		{
			m_hero_char->SetNextPosition(sprint * MOVE_UP);
			if(!m_physics_system->GonnaCollideWith(m_hero_char))
			{
				//m_sound_system->PlaySFX("foot_step.wav");
				m_scrolling = (sprint * MOVE_UP);
				m_hero_char->Move(sprint * MOVE_UP);
			}
		}
	} else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS ||
		m_gamepad_L_xAxis < 0.f)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sprint = 1.5f;
		}
		if (m_hero_char->GetPosition().x > -0.98)
		{
			m_hero_char->SetNextPosition(sprint * MOVE_LEFT);
			if (!m_physics_system->GonnaCollideWith(m_hero_char))
			{
				m_scrolling = (sprint * MOVE_LEFT);
				m_hero_char->Move(sprint * MOVE_LEFT);
			}
		}
	} else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS ||
		m_gamepad_L_yAxis > 0.f)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sprint = 1.5f;
		}
		if (m_hero_char->GetPosition().y > -0.98)
		{
			m_hero_char->SetNextPosition(sprint * MOVE_DOWN);
			if (!m_physics_system->GonnaCollideWith(m_hero_char))
			{
				m_scrolling = (sprint * MOVE_DOWN);
				m_hero_char->Move(sprint * MOVE_DOWN);
			}
		}
	} else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS ||
		m_gamepad_L_xAxis > 0.f)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sprint = 1.5f;
		}
		if (m_hero_char->GetPosition().x < 0.98)
		{
			m_hero_char->SetNextPosition(sprint * MOVE_RIGHT);
			if (!m_physics_system->GonnaCollideWith(m_hero_char))
			{
				m_scrolling = (sprint * MOVE_RIGHT);
				m_hero_char->Move(sprint * MOVE_RIGHT);
			}
		}
	}
	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS ||
		m_gamepad_A == GLFW_PRESS)
	{
		m_hero_char->Interact(true);
		m_persist_manager->SaveObject(*m_hero_char);
	}
	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_RELEASE)
	{
		m_hero_char->Interact(false);
	}
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		m_gamepad_X == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	}
	if ((glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS ||
		m_gamepad_Y == GLFW_PRESS) && !m_is_restarting)
	{
		m_is_restarting = true;
		refresh_level();
	}
	else if ((glfwGetKey(m_window, GLFW_KEY_R) == GLFW_RELEASE ||
		m_gamepad_Y == GLFW_RELEASE) && m_is_restarting)
	{
		m_is_restarting = false;
	}
	if (glfwGetKey(m_window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
	{
		m_sound_system->VolumeIncrement(0.1f);
	} else if (glfwGetKey(m_window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
	{
		m_sound_system->VolumeIncrement(-0.1f);
	}
	if(glfwGetKey(m_window, GLFW_KEY_0) == GLFW_PRESS)
	{
		is_step_by_step = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS)
	{
		is_advancing_frame = true;
	}
	if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_RELEASE && is_advancing_frame)
	{	
		advance_step = true;
		is_advancing_frame = false;
	}
}
void App::refresh_level()
{
	m_current_level++;
	delete m_brain;
	delete m_network_system;
	delete m_physics_system;
	m_refresh = true;
}

bool App::enemies_left()
{
	for (i = 0; i < 10; ++i)
	{
		if(m_enemies[i]->m_show == true)
			return true;
		else continue;
	}
	return false;
}

//void App::generate_map_rooms(int _value)
//{
//	/*Generacion procedimental de la mazmorra 
//	Cada 2 habitaciones hay que conectarlas por un pasillo*/
//	//	TODO utilizar flyweigth patron para pintar los objetos.
//	//	El numero de salas es incremental en cada piso
//	//rooms_to_generate <<= rooms_to_generate;
//	//	Por cada habitacion, generamos 2, una a cada lado.
//	for (int j = 0; j < _value; j++)
//	{
//		m_rooms[j] = new Room(glm::vec2(j-1, j/2 - 0.5f));
//	}
//}

App::~App()
{
	free(m_sound_system);
	free(m_hero_char);
}
int App::run()
{
	m_script_manager->executeScript("resources/Scripts/init.lua");
	srand(NULL);
	fprintf(stdout,"Seed: %d", rand());
	glfwInit();
	m_current_frame = static_cast<float>(glfwGetTime());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CyberRogue", nullptr, nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		fprintf(stderr, "Error on CREATE WINDOW");
		return -1;
	}
	//	GLAD
	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		fprintf(stderr, "Error loading GLAD.");
		return -1;
	}
	glViewport(-1, -1, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	
	//m_sound_system->PlayMusic("Reflections.wav", m_current_level/1.f);
	//	 Generate 4 monsters at a time
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		float x_pos = -((rand() % SCREEN_WIDTH) / 500.0);
		float y_pos = ((rand() % SCREEN_HEIGHT) / 500.0);
		int j = i;
		m_enemies[i] = new Monster(glm::vec2(x_pos, y_pos));
		++i;
		m_enemies[i] = new Monster(glm::vec2(-x_pos, y_pos));
		++i;
		m_enemies[i] = new Monster(glm::vec2(x_pos, -y_pos));
		++i;
		m_enemies[i] = new Monster(glm::vec2(-x_pos, -y_pos));

		x_pos = ((rand() % SCREEN_WIDTH) / 500.0);
		y_pos = -((rand() % SCREEN_HEIGHT) / 500.0);
		i = j;
		m_npcs[i] = new NPC(glm::vec2(x_pos, y_pos));
		++i;
		m_npcs[i] = new NPC(glm::vec2(-x_pos, y_pos));
		++i;
		m_npcs[i] = new NPC(glm::vec2(x_pos, -y_pos));
		++i;
		m_npcs[i] = new NPC(glm::vec2(-x_pos, -y_pos));
	}

	//begin_map_generation = clock();
	////generate_map_rooms(2);
	//end_map_generation = clock();
	//fprintf(stdout, "Map generation elapsed time: %ld\n", end_map_generation - begin_map_generation);
	//	Colocamos al jugador en la primera habitacion
	m_hero_char = new Hero(glm::vec2(0,0));
	m_sound_system = new SoundSystem();
refresh:
	m_network_system = new NetworkSystem();
	m_brain = new AISystem();
	m_physics_system = new PhysicsSystem();
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		float x_pos = -((rand() % SCREEN_WIDTH) / 500.0);
		float y_pos = ((rand() % SCREEN_HEIGHT) / 500.0);
		int j = i;
		m_enemies[i]->SetPosition(glm::vec2(x_pos, y_pos));
		++i;
		m_enemies[i]->SetPosition(glm::vec2(-x_pos, y_pos));
		++i;
		m_enemies[i]->SetPosition(glm::vec2(x_pos, -y_pos));
		++i;
		m_enemies[i]->SetPosition(glm::vec2(-x_pos, -y_pos));
		x_pos = ((rand() % SCREEN_WIDTH) / 500.0);
		y_pos = -((rand() % SCREEN_HEIGHT) / 500.0);
		i = j;
		m_npcs[i]->SetPosition(glm::vec2(x_pos, y_pos));
		++i;
		m_npcs[i]->SetPosition(glm::vec2(-x_pos, y_pos));
		++i;
		m_npcs[i]->SetPosition(glm::vec2(x_pos, -y_pos));
		++i;
		m_npcs[i]->SetPosition(glm::vec2(-x_pos, -y_pos));
	}
	while (!glfwWindowShouldClose(m_window)) // Game loop
	{
		if (m_refresh)
		{
			m_refresh = false;
			goto refresh;
		}
		m_new_frame = static_cast<float>(glfwGetTime());
		m_delta_time = m_new_frame - m_current_frame;
		m_accumulated_time += m_delta_time;
		m_accumulated_time_physics += m_delta_time;
		m_accumulated_time_ia += m_delta_time;
		if (m_accumulated_time >= m_frame_cap) // Render frame
		{
			process_input(m_window);
			if (!is_step_by_step || advance_step)
			{
				glClearColor(85.f / 255.f, 170.f / 255.f, 85.f / 255.f, 1.f);
				glClear(GL_COLOR_BUFFER_BIT);
				m_accumulated_time = 0.f;
				//	DRAW ENTITIES
				for (i = 0; i < MAX_ENTITIES; ++i)
				{
					if(m_enemies[i]->GetPosition().x < 1.f && 
						m_enemies[i]->GetPosition().y < 1.f &&
						m_enemies[i]->GetPosition().x > -1.f &&
						m_enemies[i]->GetPosition().y > -1.f)
					{
						m_enemies[i]->Draw();
					}

					if (m_npcs[i]->GetPosition().x < 1.f &&
						m_npcs[i]->GetPosition().y < 1.f &&
						m_npcs[i]->GetPosition().x > -1.f &&
						m_npcs[i]->GetPosition().y > -1.f)
					{
						m_npcs[i]->Draw();
					}
				}

				m_hero_char->Draw();

				glfwSwapBuffers(m_window);
				m_frame_number++;
				//fprintf(stdout, "\rFrame: %d", m_frame_number);
				if(advance_step && is_step_by_step)
					advance_step = false;
			}
			glfwPollEvents();
		}
		if (m_accumulated_time_physics >= m_frame_cap_physics) // Physics frame
		{
			m_accumulated_time_physics = 0.f;
			if (!is_step_by_step || advance_step)
			{
				//m_physics_system->UpdateStaticWorld(m_rooms);
				for (i = 0; i < MAX_ENTITIES; ++i)
				{
					/*void (*callback)() = &refresh;
					if(m_npcs[i]->UpdatePhysics(m_hero_char, m_hero_char->GetInteracting(), callback) && !enemies_left())
					{
						refresh_level();
					}*/
					m_npcs[i]->Move(m_scrolling);
					m_enemies[i]->Move(m_scrolling);
				}
				/*for (i = 0; i < 1; ++i)
				{
					m_rooms[i]->Move(m_scrolling);
				}*/
				m_scrolling = glm::vec2(0.f);
				if (advance_step && is_step_by_step)
					advance_step = false;
			}
		}
		if (m_accumulated_time_ia >= m_frame_cap_ia) // IA and Sound frame
		{
			//m_brain->Update(m_hero_char, m_dynamic_world);
			/*for (auto ent : m_enemies)
			{
				if (ent->m_show)
					ent->UpdateIA(m_hero_char);
			}*/
			m_accumulated_time_ia = 0.f;
		}
		m_current_frame = static_cast<float>(glfwGetTime());
	}
	glfwTerminate();
	return 0;
}
