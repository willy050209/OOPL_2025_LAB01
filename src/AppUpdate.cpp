#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

inline void CharacterMove(const std::shared_ptr<Character>& ptr,const float& d = 1.0f) noexcept {
    auto tmp = ptr->GetPosition();
    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        tmp.y += d;
    }else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        tmp.y -= d;
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        tmp.x += d;
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        tmp.x -= d;
    }
    ptr->SetPosition(tmp);
}

void App::Update() {

    // TODO: Add your own logics to finish the tasks in README.md

    /*
     *  Do not touch the code below as they serve the purpose for validating the tasks,
     *  rendering the frame, and exiting the game.
    */

    switch (m_Phase)
    {
    case App::Phase::CHANGE_CHARACTER_IMAGE:
        if (m_Giraffe->GetImagePath() != GA_RESOURCE_DIR"/Image/Character/giraffe.png")
            m_Giraffe->SetImage(GA_RESOURCE_DIR"/Image/Character/giraffe.png");
        break;
    case App::Phase::ABLE_TO_MOVE:
        CharacterMove(m_Giraffe, 5.0f);
        break;
    case App::Phase::COLLIDE_DETECTION:
        CharacterMove(m_Giraffe, 5.0f);
        if (m_Giraffe->IfCollides(m_Chest) && m_Chest->GetVisibility())
            m_Chest->SetVisible(false);
        break;
    case App::Phase::BEE_ANIMATION:
        m_Bee->SetLooping(true);
        ((Util::Animation*)m_Bee->getDrawable())->Play();
        break;
    case App::Phase::OPEN_THE_DOORS:
        CharacterMove(m_Giraffe, 5.0f);
        for (auto& it : m_Doors) {
            if (m_Giraffe->IfCollides(it) && it->GetImagePath() == GA_RESOURCE_DIR"/Image/Character/door_close.png")
                it->SetImage(GA_RESOURCE_DIR"/Image/Character/door_open.png");
        }
        break;
    case App::Phase::COUNTDOWN:
        m_Ball->SetLooping(false);
        ((Util::Animation*)m_Ball->getDrawable())->Play();
        if (((Util::Animation*)m_Ball->getDrawable())->GetCurrentFrameIndex() == 3)
            ((Util::Animation*)m_Ball->getDrawable())->Pause();
        break;
    default:
        break;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            ValidTask();
        }
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

    m_Root.Update();
}
