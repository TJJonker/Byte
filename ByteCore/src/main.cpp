#include <iostream>

#include <ByteCore/Core/Window.h>
#include <ByteCore/Temp/ImGuiLayer.h>
#include <imgui.h>

bool ShowProfiler = false;

void Profiler();

int main() {
    Byte::Window window;
    window.Initialize();
    window.CreateWindow(1920, 1080, "Byte");

    ImGuiLayer imguiLayer;
    imguiLayer.Initialize(window);

    while (!window.ShouldClose()) {
        window.PollEvents();

        window.Clear();
        imguiLayer.NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags = 
            ImGuiWindowFlags_NoTitleBar | 
            ImGuiWindowFlags_NoCollapse | 
            ImGuiWindowFlags_NoResize | 
            ImGuiWindowFlags_NoMove;

        ImGui::Begin("Byte", nullptr, windowFlags);

        ImGui::BeginMainMenuBar();
        {
            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Profiler", "CTRL+P", ShowProfiler)) {
                    ShowProfiler = !ShowProfiler;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGuiID dockspace_id = ImGui::GetID("ByteDockSpace");
        ImGui::DockSpace(dockspace_id);
        ImGui::End();

        ImGui::Begin("something");
        ImGui::End();



        Profiler();

        // Sample UI
        //ImGui::ShowDemoWindow();

        imguiLayer.EndFrame();
        window.SwapBuffer();
    }

    imguiLayer.ShutDown();
    window.ShutDown();

    return 0;
}



void Profiler() {
    if (ShowProfiler) {
        ImGui::Begin("Profiler", &ShowProfiler);

        ImGui::End();
    }
}