#include "imgui.h"
#include <iostream>
#include <ctime>

HWND hwnd;
RECT rc;

#define WIDTH  600 // Loader Size X
#define HEIGHT 600 // Loader Size Y

using namespace ImGui;

namespace c_gui
{
    static float textop = 0;

    static ImVec4 blue = { 0.0157, 0.3608, 0.5882, textop };
    static ImVec4 white = { 1, 1, 1, textop };
    static ImVec4 red = { 0.9804, 0.2235, 0.2118, textop };
    static ImVec4 green = { 0.0745, 0.7176, 0.4431, textop };

    class gui
    {

    public:

        DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
        ImGuiStyle& style = ImGui::GetStyle();

        void begin(const char* name, float X, float Y, float oppacity)
        {
            style.WindowRounding = 10.0f; //WINDOW ROUNDING
            style.FrameRounding = 5.0f; //FRAME ROUNDING FOR ALL ITEMS
            style.WindowBorderSize = 0.f; //REMOVES THE SMALL BORDER

            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0941, 0.0941, 0.1059, oppacity));
            ImGui::Begin(name, NULL, window_flags);
            sws(X, Y);
        }

        void end()
        {
            ImGui::End();
        }

        void sws(float X, float Y)
        {
            SetWindowSize({ X, Y });
        }

        void setpos(float X, float Y)
        {
            SetCursorPos({ X, Y });
        }

        void cText(const char* text, float posX, float posY, ImVec4 color, float op)
        {
            setpos(posX, posY);
            ImGui::TextColored(color, text);
        }

        void CEtext(std::string text, float posY) {
            auto windowWidth = ImGui::GetWindowSize().x;
            auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

            ImGui::SetCursorPos(ImVec2((windowWidth - textWidth) * 0.5f, posY));
            ImGui::Text(text.c_str());
        }

        void mw() { //makes possible moving the window

            GetWindowRect(hwnd, &rc);

            if (ImGui::GetWindowPos().x != 0 || ImGui::GetWindowPos().y != 0)
            {
                MoveWindow(hwnd, rc.left + ImGui::GetWindowPos().x, rc.top + ImGui::GetWindowPos().y, WIDTH, HEIGHT, TRUE);
                ImGui::SetWindowPos(ImVec2(0.f, 0.f));
            }

        }

        void Blur(HWND hwnd)
        {
            struct ACCENTPOLICY
            {
                int na;
                int nf;
                int nc;
                int nA;
            };
            struct WINCOMPATTRDATA
            {
                int na;
                PVOID pd;
                ULONG ul;
            };

            const HINSTANCE hm = LoadLibrary(L"user32.dll");
            if (hm)
            {
                typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

                const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
                if (SetWindowCompositionAttribute)
                {
                    ACCENTPOLICY policy = { 3, 0, 0, 0 };

                    WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
                    SetWindowCompositionAttribute(hwnd, &data);
                }
                FreeLibrary(hm);
            }
        }
    };
}
