#include "Scene3.h"

void Scene3::init() {
	// Crear generadores de fuerzas
	add_force_generator<Simple_gravity_generator>(-20.0f);
	add_force_generator<Wind_generator>(1, 0, -50, -50, 100, 100, Vector3D(-20, 0, 0));
	add_force_generator<Whirlwind_generator>(1, 0, -50, -50, 100, 100);
	add_force_generator<Explosion_generator>(Vector3D(0, 0, 0), 500, 100000, 0.5);

	// Crear partículas
	generate_particles();
}

void Scene3::cleanup() {

}

void Scene3::update(double dt) {
	Physics_scene::update(dt);
}

void Scene3::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
	switch (key) {
	case 'r':
	{
		kill_all_particles();
		generate_particles();
		break;
	}
	case '1':
	{
		toggle_active_force_generator(0);
		break;
	}
	case '2':
	{
		toggle_active_force_generator(1);
		break;
	}
	case '3':
	{
		toggle_active_force_generator(2);
		break;
	}
	case '4':
	{
		toggle_active_force_generator(3);
		reset_force_generator(3);
		break;
	}
	}
}
void Scene3::generate_particles() {
	for (int i = -20; i < 21; i += 10) {
		for (int j = -20; j < 21; j += 10) {
			for (int k = -20; k < 21; k += 10)
				//add_particle(Vector3(i, j, k), Vector3(0, 0, 0), 0.98f, 0.01, 100, Vector4(1, 0, 0, 1), { true, true, true, true });
				add_particle(Vector3(i, j, k), Vector3(0, 0, 0), 0.98f, (float)((rand() % 5) + 1), 100, Vector4(1, 0, 0, 1), { true, true, true, true });
		}
	}
}