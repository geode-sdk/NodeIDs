# Node IDs Changelog
## v1.9.1
* Updated EditorUI positioning logic to fix mod compatibility regressions

## v1.9.0
* Added batch-layer for GJBaseGameLayer
* Added GauntletSelectLayer (thanks @SpaghettDev and @ninXout)
* Added GauntletNode, LevelPage, LevelSelectLayer and MoreOptionsLayer (thanks @SpaghettDev)
* Added GJDropDownLayer and GJListLayer (thanks @kynex7510)
* Added layouts and menus to LevelSearchLayer (thanks @Alphalaneous)
* Added more PlayLayer IDs (thanks @Prevter)
* Fixed EditorPauseLayer on mobile
* Fixed EditorUI spacing
* Fixed LevelInfoLayer misalignments

## v1.8.1
- Fixed the rewards room misalignment on non-16:9 screens

## v1.8.0
* charactercolorpage :D by @Weebifying in [#27](https://github.com/geode-sdk/NodeIDs/pull/27)
* Implement SecretRewardsLayer (chest room) by @MaSp005 in [#28](https://github.com/geode-sdk/NodeIDs/pull/28)
* LevelEditorLayer.cpp implemented and PlayLayer.cpp modified by @Termantita in [#31](https://github.com/geode-sdk/NodeIDs/pull/31)

# v1.7.1
- Removed UILayer Node ID from PlayLayer because mods depended on the default one

# v1.7.0
- Fixed EndLevelLayer IDs for newly collected coins
- Fixed SetGroupIDLayer misalignments
- Added OptionsLayer (thanks @Uproxide)
- Added ChallengesPage (thanks @Uproxide)
- Added PlayLayer (thanks @Prevter)
- Added GJCommentListLayer

# v1.6.1
- Fixed EndLevelLayer crash on Mac

# v1.6.0
* Add `EndLevelLayer` IDs
* Fix inputs not working in `SetGroupIDLayer`
* Bump Geode version requirement to beta.20+

# v1.5.1
- Fix `SetGroupIDLayer` being broken like most of the time

# v1.5.0
- Add `SetGroupIDLayer` IDs and layouts

# v1.4.0
- Fixed PauseLayer crashing on Mac
- Added FLAlertLayer node IDs
- Added LevelAreaInnerLayer node IDs

# v1.3.0
- Fix a crash in PauseLayer
- Add CustomizeObjectLayer (not available for MacOS yet)

# v1.2.4
- Fixed duplicate ProfilePage menus
- Fixed PauseLayer crash for fresh save files
- Added macOS support

# v1.2.3
- Fixed MegaHack Level Edit issue >:(
- Fixed LevelCell properly

# v1.2.2
- Fixed weekly level crashing

# v1.2.1
- Fixed editor pause menu crash on Windows yayy

# v1.2.0
Added IDs for:
- EditorPauseLayer
- EditorUI
- GJGarageLayer
- PauseLayer
- UILayer

Added logo

# v1.1.4
- Fixed an android32 specific crash in Saved Levels

# v1.1.3
- Added Android 2.205 support

# v1.1.2
- Fixed Android 6 compatibility
- Fixed swapped buttons in LevelInfoLayer
- Added bottom layout to GJScoreCell

# v1.1.1
- Fixed crashes in InfoLayer and LevelCell
- Added missing LevelInfoLayer IDs

# v1.1.0
- Updated for 2.204
- Many many more ids (thank you @Cvolton)

# v1.0.0
Initial release for Windows and Android, thanks to our lovely crewmate @cvolton. Adds ids for:

- CommentCell
- CreatorLayer
- DailyLevelNode
- DailyLevelPage
- EditLevelLayer
- LevelBrowserLayer
- LevelInfoLayer
- LevelSearchLayer