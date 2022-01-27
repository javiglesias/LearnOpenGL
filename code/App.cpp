#include "App.h"
#include <cstdio>
#include <wtypes.h>
#include "common.h"

void framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
{
	glViewport(-1,-1, _width, _height);
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
			//m_hero_char->Move(sprint * MOVE_UP);
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
			//m_hero_char->Move(sprint * MOVE_LEFT);
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
			//m_hero_char->Move(sprint * MOVE_DOWN);
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
			//m_hero_char->Move(sprint * MOVE_RIGHT);
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
	m_dynamic_world.clear();
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
	m_dynamic_world.clear();
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
	glViewport(-1, -1, SCREEN_WIDTH, SCREEN_HEIGHT);
	//	Sound System init
	m_network_system = new NetworkSystem();
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	m_sound_system = new SoundSystem();
	m_brain = new AISystem();
	m_physics_system = new PhysicsSystem();
	//	TODO Aqui cuando se reinicia el nivel, se estan pintando 2 puestas de salida.
	/*m_exit_door = new Door(new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "DOOR"), 
		glm::vec2(-1.f,-1.f));*/
refresh:
	//m_sound_system->PlayMusic("flies.wav");
	m_dynamic_world.clear();
	/*for (unsigned int i = 0; i < 10; i++)
	{
		float x_pos = ((rand() % SCREEN_WIDTH) / 1000.0) - 0.5;
		Sleep(3);
		float y_pos = ((rand() % SCREEN_HEIGHT) / 1000.0) - 0.5;
		m_dynamic_world.push_back( new Monster(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO"),
			glm::vec2(x_pos, y_pos)));
			
	}*/
	// Generacion procedimental de la mazmorra maximo 10 habitaciones.
	// Super simple, TODO iteracion mas adelante.
	for (unsigned int j = 0; j < 10; j++)
	{
		Wall* wall = nullptr;
		if(m_static_world.size() > 0)
		{
			auto last_room = m_static_world.at(m_static_world.size() -1);
			float is_x = rand() % 1000 / 1000.f;
			float is_y = rand() % 1000 / 1000.f;
			glm::vec2 init_position{};
			if(is_x > is_y)
			{
				init_position = glm::vec2(last_room->GetPosition().x + last_room->GetSize().w, last_room->GetPosition().y);
			} else
			{
				init_position = glm::vec2(last_room->GetPosition().x, last_room->GetPosition().y + last_room->GetSize().h);
			}
			wall = new Wall(init_position,
				0.2, 0.2,
				new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "WALL"));
		}
		else{
			wall = new Wall(glm::vec2(0.f, 0.f),
				0.2, 0.2,
				new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "WALL"));
		}
		m_static_world.push_back(wall);
	}

	//	Colocamos al jugador en la primera habitacion
	glm::vec2 init_position{};
	init_position = glm::vec2(
		m_static_world.at(0)->GetPosition().x,
		m_static_world.at(0)->GetPosition().y
	);
	m_hero_char = new Hero(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "HERO"), init_position);
	init_position = glm::vec2(
		m_static_world.at(m_static_world.size()-1)->GetPosition().x,
		m_static_world.at(m_static_world.size() - 1)->GetPosition().y
	);
	m_npc = new NPC(new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "NPC"),
		init_position);
	m_dynamic_world.push_back(m_npc);
	while (!glfwWindowShouldClose(m_window)) // Game loop
	{
		int axes_count = -1, button_count = -1;
		if(glfwJoystickPresent(GLFW_JOYSTICK_1))
		{
			m_joystick_detected = true;
			m_joystick_axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
			m_joystick_buttons = glfwGetJoystickHats(GLFW_JOYSTICK_1,
				&button_count);
			fprintf(stdout, "X: %f\n", m_joystick_axes[0]);
			fprintf(stdout, "Y: %f\n", m_joystick_axes[1]);

		}

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
			for (auto ent : m_dynamic_world)
			{
				ent->Draw();
			}
			//m_exit_door->Draw();

			glfwSwapBuffers(m_window);
			glfwPollEvents();
			m_frame_number++;
		}
		if (m_accumulated_time_physics >= m_frame_cap_physics) // Physics frame
		{
			m_accumulated_time_physics = 0.f;
			m_npc->UpdatePhysics(m_hero_char, m_hero_char->GetInteracting());
			m_physics_system->UpdateStaticWorld(m_static_world);
			for(auto ent : m_static_world)
			{
				ent->Move(m_scrolling);
			}
			for(auto ent : m_dynamic_world)
			{
				ent->Move(m_scrolling);
			}
			//m_exit_door->Move(m_scrolling);
			m_scrolling = glm::vec2(0.f);
		}
		if (m_accumulated_time_ia >= m_frame_cap_ia) // IA and Sound frame
		{
			m_brain->Update(m_hero_char, m_dynamic_world);
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