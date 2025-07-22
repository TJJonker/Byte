#include <iostream>

#include <ByteCore/Core/Window.h>
#include <ByteCore/Temp/ImGuiLayer.h>
#include <imgui.h>

bool ShowProfiler = false;

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

        if (ShowProfiler) {
            ImGui::Begin("Profiler", &ShowProfiler);
            ImGui::Text("Hello Profiler");
            static float frameTimes[100] = {};
            static int index = 0;
            frameTimes[index] = ImGui::GetIO().DeltaTime * 1000.0f; // ms
            index = (index + 1) % 100;

            ImGui::PlotLines("Frame Times (ms)", frameTimes, IM_ARRAYSIZE(frameTimes), index, nullptr, 0.0f, 40.0f, ImVec2(0, 80));

            ImGui::End();
        }

        // Sample UI
        //ImGui::ShowDemoWindow();

        imguiLayer.EndFrame();
        window.SwapBuffer();
    }

    imguiLayer.ShutDown();
    window.ShutDown();

    return 0;
}
