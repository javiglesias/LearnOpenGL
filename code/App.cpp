#include "App.h"
#include <cstdio>
#include <wtypes.h>
#include "common.h"
#include "ECS/Entities/Wall.h"

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

		if(m_joystick_buttons[0] == GLFW_PRESS)
			fprintf(stdout, "Button 0", m_joystick_buttons[0]);
		else if (m_joystick_buttons[1] == GLFW_PRESS)
			fprintf(stdout, "Button 1");
		else if(m_joystick_buttons[2] == GLFW_PRESS)
			fprintf(stdout, "Button 2", m_joystick_buttons[0]);
		else if (m_joystick_buttons[3] == GLFW_PRESS)
			fprintf(stdout, "Button 3", m_joystick_buttons[1]);

	}
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS ||
		round(m_joystick_axes[1]) < 0.f)
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
		round(m_joystick_axes[0]) < 0.f)
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
		round(m_joystick_axes[1]) > 0.f)
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
		round(m_joystick_axes[0]) > 0.f)
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
	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
	{
		m_hero_char->Interact(true);
	}
	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_RELEASE)
	{
		m_hero_char->Interact(false);
	}
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwTerminate();
		exit(0);
	}
	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS && !m_is_restarting)
	{
		m_is_restarting = true;
		refresh_level();
	}
	else if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_RELEASE && m_is_restarting)
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
}
void App::refresh_level()
{
	m_current_level++;
	fprintf(stdout, "\nNivel de cerveza: %d\n", m_current_level);
	this->m_refresh = true;
	m_dynamic_world.clear();
	m_npcs.clear();
	m_enemies.clear();
	m_static_world.clear();
	m_sound_system->StopAll();
	m_sound_system->PlaySFX("open_door.wav");
}

bool App::enemies_left()
{
	for (auto enemy : m_enemies)
	{
		if(enemy->m_show == true)
			return true;
		else continue;
	}
	return false;
}

App::~App()
{
	free(m_sound_system);
	free(m_hero_char);
	m_dynamic_world.clear();
	m_static_world.clear();
	m_npcs.clear();
}
int App::run()
{
	srand(NULL);
	fprintf(stdout,"Seed: %d", rand());
	glfwInit();
	m_current_frame = glfwGetTime();
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
	//	Sound System init
	m_network_system = new NetworkSystem();
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	m_sound_system = new SoundSystem();
	m_brain = new AISystem();
	m_physics_system = new PhysicsSystem();
	
refresh:
	m_sound_system->PlayMusic("Reflections.wav", m_current_level/1.f);
	m_dynamic_world.clear();
	//	 Generate 4 monsters at a time
	for (unsigned int i = 0; i < 10; i++)
	{
		float x_pos = ((rand() % SCREEN_WIDTH) / 1010.0);
		Sleep(3);
		float y_pos = ((rand() % SCREEN_HEIGHT) / 1010.0);
		m_enemies.push_back( new Monster(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO"),
			glm::vec2(x_pos, y_pos)));

		x_pos = ((rand() % SCREEN_WIDTH) / -1010.0);
		Sleep(3);
		y_pos = ((rand() % SCREEN_HEIGHT) / 1010.0);
		m_enemies.push_back(new Monster(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO"),
			glm::vec2(x_pos, y_pos)));

		x_pos = ((rand() % SCREEN_WIDTH) / 1010.0);
		Sleep(3);
		y_pos = ((rand() % SCREEN_HEIGHT) / -1010.0);
		m_enemies.push_back(new Monster(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO"),
			glm::vec2(x_pos, y_pos)));

		x_pos = ((rand() % SCREEN_WIDTH) / -1010.0);
		Sleep(3);
		y_pos = ((rand() % SCREEN_HEIGHT) / -1010.0);
		m_enemies.push_back(new Monster(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO"),
			glm::vec2(x_pos, y_pos)));
			
	}
	// Generacion procedimental de la mazmorra 
	// Super simple, TODO iteracion mas adelante.
#if 1
	for (unsigned int j = 0; j < 100; j++)
	{
		Wall* wall = nullptr;
		if(m_static_world.size() > 0)
		{
			float is_x = rand() % 1000 / 1000.f;
			float is_y = rand() % 1000 / 1000.f;
			glm::vec2 init_position{};
			auto last_wall = m_static_world.at(m_static_world.size()-1);
			if(is_x > is_y)
			{
				float x_pos = last_wall->GetPosition().x +
					last_wall->GetSize().w;
				if(x_pos > 1.0f || x_pos < -1.0f)
				{
					x_pos = 0.f;
				}
				init_position = glm::vec2(x_pos, last_wall->GetPosition().y);
			} else
			{
				float y_pos	= last_wall->GetPosition().y + last_wall->GetSize().h;
				if(y_pos > 1.f || y_pos < -1.f)
				{
					y_pos = 0.f;
				}
				init_position = glm::vec2(last_wall->GetPosition().x, y_pos);
			}
			wall =new Wall(init_position,
				0.1f, 0.1f,
				new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "WALL"));
		}
		else
		{
			wall = new Wall(glm::vec2(-1.f,-1.f),
				0.1f, 0.1f,
				new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "WALL"));
		}
		m_static_world.push_back(wall);
	}
#else
	Wall* wall = nullptr;
	wall = new Wall(glm::vec2(-1.f, -1.f),
		0.1f, 0.1f,
		new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "WALL"));
	m_static_world.push_back(wall);
#endif

	//	Colocamos al jugador en la primera habitacion
	m_hero_char = new Hero(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "HERO"), glm::vec2(0, 0.f));
	m_npcs.push_back(new NPC(new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "NPC"), 
		m_static_world.at(rand() % m_static_world.size())->GetPosition()));

	while (!glfwWindowShouldClose(m_window)) // Game loop
	{
		if (m_refresh)
		{
			m_refresh = false;
			goto refresh;
		}
		m_new_frame = glfwGetTime();
		m_delta_time = m_new_frame - m_current_frame;
		m_accumulated_time += m_delta_time;
		m_accumulated_time_physics += m_delta_time;
		m_accumulated_time_ia += m_delta_time;
		if (m_accumulated_time >= m_frame_cap) // Render frame
		{
			glClearColor(0, 0, 0, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			process_input(m_window);
			m_accumulated_time = 0.f;
			for (auto ent : m_static_world)
			{
				ent->Draw();
			}
			m_hero_char->Draw();
			for (auto monster : m_enemies)
			{
				monster->Draw();
			}
			for(auto npc : m_npcs)
			{
				npc->Draw();
			}

			glfwSwapBuffers(m_window);
			glfwPollEvents();
			m_frame_number++;
		}
		if (m_accumulated_time_physics >= m_frame_cap_physics) // Physics frame
		{
			m_accumulated_time_physics = 0.f;
			m_physics_system->UpdateStaticWorld(m_static_world);
			for (auto npc : m_npcs)
			{
				void (*callback)() = &refresh;
				if(npc->UpdatePhysics(m_hero_char, m_hero_char->GetInteracting(), callback) && !enemies_left())
				{
					refresh_level();
				}
				npc->Move(m_scrolling);
			}
			for (auto monster : m_enemies)
			{
				if(monster->UpdatePhysics(m_hero_char))
				{
					continue;
				}
				else
				{
					monster->Move(m_scrolling);
				}
			}
			for (auto ent : m_static_world)
			{
				ent->Move(m_scrolling);
			}
			m_scrolling = glm::vec2(0.f);
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
		m_current_frame = glfwGetTime();
	}
	glfwTerminate();
	return 0;
}
