#pragma once
#include <ByteCore/Core/Window.h>


class ImGuiLayer {
public: 
	void Initialize(Byte::Window& window);
	void ShutDown();
	void NewFrame();
	void EndFrame();	
};