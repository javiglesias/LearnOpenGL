#include "App.h"
#include <cstdio>
#include <wtypes.h>
#include "common.h"

void framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
{
	glViewport(0,0, _width, _height);
	//glOrtho(0, _width, 0, _height, 0, 1);
}
void App::process_input(GLFWwindow* m_window)
{
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sprint = 1.5f;
		}
		m_hero_char->SetNextPosition(sprint * MOVE_UP);
		if(!m_physics_system->GonnaCollideWith(m_hero_char))
		{
			//m_sound_system->PlaySFX("foot_step.wav");
			m_scrolling = (sprint * MOVE_UP);
			m_hero_char->Move(sprint * MOVE_UP);
		}
	} else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sprint = 1.5f;
		}
		m_hero_char->SetNextPosition(sprint * MOVE_LEFT);
		if (!m_physics_system->GonnaCollideWith(m_hero_char))
		{
			m_scrolling = (sprint * MOVE_LEFT);
			m_hero_char->Move(sprint * MOVE_LEFT);
		}
	} else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sprint = 1.5f;
		}
		m_hero_char->SetNextPosition(sprint * MOVE_DOWN);
		if (!m_physics_system->GonnaCollideWith(m_hero_char))
		{
			m_scrolling = (sprint * MOVE_DOWN);
			m_hero_char->Move(sprint * MOVE_DOWN);
		}
	} else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		float sprint = 1.f;
		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			sprint = 1.5f;
		}
		m_hero_char->SetNextPosition(sprint * MOVE_RIGHT);
		if (!m_physics_system->GonnaCollideWith(m_hero_char))
		{
			m_scrolling = (sprint * MOVE_RIGHT);
			m_hero_char->Move(sprint * MOVE_RIGHT);
		}
	}
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwTerminate();
		exit(0);
	}
	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS && !m_is_restarting)
	{
		refresh_level();
		m_is_restarting = true;
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
	fprintf(stdout, "\nRecuerda beber cerveza.");
	m_refresh = true;
	m_enemies.clear();
	//free(m_exit_door);
	m_static_world.clear();
	m_sound_system->StopAll();
	m_sound_system->PlaySFX("open_door.wav");
}
App::~App()
{
	free(m_sound_system);
	free(m_hero_char);
	free(m_exit_door);
	m_enemies.clear();
	m_static_world.clear();
}
int App::run()
{
	srand(NULL);
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
	glViewport(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//	Sound System init
	m_network_system = new NetworkSystem();
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	m_sound_system = new SoundSystem();
	m_brain = new AISystem();
	m_physics_system = new PhysicsSystem();
	//	TODO Aqui cuando se reinicia el nivel, se estan pintando 2 puestas de salida.
	m_exit_door = new Door(new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "DOOR"), 
		glm::vec2(-0.5f,-0.49f));
	m_npc = new NPC(new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "NPC"),
		glm::vec2(0.5f, 0.49f));
refresh:
	m_sound_system->PlayMusic("flies.wav");
	m_hero_char = new Hero(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "HERO"), glm::vec2(0,0));
	m_enemies.clear();
	m_static_world.push_back(m_npc);
	for (unsigned int i = 0; i < 10; i++)
	{
		float x_pos = ((rand() % SCREEN_WIDTH) / 1000.0) - 0.5;
		Sleep(3);
		float y_pos = ((rand() % SCREEN_HEIGHT) / 1000.0) - 0.5;
		m_enemies.push_back( new Monster(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO"),
			glm::vec2(x_pos, y_pos)));
			
	}
	for (unsigned int j = 0; j < 100; j++)
	{
		auto wall = new Wall(glm::vec2(rand() % 200 / 200.f, 
			rand() % 200 / 200.f), 
			0.01, 0.01,
			new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "WALL"));
		m_static_world.push_back(wall);
	}
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
			glClearColor(0.2f, 0.2f, 0.3f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			process_input(m_window);
			m_accumulated_time = 0.f;
			for (auto ent : m_enemies)
			{
				ent->Draw(m_scrolling);
			}
			for (auto ent : m_static_world)
			{
				ent->Draw(m_scrolling);
			}
			m_hero_char->Draw(m_scrolling);
			m_exit_door->Draw(m_scrolling);

			glfwSwapBuffers(m_window);
			glfwPollEvents();
			m_physics_system->FreeOutOfBounds(&m_static_world);
			m_frame_number++;
			m_scrolling = glm::vec2(0.f);
		}
		if (m_accumulated_time_physics >= m_frame_cap_physics) // Physics frame
		{
			m_accumulated_time_physics = 0.f;
			//	COMMITEAR LAS FUTURAS POSICIONES
			/*for (auto ent : m_static_world)
			{
				if (ent->m_show)
				{
					if (m_physics_system->GonnaCollide(m_hero_char, ent))
					{
						ent->m_show = false;
					}
					ent->UpdatePhysics();
				}
			}*/
			//	Comprobamos las colisiones con el mundo estatico antes de avanzar.
			if (m_physics_system->GonnaCollide(m_hero_char, m_exit_door))
			{
				refresh_level();
				goto refresh;
			}
		}
		if (m_accumulated_time_ia >= m_frame_cap_ia) // IA and Sound frame
		{
			m_brain->Update(m_hero_char, m_enemies);
			for (auto ent : m_static_world)
			{
				if (ent->m_show || !ent->m_to_delete)
					ent->UpdateIA();
			}
			m_accumulated_time_ia = 0.f;
		}
		m_current_frame = glfwGetTime();
	}
	glfwTerminate();
	return 0;
}