# Node IDs Changelog
## v1.19.0
* Added StarInfoPopup IDs [#115](https://github.com/geode-sdk/NodeIDs/pull/115)
* Fixed incorrect controller sprite ID in GauntletSelectLayer
* Fixed incorrect GJListLayer IDs in Level List view
* Stopped using getChildBySpriteFrameName reimplementation in PauseLayer

## v1.18.0
* Added FriendRequestPopup IDs
* Added GJMessageCell IDs
* Added LevelAreaLayer and SecretLayer3 and SecretLayer6 [#113](https://github.com/geode-sdk/NodeIDs/pull/113)
* Fixed LevelPage IDs on non-level pages
* Updated about.md

## v1.17.0
* Added ItemInfoPopup [#111](https://github.com/geode-sdk/NodeIDs/pull/111)
* Added SecretLayer and SecretLayer4 (2.0 vault and Chamber of Time) [#109](https://github.com/geode-sdk/NodeIDs/pull/109)
* Fixed replaceInput not inheriting number input property [#110](https://github.com/geode-sdk/NodeIDs/pull/110)
* Updated for GD 2.207

## v1.16.0
* Added secret coin ID to LevelPage
* Fixed a crash in LevelCell when Texture Loader fallback is used for the NCS logo
* Fixed incorrect PlayLayer IDs when "Hide Playtest Text" setting is enabled
* Improved LevelPage handling (adding nodes in init should no longer break the whole ID set)

## v1.15.0
* Fixed an issue where some Private Servers would crash upon opening level comments
* Improved GauntletNode IDs

## v1.14.1
* Fixed CommentCell positioning on 4:3 displays

## v1.14.0
* Added GauntletLayer IDs
* Upgraded CommentCell for level comments

## v1.13.2
* Fixed testmode label in main levels (PlayLayer)
* Fixed crash when entering Gauntlets (macOS only)

## v1.13.1
* Fixed improper assignment of claim-button in LevelListLayer

## v1.13.0
* Added LevelListLayer
* Added FriendsProfilePage
* Added DemonInfoPopup
* Added SecretLayer2 (thanks @MuhXd [#98](https://github.com/geode-sdk/NodeIDs/pull/98))
* Fixed parental control crash in InfoLayer while loading comments (thanks @SpaghettDev [#94](https://github.com/geode-sdk/NodeIDs/pull/94))
* Fixed ProfilePage positioning issues (name running away, info button misaligned after refresh)
* Fixed some CustomizeObjectLayer issues (invisible clear text button, misalignments)
* Fixed EditorPauseLayer issues (thanks @Alphalaneous [#95](https://github.com/geode-sdk/NodeIDs/pull/95))

## v1.12.0

 * Bump Geode to v3.0.0-beta.1

## v1.11.0
* Add IDs for all the EditButtonBars in EditorUI as well as for the edit buttons (move, rotate, etc.)

## v1.10.2
* Rebuild the mod against updated bindings to fix macOS crashes

## v1.10.1
* Temporarily remove LevelListLayer IDs as there were no layouts which will need to be added due to API breaks

## v1.10.0
 * Added CustomSongWidget (thanks @Fleeym)
 * Added ShardsPage, DemonFilterSelectLayer, LevelListLayer, LevelListCell & MoreSearchLayer (thanks @RayDeeUx, [#50](https://github.com/geode-sdk/NodeIDs/pull/50))
 * Added GJGroundLayer & MenuGameLayer (thanks @TheSillyDoggo, [#56](https://github.com/geode-sdk/NodeIDs/pull/56))
 * Tweak the positioning of `bottom-menu` in `CreatorLayer` (@acaruso-xx, [#53](https://github.com/geode-sdk/NodeIDs/pull/53))

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