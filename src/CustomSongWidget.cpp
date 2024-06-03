// #include "AddIDs.hpp"

#include "Geode/binding/InfoAlertButton.hpp"
#include <Geode/Bindings.hpp>
#include <Geode/utils/NodeIDs.hpp>
#include <Geode/modify/CustomSongWidget.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(CustomSongWidget) {
    setIDSafe<CCScale9Sprite>(this, 0, "bg");
    setIDSafe<CCSprite>(this, 0, "loading-bar");
    m_songLabel->setID("song-name-label");
    m_artistLabel->setID("artist-label");
    m_songIDLabel->setID("id-and-size-label");
    m_errorLabel->setID("error-label");
    m_buttonMenu->setID("buttons-menu");
    m_downloadBtn->setID("download-button");
    m_cancelDownloadBtn->setID("cancel-button");
    m_selectSongBtn->setID("use-button");
    m_getSongInfoBtn->setID("get-song-info-button");
    m_playbackBtn->setID("play-song-button");
    m_moreBtn->setID("more-button");
    m_deleteBtn->setID("delete-button");
    m_ncsLogo->setID("ncs-logo");
    setIDSafe<InfoAlertButton>(m_buttonMenu, 0, "info-button");
};

struct CustomSongWidgetIDs : Modify<CustomSongWidgetIDs, CustomSongWidget> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("CustomSongWidget::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set CustomSongWidget::init hook priority, node IDs may not work properly");
        }
    }

    bool init(
        SongInfoObject* songInfo,
        CustomSongDelegate* songDelegate,
        bool showSongSelect,
        bool showPlayMusic,
        bool showDownload,
        bool isRobtopSong,
        bool unkBool,
        bool isMusicLibrary,
        int unk       
    ) {
        if (!CustomSongWidget::init(
            songInfo,
            songDelegate,
            showSongSelect,
            showPlayMusic,
            showDownload,
            isRobtopSong,
            unkBool,
            isMusicLibrary,
            unk
        )) {
            return false;
        }

        NodeIDs::get()->provide(this);

        return true;
    }
};