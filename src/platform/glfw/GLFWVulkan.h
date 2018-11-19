/*
* Filename: GLFWVulkan.h
* Author: Lars Vidar Magnusson
*/

#pragma once

#define GLFWVULKAN_NAME "GLFWVulkan"

class GLFWVulkan : public Platform {

private:

    GLFWVulkan() {}
    
public:

    static Platform * Create(PlatformConfig &config);

    bool Initialize(PlatformConfig &config);

	void Shutdown();

	void HandleEvents();

	void SwapBuffers();

	void *LoadLibrary(const string &filename);

	void UnloadLibrary(void *handle);

	void *LoadLibrarySymbol(void *handle, const string &name);

	unsigned long long GetSystemTime();

    const string &GetCommandLine();

private:

    class __Register {
    private:
        static __Register singleton;
    public:
        __Register() { Platform::RegisterImplementation(GLFWVULKAN_NAME, &(GLFWVulkan::Create)); }
    };

};
