#include <iostream>
#include <Shader.hpp>
#include <Window.hpp>

void Window::loop() {
	bool errorsInLoop = false;

	while (!glfwWindowShouldClose(window) && !errorsInLoop) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& [camID, camera] : cameras) camera.updateViewProjection();

		for (auto& [shaderID, camMap] : meshes) {
			shaders.at(shaderID).use();

			if (checkError("mesh, shader use")) errorsInLoop = true;

			shaders.at(shaderID).uploadUniforms();
			//shaders.at(shaderID).setVec3("lightDir", Vec3{-0.5f, -1.0f, -0.3f}); // temporary testing thing

			if (checkError("mesh, shader set vec3")) errorsInLoop = true;

			for (auto& [camID, meshEntries] : camMap) {
				shaders.at(shaderID).setMat4("viewProjection", cameras.at(camID).getViewProjection());

				if (checkError("mesh, shader set mat4")) errorsInLoop = true;

				for (auto& meshEntry : meshEntries) meshEntry.mesh.draw();

				if (checkError("mesh, draw")) errorsInLoop = true;
			}
		}

		for (auto& [shaderID, camMap] : models) {
			shaders.at(shaderID).use();

			if (checkError("model, shader use")) errorsInLoop = true;

			shaders.at(shaderID).uploadUniforms();
			//shaders.at(shaderID).setVec3("lightDir", Vec3{-0.5f, -1.0f, -0.3f}); // temporary testing thing

			if (checkError("model, shader set vec3")) errorsInLoop = true;

			for (auto& [camID, modelEntries] : camMap) {
				shaders.at(shaderID).setMat4("viewProjection", cameras.at(camID).getViewProjection());

				if (checkError("model, shader set mat4")) errorsInLoop = true;

				for (auto& modelEntry : modelEntries) modelEntry.model.draw();

				if (checkError("model, draw")) errorsInLoop = true;
			}
		}

		checkError("Main Loop");

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
