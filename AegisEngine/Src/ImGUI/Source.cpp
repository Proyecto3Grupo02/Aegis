#include <imgui.h>
#include <imgui_impl_glut.h>
#include <imgui_impl_opengl3.h>
int main() {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
}