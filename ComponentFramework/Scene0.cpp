#include <glew.h>
#include <iostream>
#include <SDL_events.h>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"


Scene0::Scene0() :sphere( nullptr ), shader( nullptr ), mesh( nullptr ), earthTexture(nullptr),
		moonTexture(nullptr) {

	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene0::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	sphere = new Actor(nullptr);
	sphere->OnCreate();

	mesh = new Mesh(nullptr,"meshes/Sphere.obj");
	if (mesh->OnCreate() == false) {
		Debug::Error("Can't load Mesh()", __FILE__, __LINE__);
	}

	shader = new Shader(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}
	earthTexture = new Texture();
	if (earthTexture->LoadImage("textures/earthclouds.jpg") == false) {
		Debug::Error("Can't load Mesh()", __FILE__, __LINE__);
	}
	moonTexture = new Texture();
	if (moonTexture->LoadImage("textures/mars.jpg") == false) {
		Debug::Error("Can't load Mesh()", __FILE__, __LINE__);
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	
	lightPos = Vec3(20.0f, 0.0f, 0.0f);
	return true;
}

void Scene0::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	delete earthTexture;
	delete moonTexture;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		break;

	case SDL_MOUSEMOTION:          
		break;

	case SDL_MOUSEBUTTONDOWN:              
		break; 

	case SDL_MOUSEBUTTONUP:            
	break;

	default:
		break;
    }
}

void Scene0::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;
	earthModelMatrix = MMath::rotate(totalTime * 30.0f, Vec3(0.0f, 1.0f, 0.0f)) *
				MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

	moonModelMatrix = MMath::rotate(totalTime * 10.0f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::translate(Vec3(0.0f,0.0f,6.0f)) *
		MMath::rotate(totalTime * 60.0f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::scale(Vec3(0.27f, 0.27f, 0.27f)) *
		MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

}

void Scene0::Render(){
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, earthModelMatrix);
	glBindTexture(GL_TEXTURE_2D, earthTexture->getTextureID());
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);


	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, moonModelMatrix);
	glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}



	
