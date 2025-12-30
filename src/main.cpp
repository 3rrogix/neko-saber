#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "paper/shared/logger.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Color.hpp"
#include "System/String.hpp"
#include "System/IO/File.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Vector2.hpp"

ModInfo modInfo;

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

MAKE_HOOK_MATCH(TextMeshProUGUI_set_text, il2cpp_utils::FindMethodUnsafe("", "TMPro.TextMeshProUGUI", "set_text", 1), void, TMPro::TextMeshProUGUI* self, System::String* value) {
    if (value != nullptr) {
        System::String* uwuText = System::String::Concat(value, System::String::CreateString(" UwU~"));
        TextMeshProUGUI_set_text(self, uwuText);
    } else {
        TextMeshProUGUI_set_text(self, value);
    }
}

MAKE_HOOK_MATCH(TextMeshProUGUI_Awake, il2cpp_utils::FindMethodUnsafe("", "TMPro.TextMeshProUGUI", "Awake", 0), void, TMPro::TextMeshProUGUI* self) {
    self->set_color(UnityEngine::Color(1.0f, 0.0f, 1.0f, 1.0f));  // Pink
    TextMeshProUGUI_Awake(self);
}

MAKE_HOOK_MATCH(Image_Awake, il2cpp_utils::FindMethodUnsafe("", "UnityEngine.UI.Image", "Awake", 0), void, UnityEngine::UI::Image* self) {
    if (self->get_name() && self->get_name()->Contains(System::String::CreateString("BG"))) {
        self->set_color(UnityEngine::Color(1.0f, 0.0f, 1.0f, 1.0f));  // Pink background
    }
    Image_Awake(self);
}

MAKE_HOOK_MATCH(SceneManager_sceneLoaded, il2cpp_utils::FindMethodUnsafe("", "UnityEngine.SceneManagement.SceneManager", "add_sceneLoaded", 1), void, UnityEngine::SceneManagement::Scene* scene) {
    std::string sceneName = to_utf8(csstrtostr(scene->get_name()));
    if (sceneName == "SoloMenu") {
        ReplaceBackgroundImage("BG", "solo_bg.png");
    } else if (sceneName == "SettingsMenu") {
        ReplaceBackgroundImage("BG", "settings_bg.png");
    } else if (sceneName == "CampaignMenu") {
        ReplaceBackgroundImage("BG", "campaign_bg.png");
    } else if (sceneName == "MultiplayerMenu") {
        ReplaceBackgroundImage("BG", "multiplayer_bg.png");
    }
    SceneManager_sceneLoaded(scene);
}

void ReplaceBackgroundImage(const char* bgName, const char* assetName) {
    UnityEngine::GameObject* bgObj = UnityEngine::GameObject::Find(System::String::CreateString(bgName));
    if (bgObj) {
        UnityEngine::UI::Image* img = bgObj->GetComponent<UnityEngine::UI::Image>();
        if (img) {
            System::String* path = System::String::Concat(System::String::CreateString("/sdcard/ModData/neko-saber/"), System::String::CreateString(assetName));
            if (System::IO::File::Exists(path)) {
                Array<uint8_t>* bytes = System::IO::File::ReadAllBytes(path);
                UnityEngine::Texture2D* tex = UnityEngine::Texture2D::CreateExternalTexture(1024, 1024, UnityEngine::TextureFormat::RGBA32, false, false, nullptr);
                tex->LoadImage(bytes);
                UnityEngine::Sprite* sprite = UnityEngine::Sprite::Create(tex, UnityEngine::Rect(0, 0, 1024, 1024), UnityEngine::Vector2(0.5f, 0.5f));
                img->set_sprite(sprite);
            }
        }
    }
}

extern "C" void setup(ModInfo& info) {
    info.id = "neko-saber";
    info.version = "1.0.0";
    modInfo = info;

    getLogger().info("Setting up NekoSaber mod");

    INSTALL_HOOK(getLogger(), TextMeshProUGUI_set_text);
    INSTALL_HOOK(getLogger(), TextMeshProUGUI_Awake);
    INSTALL_HOOK(getLogger(), Image_Awake);
    INSTALL_HOOK(getLogger(), SceneManager_sceneLoaded);
}

extern "C" void load() {
    getLogger().info("Loading NekoSaber mod");
}