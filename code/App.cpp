#include "App.h"
#include <cstdio>
#include <wtypes.h>
#include "common.h"
#include "ECS/Entities/Room.h"
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
}
void App::refresh_level()
{
	m_current_level++;
	this->m_refresh = true;
	m_rooms.clear();
	m_props_world.clear();
	m_corridors.clear();
#if !MAP_GENERATION
	fprintf(stdout, "\nNivel de cerveza: %d\n", m_current_level);
	m_dynamic_world.clear();
	m_npcs.clear();
	m_enemies.clear();
	m_sound_system->StopAll();
	m_sound_system->PlaySFX("open_door.wav");
#endif

}

bool App::enemies_left()
{
	for (i = 0; i < m_enemies.size(); ++i)
	{
		if(m_enemies[i]->m_show == true)
			return true;
		else continue;
	}
	return false;
}

void App::generate_map_rooms(int _value)
{
	/* Generacion procedimental de la mazmorra 
	 Cada 2 habitaciones hay que conectarlas por un pasillo*/
	Room* last_room = m_rooms.size() > 0 ? m_rooms[m_rooms.size() - 1] : nullptr;
	int rooms_to_generate = _value + 1; // el numero de salas es incremental en cada piso
	float room_width = 0.2f, room_height = 0.2f;
	float x_pos = -1.f;
	float y_pos = -1.f;
	if(last_room)
	{
		room_width = last_room->GetSize().w;
		room_height = last_room->GetSize().h;
		x_pos = last_room->GetPosition().x;
		y_pos = last_room->GetPosition().y;
	}
	Room* room = nullptr;
	glm::vec2 init_position
	{
		x_pos+room_width,
		y_pos+2*room_height
	};
	rooms_to_generate <<= rooms_to_generate; // por cada habitacion, generamos 2, una a cada lado.
	for (int j = 0; j < rooms_to_generate; j++)
	{
		int room_rng = rand() % 100;
		if(room_rng > 50 || room_rng > 75)
		{
			init_position = glm::vec2(1.2 * j * room_width,init_position.y);
			room = new Room(init_position, room_width, room_height,
				new Shader("code\\shaders\\instance.vert",
					"code\\shaders\\instance.frag", "Room"));
			m_rooms.push_back(room);
		} else if(room_rng < 50 || room_rng < 75)
		{
			init_position = glm::vec2(-1.2 * j * room_width,init_position.y);
			room = new Room(init_position, room_width, room_height,
				new Shader("code\\shaders\\instance.vert",
					"code\\shaders\\instance.frag", "Room"));
			m_rooms.push_back(room);
		}
	}
}

App::~App()
{
	free(m_sound_system);
	free(m_hero_char);
	m_dynamic_world.clear();
	m_rooms.clear();
	m_npcs.clear();
}
int App::run()
{
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
	//	Sound System init
	m_network_system = new NetworkSystem();
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	m_sound_system = new SoundSystem();
	m_brain = new AISystem();
	m_physics_system = new PhysicsSystem();
	
refresh:
#if !MAP_GENERATION
	m_sound_system->PlayMusic("Reflections.wav", m_current_level/1.f);
	m_dynamic_world.clear();
	//	 Generate 4 monsters at a time
	float x_pos = ((rand() % SCREEN_WIDTH) / 1010.0);
	float y_pos = ((rand() % SCREEN_HEIGHT) / 1010.0);
	for (i = 0; i < 10; i++)
	{
		m_enemies.push_back( new Monster(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "MOSTRO"),
			glm::vec2(x_pos, y_pos)));
	}
#endif

#if 1
	begin_map_generation = clock();
	generate_map_rooms(0);
	generate_map_rooms(1);
	generate_map_rooms(2);
	end_map_generation = clock();
	fprintf(stdout, "Map generation elapsed time: %ld\n", end_map_generation - begin_map_generation);
#else
	Room* first_room = nullptr;
	first_room = new Room(glm::vec2(-1.f, -1.f),
		0.1f, 0.1f,
		new Shader("code\\shaders\\basic_water.vert", "code\\shaders\\basic_water.frag", "Room"));
	m_rooms.push_back(first_room);
#endif
	//	Colocamos al jugador en la primera habitacion
	m_hero_char = new Hero(new Shader("code\\shaders\\basic.vert", "code\\shaders\\basic.frag", "HERO"), 
	m_rooms.at(0)->GetPosition(),
		.02f, .04f);
	/*m_npcs.push_back(new NPC(new Shader("code\\shaders\\instance.vert", "code\\shaders\\instance.frag", "NPC"), 
		m_rooms.at(rand() % m_rooms.size())->GetPosition()));*/
#if 0
	return 0;
#endif
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
			glClearColor(85.f / 255.f, 170.f / 255.f, 85.f / 255.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			process_input(m_window);
			m_accumulated_time = 0.f;
			//	Lo primero en dibujar, el fondo
			for (i=0; i < m_props_world.size(); ++i)
			{
				
				m_props_world[i]->Draw();
			}
			for (i = 0; i < m_rooms.size(); ++i)
			{
				m_rooms[i]->Draw();
			}
			for (i=0; i < m_corridors.size(); ++i)
			{
				m_corridors[i]->Draw();
			}
#if !MAP_GENERATION
			for (i = 0; i < m_enemies.size(); ++i)
			{
				m_enemies[i]->Draw();
			}
			for(i = 0; i < m_npcs.size(); ++i)
			{
				m_npcs[i]->Draw();
			}
#endif
			m_hero_char->Draw();

			glfwSwapBuffers(m_window);
			glfwPollEvents();
			m_frame_number++;
		}
		if (m_accumulated_time_physics >= m_frame_cap_physics) // Physics frame
		{
			m_accumulated_time_physics = 0.f;
			register int i = 0;
#if !MAP_GENERATION
			m_physics_system->UpdateStaticWorld(m_rooms);
			for (i = 0; i < m_npcs.size(); ++i)
			{
				void (*callback)() = &refresh;
				if(m_npcs[i]->UpdatePhysics(m_hero_char, m_hero_char->GetInteracting(), callback) && !enemies_left())
				{
					refresh_level();
				}
				m_npcs[i]->Move(m_scrolling);
			}
			for (i = 0; i < m_enemies.size(); ++i)
			{
				if(m_enemies[i]->UpdatePhysics(m_hero_char))
				{
					continue;
				}
				else
				{
					m_enemies[i]->Move(m_scrolling);
				}
			}
#endif
			for (i = 0; i < m_props_world.size(); ++i)
			{
				m_props_world[i]->Move(m_scrolling);
			}
			for (i = 0; i < m_rooms.size(); ++i)
			{
				m_rooms[i]->Move(m_scrolling);
			}
			for (i = 0; i < m_corridors.size(); ++i)
			{
				m_corridors[i]->Move(m_scrolling);
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
		m_current_frame = static_cast<float>(glfwGetTime());
	}
	glfwTerminate();
	return 0;
}
