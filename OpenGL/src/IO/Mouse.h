#pragma once

#include "Vector.h"

namespace IO {
    struct Mouse {
        static constexpr int LEFT_MOUSE   = 0;
        static constexpr int RIGHT_MOUSE  = 1;
        static constexpr int MIDDLE_MOUSE = 2;
        static constexpr int LAST_MOUSE   = 7; // GLFW_MOUSE_BUTTON_LAST

        int mouseStates = 0;
        int prevMouseStates = 0;

        Mouse() = default;

        void Update();

        [[nodiscard]] Maths::Vec2d GetMousePosPx() const;
        [[nodiscard]] Maths::Vec2d GetMousePos() const;
        [[nodiscard]] bool IsInWindow() const;
        
        [[nodiscard]] int  PressedState()         const;
        [[nodiscard]] bool LeftPressed()          const;
        [[nodiscard]] bool RightPressed()         const;
        [[nodiscard]] bool MiddlePressed()        const;
        [[nodiscard]] bool ButtonPressed(int btn) const;
        [[nodiscard]] bool AnyPressed()           const;
        [[nodiscard]] bool NonePressed()          const;

        [[nodiscard]] int  OnPressState()         const;
        [[nodiscard]] bool LeftOnPress()          const;
        [[nodiscard]] bool RightOnPress()         const;
        [[nodiscard]] bool MiddleOnPress()        const;
        [[nodiscard]] bool ButtonOnPress(int btn) const;
        [[nodiscard]] bool AnyOnPress()           const;
        [[nodiscard]] bool NoneOnPress()          const;

        [[nodiscard]] int  OnReleaseState()         const;
        [[nodiscard]] bool LeftOnRelease()          const;
        [[nodiscard]] bool RightOnRelease()         const;
        [[nodiscard]] bool MiddleOnRelease()        const;
        [[nodiscard]] bool ButtonOnRelease(int btn) const;
        [[nodiscard]] bool AnyOnRelease()           const;
        [[nodiscard]] bool NoneOnRelease()          const;

        static bool IsStandardMouseButton(int btn);
        static bool IsValidMouseButton(int btn);
        static const char* MouseButtonToStr(int btn);
    };
}